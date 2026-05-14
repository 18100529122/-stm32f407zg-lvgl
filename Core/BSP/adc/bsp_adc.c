#include "bsp_adc.h"
#include "bsp_adc_fifo.h"
#include "adc.h"
#include "tim.h"
#include <string.h>

uint16_t g_adc_buff[ADC_BUFF_SIZE];
volatile uint16_t g_adc_average = 0;

/* FIFO 设备定义 */
bsp_adc_fifo_t g_adc_fifo_dev = {0};
/* 信号量定义 */
SemaphoreHandle_t g_adc_data_sem = NULL;

/**
 * @brief 初始化ADC并开启DMA采集
 * @note  由于不修改 Core/Src/adc.c，部分寄存器配置在运行时动态调整以确保 1Msps 触发
 */
void bsp_adc_init(void)
{
    /* 创建信号量 */
    if (g_adc_data_sem == NULL) {
        g_adc_data_sem = xSemaphoreCreateBinary();
    }

    /* 动态调整 ADC1 配置以支持 Timer2 触发 and DMA 连续请求 */
    hadc1.Instance->CR2 &= ~ADC_CR2_CONT;      /* 关闭连续转换模式，改为触发模式 */
    hadc1.Instance->CR2 |= ADC_CR2_DDS;       /* 开启 DMA 连续请求 (DDS位) */
    
    /* 设置外部触发源为 Timer2 TRGO，并使能上升沿触发 */
    hadc1.Instance->CR2 &= ~ADC_CR2_EXTSEL;
    hadc1.Instance->CR2 |= ADC_EXTERNALTRIGCONV_T2_TRGO;
    hadc1.Instance->CR2 &= ~ADC_CR2_EXTEN;
    hadc1.Instance->CR2 |= ADC_EXTERNALTRIGCONVEDGE_RISING;

    /* 启动 ADC DMA 采集 */
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)g_adc_buff, ADC_BUFF_SIZE);
    
    /* 启动 Timer2 产生触发信号 */
    HAL_TIM_Base_Start(&htim2);
}

/**
 * @brief 获取ADC转换后的电压值 (单位: mV)
 */
uint32_t bsp_adc_get_voltage(uint16_t raw_value)
{
    return (uint32_t)((uint64_t)raw_value * 3300 / 4096);
}

/**
 * @brief 获取平均电压值 (单位: mV)
 */
uint32_t bsp_adc_get_average_voltage(void)
{
    return bsp_adc_get_voltage(g_adc_average);
}

/**
 * @brief ADC DMA 传输完成回调函数
 * @note  当 DMA 缓冲区填满时由 HAL 库自动调用
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        uint8_t w_idx = g_adc_fifo_dev.write_idx;
        
        /* 拷贝数据到固定 FIFO 块 */
        memcpy(g_adc_fifo_dev.data[w_idx], g_adc_buff, ADC_DMA_BUFF_SIZE * 2);
        
        /* 标记该块已满 */
        g_adc_fifo_dev.status[w_idx].is_full = 1;
        
        /* 更新写入索引 */
        g_adc_fifo_dev.write_idx = (w_idx + 1) % ADC_FIFO_NUM;
        
        /* 发送信号量给后台任务 */
        if (g_adc_data_sem != NULL) {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            xSemaphoreGiveFromISR(g_adc_data_sem, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}
