#include "app_data_process.h"
#include "bsp_adc_fifo.h"
#include "bsp_adc.h"
#include "app_data_fft.h"
#include "app_data_create.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"
#include <stdio.h>

static void app_data_process_task(void *argument);

/**
 * @brief 数据处理任务初始化
 */
void app_data_process_init(void)
{
    app_data_fft_init();
    app_data_create_init();
    xTaskCreate(app_data_process_task, "adc_process", 1024, NULL, osPriorityNormal, NULL);
}

/**
 * @brief 数据处理任务主体
 */
static void app_data_process_task(void *argument)
{
    /* 启动 ADC 采样 (此时任务已启动，可以接收信号量) */
    bsp_adc_start();
    printf("ADC Start from Task Done\r\n");

    while (1)
    {
        /* 等待 DMA 传输完成信号 */
        if (xSemaphoreTake(g_adc_data_sem, portMAX_DELAY) == pdTRUE)
        {
            uint8_t r_idx = g_adc_fifo_dev.read_idx;
            
            /* 检查是否有未处理的已满块 */
            while (g_adc_fifo_dev.status[r_idx].is_full)
            {
                /* 执行 FFT 计算 */
                app_data_fft_compute(g_adc_fifo_dev.data[r_idx], ADC_DMA_BUFF_SIZE);
                
                /* 清除该块的已满标志 */
                g_adc_fifo_dev.status[r_idx].is_full = 0;
                
                /* 移动读取索引 */
                r_idx = (r_idx + 1) % ADC_FIFO_NUM;
                g_adc_fifo_dev.read_idx = r_idx;
            }

            /* 处理完当前所有数据块后，重新开启 ADC 采样 (如果之前因为溢出停止了) */
            bsp_adc_start();
        }
    }
}
