#include "app_data_process.h"
#include "bsp_adc_fifo.h"
#include "bsp_adc.h"
#include "app_data_fft.h"
#include "app_data_create.h"
#include "FreeRTOS.h"
#include "task.h"
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
    /* 将优先级设为 AboveNormal，确保它能抢占 LVGL 的数据更新任务 */
    xTaskCreate(app_data_process_task, "adc_process", 2048, NULL, osPriorityAboveNormal, NULL);
}

/**
 * @brief 获取数据处理结果
 * @return app_data_result_t 数据处理结果
 */
app_data_result_t* app_data_process_get_result(void)
{
    return &g_app_data_result;
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
        /* 等待 DMA 传输完成信号 */
        if (xSemaphoreTake(g_adc_data_sem, portMAX_DELAY) == pdTRUE)
        {
            bsp_adc_fifo_t *fifo = bsp_adc_get_fifo_dev();
            uint8_t r_idx = fifo->read_idx;
            
            /* 检查是否有未处理 of 已满块 */
            while (fifo->status[r_idx].is_full)
            {
                static uint32_t printf_count = 0;
                printf_count=(printf_count+1)%10;
                if (printf_count == 0) {
                    printf("r_idx: %d\r\n", r_idx);
                }
                

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

                /* 清除该块的已满标志 */
                fifo->status[r_idx].is_full = 0;
                
                /* 移动读取索引 */
                r_idx = (r_idx + 1) % ADC_FIFO_NUM;
                fifo->read_idx = r_idx;
            }

            /* 处理完当前所有数据块后，重新开启 ADC 采样 (如果之前因为溢出停止了) */
            bsp_adc_start();
        }
    }
}
