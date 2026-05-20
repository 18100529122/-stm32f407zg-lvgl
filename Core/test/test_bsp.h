#ifndef __TEST_BSP_H
#define __TEST_BSP_H

#include "main.h"

/**
  * @brief 外部 SRAM 测试函数 (通过绝对地址访问)
  */
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

#endif /* __TEST_BSP_H */
