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

    printf("ADC Stop: FIFO Full!\r\n");
}

/**
 * @brief 获取ADC转换后的电压值 (单位: mV)
 */
uint32_t bsp_adc_get_voltage(uint16_t raw_value)
{
    return (uint32_t)((uint64_t)raw_value * 3300 / 4096);
}

/**
 * @brief ADC DMA 传输完成回调函数
 * @note  当 DMA 缓冲区填满时由 HAL 库自动调用。
 *        通过累计偏移量实现大跨度抽取（1/200），而不增加 DMA 缓冲区大小。
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        static uint32_t s_rem = 0;             /* 累计未抽取的点数偏移 */
        static uint32_t s_sample_idx = 0;      /* 当前 FIFO 块内的采样点索引 */
        
        bsp_adc_fifo_t *fifo = bsp_adc_get_fifo_dev();
        uint8_t w_idx = fifo->write_idx;

        /* 如果当前待写入的块已经是满的，说明后台处理太慢，停止采集 */
        // if (fifo->status[w_idx].is_full)
        // {
        //     bsp_adc_stop();
        //     printf("ADC Stop: FIFO Full!\r\n");
        //     // 重置当前块的采样点索引
        //     s_sample_idx = 0;
        //     // 重置偏移量
        //     s_rem = 0;
        //     //清除dma的buff
        //     memset(g_adc_buff, 0, ADC_BUFF_SIZE);
        //     return;
        // }
        
        /* 
         * 优化逻辑：不再遍历 1024 个点，而是直接计算下一个采样点的索引。
         * 循环次数从 1024 次降低到 5~6 次，显著减轻 ISR 负担。
         */
        for (int i = (200 - 1 - s_rem); i < ADC_BUFF_SIZE; i += 200)
        {
            fifo->data[w_idx][s_sample_idx] = g_adc_buff[i];
            s_sample_idx++;
            
            /* 如果当前块存满了 (512个点) */
            if (s_sample_idx >= ADC_DMA_BUFF_SIZE)
            {
                s_sample_idx = 0;
                
                /* 标记该块已满 */
                fifo->status[w_idx].is_full = 1;
                
                /* 更新写入索引 */
                w_idx = (w_idx + 1) % ADC_FIFO_NUM;
                fifo->write_idx = w_idx;
                
                /* 发送信号量给后台任务 */
                if (g_adc_data_sem != NULL) {
                    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                    xSemaphoreGiveFromISR(g_adc_data_sem, &xHigherPriorityTaskWoken);
                    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
                }
            }
        }
        
        /* 更新偏移量：将本轮多出的点数带入下一轮计算 */
        s_rem = (s_rem + ADC_BUFF_SIZE) % 200;
    }
}
