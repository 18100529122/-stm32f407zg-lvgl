#ifndef __BSP_H
#define __BSP_H

#include "main.h"

/**
 * @brief 硬件抽象层初始化 (板级支持包初始化)
 */
void BSP_Init(void);

/**
 * @brief 微秒级延时
 * @param us 延时时长
 */
void delay_us(uint32_t us);

/**
 * @brief 毫秒级延时
 * @param ms 延时时长
 */
void delay_ms(uint32_t ms);

#endif /* __BSP_H */
