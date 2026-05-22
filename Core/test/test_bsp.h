#ifndef __TEST_BSP_H
#define __TEST_BSP_H

#include "main.h"

/**
 * @brief 测试BSP函数，包含SRAM_Test, SRAM_Section_Test 和 LCD_Test
 */
void Test_BSP(void);

/**
 * @brief LCD 显示测试
 */
void LCD_Test(void);

/**
 * @brief W25QXX SPI Flash 测试
 */
void W25QXX_Test(void);

/**
 * @brief EasyFlash 测试
 */
void EasyFlash_Test(void);

#endif /* __TEST_BSP_H */
