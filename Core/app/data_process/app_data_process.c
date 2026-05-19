#include "app_data_process.h"
#include "bsp_adc_fifo.h"
#include "bsp_adc.h"
#include "app_data_fft.h"
#include "app_data_create.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cmsis_os.h"
#include "main.h"
#include "arm_math.h"
#include <stdio.h>
#include <string.h>

app_data_result_t g_app_data_result;

static void app_data_process_task(void *argument);
static void app_data_process_update_tof(uint16_t *data, uint32_t len);

/**
 * @brief 数据处理任务初始化
 */
void app_data_process_init(void)
{
    app_data_fft_init();
    app_data_create_init();
    
    /* 初始化飞行图谱参数 */
    g_app_data_result.trigger_thr_mv = 5.0f; /* 触发阈值设为 5.0mV，适应 0-20mV 图谱范围 */
    app_data_process_reset_tof();
    
    /* 增加堆栈大小到 4096，防止 FFT 和 printf 导致溢出 */
    xTaskCreate(app_data_process_task, "adc_process", 4096, NULL, osPriorityAboveNormal, NULL);
}

/**
 * @brief 重置飞行图谱矩阵
 */
void app_data_process_reset_tof(void)
{
    memset(g_app_data_result.tof_matrix, 0, sizeof(g_app_data_result.tof_matrix));
    g_app_data_result.tof_point_cnt = 0;
    g_app_data_result.last_pulse_sample_idx = 0;
}

/**
 * @brief 获取数据处理结果
 * @return app_data_result_t 数据处理结果
 */
app_data_result_t* app_data_process_get_result(void)
{
    return &g_app_data_result;
}

uint8_t app_data_process_get_rms_uint8(void)
{
    return (uint8_t)(g_app_data_result.rms * 0.01f);
}

uint8_t app_data_process_get_peak_uint8(void)   
{
    return (uint8_t)(g_app_data_result.peak * 0.01f);
}

uint8_t app_data_process_get_freq_50hz_uint8(void)
{
    return (uint8_t)(g_app_data_result.freq_50hz * 0.05f);
}

uint8_t app_data_process_get_freq_100hz_uint8(void)
{
    return (uint8_t)(g_app_data_result.freq_100hz * 0.05f);
}

char *app_data_process_get_rms_str(void)
{
    static char rms_data[10];
    snprintf(rms_data, sizeof(rms_data), "%.2f", g_app_data_result.rms);
    return rms_data;
}

char *app_data_process_get_peak_str(void)
{
    static char peak_data[10];
    snprintf(peak_data, sizeof(peak_data), "%.2f", g_app_data_result.peak);
    return peak_data;
}

char *app_data_process_get_freq_50hz_str(void)
{
    static char freq_50hz_data[10];
    snprintf(freq_50hz_data, sizeof(freq_50hz_data), "%.2f", g_app_data_result.freq_50hz);
    return freq_50hz_data;
}

char *app_data_process_get_freq_100hz_str(void)
{
    static char freq_100hz_data[10];
    snprintf(freq_100hz_data, sizeof(freq_100hz_data), "%.2f", g_app_data_result.freq_100hz);
    return freq_100hz_data;
}

char *app_data_process_get_threshold_str(void)
{
    static char threshold_data[10];
    snprintf(threshold_data, sizeof(threshold_data), "%.2f", g_app_data_result.trigger_thr_mv);
    return threshold_data;
}

uint16_t app_data_process_get_tof_bin(uint8_t amp_idx, uint8_t time_idx)
{
    if (amp_idx < TOF_AMP_BINS && time_idx < TOF_TIME_BINS) {
        return g_app_data_result.tof_matrix[amp_idx][time_idx];
    }
    return 0;
}


/**
 * @brief 数据处理任务主体
 */
