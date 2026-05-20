#include "bsp.h"
#include "bsp_usart.h"
#include "lcd.h"
#include "touch.h"
#include "bsp_adc.h"
#include "bsp_time.h" // Add bsp_time.h include
#include "bsp_dac.h"
#include "driver_w25qxx_basic.h"

#include "elog.h" //特别拿到最前面初始化

/**
 * @brief 硬件抽象层初始化 (板级支持包初始化)
 */
void BSP_Init(void)
{
    /* 初始化微秒级定时器 */
    bsp_time_init();

    /* 初始化串口 */
    BSP_USART_Init();

    /* 初始化 EasyLogger */
    elog_init();
    /* 启动 EasyLogger */
    elog_start();
    
    /* 初始化 LCD */
    lcd_init();

    /* 初始化触摸屏 */
    tp_init();
    log_i("tp_init done");

    /* 初始化 W25Q128 Flash */
    w25qxx_basic_init(W25Q128, W25QXX_INTERFACE_SPI, W25QXX_BOOL_FALSE);
    log_i("w25qxx_basic_init done");

    /* 初始化 ADC 采样 (1Msps) */
    bsp_adc_init();
    log_i("bsp_adc_init done");

    /* 初始化 DAC 输出 */
    bsp_dac_init();
    log_i("bsp_dac_init done");

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
