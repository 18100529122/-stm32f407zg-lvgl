#include "app_data_process.h"
#include "bsp_adc_fifo.h"
#include "bsp_adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"

static void app_data_process_task(void *argument);

/**
 * @brief 数据处理任务初始化
 */
void app_data_process_init(void)
{
    xTaskCreate(app_data_process_task, "adc_process", 1024, NULL, osPriorityNormal, NULL);
}

/**
 * @brief 数据处理任务主体
 */
static void app_data_process_task(void *argument)
{
    while (1)
    {
        /* 等待 DMA 传输完成信号 */
        if (xSemaphoreTake(g_adc_data_sem, portMAX_DELAY) == pdTRUE)
        {
            uint8_t r_idx = g_adc_fifo_dev.read_idx;
            
            /* 检查是否有未处理的已满块 */
            while (g_adc_fifo_dev.status[r_idx].is_full)
            {
                uint32_t sum = 0;
                
                /* 求平均值逻辑 */
                for (int i = 0; i < ADC_DMA_BUFF_SIZE; i++)
                {
                    sum += g_adc_fifo_dev.data[r_idx][i];
                }
                
                /* 更新全局平均值 */
                extern volatile uint16_t g_adc_average;
                g_adc_average = (uint16_t)(sum / ADC_DMA_BUFF_SIZE);
                
                /* 清除该块的已满标志 */
                g_adc_fifo_dev.status[r_idx].is_full = 0;
                
                /* 移动读取索引 */
                r_idx = (r_idx + 1) % ADC_FIFO_NUM;
                g_adc_fifo_dev.read_idx = r_idx;
            }
        }
    }
}
