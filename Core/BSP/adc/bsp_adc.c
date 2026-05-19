#include "bsp_adc.h"
#include "bsp_adc_fifo.h"
#include "adc.h"
#include "tim.h"
#include <string.h>
#include <stdio.h>

/* 使用片内 SRAM 存储缓冲区 */
static uint16_t s_adc_buff[ADC_BUFF_SIZE];
static bsp_adc_fifo_t s_adc_fifo;

/* 对外接口指针指向片内数组 */
uint16_t *g_adc_buff = s_adc_buff;

/**
 * @brief 获取 ADC FIFO 设备指针
 * @return bsp_adc_fifo_t* FIFO 设备指针
 */
bsp_adc_fifo_t* bsp_adc_get_fifo_dev(void)
{
    return &s_adc_fifo;
}

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

    /* 清空片内 SRAM 中的 FIFO 状态 */
    memset(bsp_adc_get_fifo_dev(), 0, sizeof(bsp_adc_fifo_t));
}

/**
 * @brief 启动ADC采集
 */
void bsp_adc_start(void)
{
    /* 检查 ADC 是否已经在运行，避免重复启动导致状态机冲突 */
    if (hadc1.State == HAL_ADC_STATE_BUSY_REG) {
        return;
    }

    /* 启动 ADC DMA 采集 */
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)g_adc_buff, ADC_BUFF_SIZE);
    
    /* 启动 Timer2 产生触发信号 */
    HAL_TIM_Base_Start(&htim2);
}

/**
 * @brief 停止ADC采集
 */
void bsp_adc_stop(void)
{
    /* 停止 Timer2 触发 */
    HAL_TIM_Base_Stop(&htim2);

    /* 停止 ADC DMA 采集 */
    HAL_ADC_Stop_DMA(&hadc1);
}

/**
 * @brief ADC 错误回调函数
 * @note  实现硬件级自愈：当发生 Overrun 时立即清除标志位并重启
 */
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        uint32_t err = HAL_ADC_GetError(hadc);
        if (err & HAL_ADC_ERROR_OVR)
        {
            /* 1. 彻底清除 OVR 标志位 (关键步骤) */
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_OVR);
            
            /* 2. 重启 DMA 采集 */
            /* 注意：在中断中直接调用 HAL_ADC_Start_DMA 是安全的，因为它不涉及阻塞操作 */
            HAL_ADC_Start_DMA(hadc, (uint32_t *)g_adc_buff, ADC_BUFF_SIZE);
        }
    }
}

/**
 * @brief 获取ADC转换后的电压值 (单位: mV)
 */
uint32_t bsp_adc_get_voltage(uint16_t raw_value)
{
    return (uint32_t)((uint64_t)raw_value * 3300 / 4096);
}

/**
 * @brief 内部抽取处理逻辑
 * @param start_idx 起始索引
 */
static void bsp_adc_extract_to_fifo(uint32_t start_idx)
{
    static uint32_t s_rem = 0;             /* 累计未抽取的点数偏移 */
    static uint32_t s_sample_idx = 0;      /* 当前 FIFO 块内的采样点索引 */
    
    bsp_adc_fifo_t *fifo = bsp_adc_get_fifo_dev();
    uint8_t w_idx = fifo->write_idx;

    /* 处理半个缓冲区的数据量 */
    uint32_t process_len = ADC_BUFF_SIZE / 2;
    
    for (int i = (200 - 1 - s_rem); i < process_len; i += 200)
    {
        fifo->data[w_idx][s_sample_idx] = g_adc_buff[start_idx + i];
        s_sample_idx++;
        
        if (s_sample_idx >= ADC_DMA_BUFF_SIZE)
        {
            s_sample_idx = 0;
            fifo->status[w_idx].is_full = 1;
            w_idx = (w_idx + 1) % ADC_FIFO_NUM;
            fifo->write_idx = w_idx;
            
            if (g_adc_data_sem != NULL) {
                BaseType_t xHigherPriorityTaskWoken = pdFALSE;// 标志位，用于判断是否需要切换到高优先级任务
                xSemaphoreGiveFromISR(g_adc_data_sem, &xHigherPriorityTaskWoken);// 释放信号量，通知数据处理任务
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);// 切换到高优先级任务
            }
        }
    }
    
    /* 更新偏移量 */
    s_rem = (s_rem + process_len) % 200;
}

/**
 * @brief ADC DMA 传输半完成回调函数
 */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        bsp_adc_extract_to_fifo(0);
    }
}

/**
 * @brief ADC DMA 传输完成回调函数
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        bsp_adc_extract_to_fifo(ADC_BUFF_SIZE / 2);
    }
}
