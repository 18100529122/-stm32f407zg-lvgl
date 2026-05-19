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

/**
 * @brief 数据处理任务初始化
 */
void app_data_process_init(void)
{
    app_data_fft_init();
    app_data_create_init();
    
    /* 增加堆栈大小到 4096，防止 FFT 和 printf 导致溢出 */
    xTaskCreate(app_data_process_task, "adc_process", 4096, NULL, osPriorityAboveNormal, NULL);
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
                // static uint32_t printf_count = 0;
                // printf_count=(printf_count+1)%10;
                // if (printf_count == 0) {
                //     printf("r_idx: %d\r\n", r_idx);
                // }
                

                /* 执行 FFT 计算 */
                // printf("FFT Start\r\n");
                app_data_fft_compute(fifo->data[r_idx], ADC_DMA_BUFF_SIZE);
                // printf("FFT Done\r\n");
                
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

                /* 清除该块的已满标志 */
                fifo->status[r_idx].is_full = 0;
                
                /* 移动读取索引 */
                r_idx = (r_idx + 1) % ADC_FIFO_NUM;
                fifo->read_idx = r_idx;
            }
        }
    }
}