static void app_data_process_task(void *argument)
{
    /* 启动 ADC 采样 (此时任务已启动，可以接收信号量) */
    printf("ADC Start from Task Done\r\n");
    osDelay(500);
    bsp_adc_start();

    while (1)
    {
        /* 恢复为永久等待，由硬件中断级自愈保证稳定性 */
        if (xSemaphoreTake(g_adc_data_sem, portMAX_DELAY) == pdTRUE)
        // if (xSemaphoreTake(g_adc_data_sem, pdMS_TO_TICKS(500)) == pdTRUE)
        {
            bsp_adc_fifo_t *fifo = bsp_adc_get_fifo_dev();
            uint8_t r_idx = fifo->read_idx;
            
            /* 检查是否有未处理 of 已满块 */
            while (fifo->status[r_idx].is_full)
            {
                /* 执行 FFT 计算 */
                app_data_fft_compute(fifo->data[r_idx], ADC_DMA_BUFF_SIZE);
                
                /* 计算有效值 (RMS) 和 最大值 (Peak) */
                float32_t sum_sq = 0;
                uint16_t max_val = 0;
                for (uint32_t i = 0; i < ADC_DMA_BUFF_SIZE; i++) {
                    float32_t val = (float32_t)fifo->data[r_idx][i];
                    sum_sq += val * val;
                    if (fifo->data[r_idx][i] > max_val) {
                        max_val = fifo->data[r_idx][i];
                    }
                }
                
                g_app_data_result.rms = sqrtf(sum_sq / ADC_DMA_BUFF_SIZE);
                g_app_data_result.peak = (float32_t)max_val;

                /* 更新频率分量 (50Hz 和 100Hz) */
                g_app_data_result.freq_50hz = app_data_fft_get_freq_value(0);
                g_app_data_result.freq_100hz = app_data_fft_get_freq_value(1);

                /* 更新飞行图谱 (ToF) */
                app_data_process_update_tof(fifo->data[r_idx], ADC_DMA_BUFF_SIZE);

                /* 当累计点数超过 2000 个时，自动重置图谱，以保持显示的实时性并防止矩阵饱和 */
                if (g_app_data_result.tof_point_cnt > 2000) {
                    app_data_process_reset_tof();
                }

                /* 清除该块的已满标志 */
                fifo->status[r_idx].is_full = 0;
                
                /* 移动读取索引 */
                r_idx = (r_idx + 1) % ADC_FIFO_NUM;
                fifo->read_idx = r_idx;
            }
        }
    }
}

/**
 * @brief 更新飞行图谱统计矩阵
 * @param data ADC 原始数据 (抽点后)
 * @param len 数据长度
 */
static void app_data_process_update_tof(uint16_t *data, uint32_t len)
{
    static uint32_t total_sample_cnt = 0;
    
    for (uint32_t i = 0; i < len; i++) {
        total_sample_cnt++;
        
        /* 转换为 mV (ADC 12bit, 3.3V基准) 
           注意：由于 DAC 输出是 0-3.3V (约 3000mV)，而图谱范围是 0-20mV，
           为了模拟实际传感器信号，此处增加一个 0.005 的缩放系数 (即 3000mV -> 15mV)
        */
        float32_t mv = ((float32_t)data[i] * 3300.0f / 4096.0f) * 0.005f;
        
        /* 脉冲峰值检测：
           1. 超过阈值 trigger_thr_mv
           2. 局部最大值 (当前值 > 前一个值 且 当前值 >= 后一个值)
        */
        if (mv > g_app_data_result.trigger_thr_mv) {
            /* 边界处理：忽略块两端的极值以简化逻辑，或使用持久化状态 */
            if (i > 0 && i < len - 1) {
                if (data[i] > data[i - 1] && data[i] >= data[i + 1]) {
                    /* 检测到有效脉冲峰值 */
                    if (g_app_data_result.last_pulse_sample_idx != 0) {
                        /* 计算时间间隔 (有效采样率 5000Hz -> 每个点 0.2ms) */
                        uint32_t interval_samples = total_sample_cnt - g_app_data_result.last_pulse_sample_idx;
                        float32_t interval_ms = (float32_t)interval_samples * 0.2f;
                        
                        /* 映射到矩阵索引 */
                        int amp_idx = (int)(mv / 0.5f);           /* 0-20mV -> 40 bins (0.5mV/bin) */
                        int time_idx = (int)(interval_ms / 2.0f); /* 0-200ms -> 100 bins (2ms/bin) */
                        
                        if (amp_idx < TOF_AMP_BINS && time_idx < TOF_TIME_BINS) {
                            /* 增加计数，限制最大值为 65535 */
                            if (g_app_data_result.tof_matrix[amp_idx][time_idx] < 65535) {
                                g_app_data_result.tof_matrix[amp_idx][time_idx]++;
                                g_app_data_result.tof_point_cnt++;
                            }
                        }
                    }
                    /* 更新上一个脉冲的时间戳 */
                    g_app_data_result.last_pulse_sample_idx = total_sample_cnt;
                }
            }
        }
    }
}
