/**
 ****************************************************************************************************
 * @file        touch.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.1
 * @date        2023-05-29
 * @brief       触摸屏 驱动代码 (仅支持电容屏 GT9xxx)
 ****************************************************************************************************
 */

#include "stdio.h"
#include "stdlib.h"
#include "lcd.h"
#include "touch.h"
#include "bsp.h"
#include "gt9xxx.h"

_m_tp_dev tp_dev =
{
    tp_init,
    gt9xxx_scan,
    {0},
    {0},
    0,
    0x80,   /* 默认电容屏 */
};

/**
 * @brief       触摸屏初始化
 * @param       无
 * @retval      0, 成功; 1, 失败
 */
uint8_t tp_init(void)
{
    /* 针对 ID 为 0x9806 的屏幕，直接初始化 GT9xxx */
    if (gt9xxx_init() == 0)
    {
        tp_dev.scan = gt9xxx_scan;
        tp_dev.touchtype |= 0X80;   /* 电容屏标记 */
        return 0;
    }
    
    return 1;
}
