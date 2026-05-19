#ifndef __BSP_ADC_FIFO_H__
#define __BSP_ADC_FIFO_H__

#include "main.h"
#include "FreeRTOS.h"
#include "semphr.h"

#define ADC_DMA_BUFF_SIZE 2048
#define ADC_FIFO_NUM       8

#pragma pack(1)
typedef struct {
    volatile struct {
        uint8_t is_full : 1;
        uint8_t reserved : 7;
    } status[ADC_FIFO_NUM];
    
    volatile uint8_t write_idx;  /* 当前正在写入的 FIFO 索引 */
    volatile uint8_t read_idx;   /* 当前待处理的 FIFO 索引 */
    
    uint16_t data[ADC_FIFO_NUM][ADC_DMA_BUFF_SIZE];
} bsp_adc_fifo_t;
#pragma pack()

extern SemaphoreHandle_t g_adc_data_sem;

#endif /* __BSP_ADC_FIFO_H__ */
