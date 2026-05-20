/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_w25qxx_interface_template.c
 * @brief     driver w25qxx interface template source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-07-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/07/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_w25qxx_interface.h"
#include "spi.h"
#include "main.h"
#include "bsp.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * @brief  interface spi qspi bus init
 * @return status code
 *         - 0 success
 *         - 1 spi qspi init failed
 * @note   none
 */
uint8_t w25qxx_interface_spi_qspi_init(void)
{
    return 0;
}

/**
 * @brief  interface spi qspi bus deinit
 * @return status code
 *         - 0 success
 *         - 1 spi qspi deinit failed
 * @note   none
 */
uint8_t w25qxx_interface_spi_qspi_deinit(void)
{
    return 0;
}

/**
 * @brief      interface spi qspi bus write read
 * @param[in]  instruction sent instruction
 * @param[in]  instruction_line instruction phy lines
 * @param[in]  address register address
 * @param[in]  address_line address phy lines
 * @param[in]  address_len address length
 * @param[in]  alternate register address
 * @param[in]  alternate_line alternate phy lines
 * @param[in]  alternate_len alternate length
 * @param[in]  dummy dummy cycle
 * @param[in]  *in_buf pointer to a input buffer
 * @param[in]  in_len input length
 * @param[out] *out_buf pointer to a output buffer
 * @param[in]  out_len output length
 * @param[in]  data_line data phy lines
 * @return     status code
 *             - 0 success
 *             - 1 write read failed
 * @note       none
 */
uint8_t w25qxx_interface_spi_qspi_write_read(uint8_t instruction, uint8_t instruction_line,
                                             uint32_t address, uint8_t address_line, uint8_t address_len,
                                             uint32_t alternate, uint8_t alternate_line, uint8_t alternate_len,
                                             uint8_t dummy, uint8_t *in_buf, uint32_t in_len,
                                             uint8_t *out_buf, uint32_t out_len, uint8_t data_line)
{
    uint8_t temp[5];

    /* 拉低 CS */
    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
    
    /* 增加一个极小的延时，确保 CS 稳定 */
    for (volatile uint32_t i = 0; i < 10; i++);

    /* 发送指令 (仅当 instruction_line > 0 时) */
    if (instruction_line != 0)
    {
        if (HAL_SPI_Transmit(&hspi1, &instruction, 1, 1000) != HAL_OK)
        {
            HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
            return 1;
        }
    }

    /* 发送地址 (仅当 address_line > 0 且 address_len > 0 时) */
    if (address_line != 0 && address_len > 0)
    {
        if (address_len == 3)
        {
            temp[0] = (address >> 16) & 0xFF;
            temp[1] = (address >> 8) & 0xFF;
            temp[2] = (address >> 0) & 0xFF;
        }
        else if (address_len == 4)
        {
            temp[0] = (address >> 24) & 0xFF;
            temp[1] = (address >> 16) & 0xFF;
            temp[2] = (address >> 8) & 0xFF;
            temp[3] = (address >> 0) & 0xFF;
        }
        if (HAL_SPI_Transmit(&hspi1, temp, address_len, 1000) != HAL_OK)
        {
            HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
            return 1;
        }
    }

    /* 发送 alternate (仅当 alternate_line > 0 时) */
    if (alternate_line != 0 && alternate_len > 0)
    {
        temp[0] = (alternate >> 0) & 0xFF; 
        if (HAL_SPI_Transmit(&hspi1, temp, alternate_len, 1000) != HAL_OK)
        {
            HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
            return 1;
        }
    }

    /* 发送 dummy cycles (仅在 SPI 模式下，dummy 是时钟周期数，通常是 8 的倍数) */
    if (dummy > 0)
    {
        uint8_t dummy_bytes = dummy / 8;
         if (dummy_bytes == 0 && dummy > 0) dummy_bytes = 1; // 至少发送 1 字节如果是奇数位
         
         memset(temp, 0x00, sizeof(temp));
         for (uint8_t i = 0; i < dummy_bytes; i++)
        {
            if (HAL_SPI_Transmit(&hspi1, &temp[0], 1, 1000) != HAL_OK)
            {
                HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
                return 1;
            }
        }
    }

    /* 写入数据 (in_buf) */
    if (in_len > 0)
    {
        if (HAL_SPI_Transmit(&hspi1, in_buf, in_len, 1000) != HAL_OK)
        {
            HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
            return 1;
        }
    }

    /* 读取数据 (out_buf) */
    if (out_len > 0)
    {
        if (HAL_SPI_Receive(&hspi1, out_buf, out_len, 1000) != HAL_OK)
        {
            HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
            return 1;
        }
    }

    /* 拉高 CS */
    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void w25qxx_interface_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

/**
 * @brief     interface delay us
 * @param[in] us time
 * @note      none
 */
void w25qxx_interface_delay_us(uint32_t us)
{
    delay_us(us);
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void w25qxx_interface_debug_print(const char *const fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
