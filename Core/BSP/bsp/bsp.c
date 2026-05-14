#include "bsp.h"
#include "bsp_usart.h"
#include "lcd.h"
#include "touch.h"
#include "bsp_adc.h"
#include "bsp_dac.h"

/**
 * @brief 硬件抽象层初始化 (板级支持包初始化)
 */
void BSP_Init(void)
{
    /* 初始化串口 */
    BSP_USART_Init();
    
    /* 初始化 LCD */
    lcd_init();

    /* 初始化触摸屏 */
    tp_init();

    /* 初始化 ADC 采样 (1Msps) */
    bsp_adc_init();

    /* 初始化 DAC 输出 */
    bsp_dac_init();
}

/**
 * @brief 微秒级延时
 * @note  使用 HAL_GetTick 和系统频率计算，或者简单的循环。
 *        对于 F407 (168MHz)，使用循环是最简单直接的方法。
 */
void delay_us(uint32_t us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;

    ticks = us * (SystemCoreClock / 1000000);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break;
        }
    }
}

/**
 * @brief 毫秒级延时
 */
void delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}
