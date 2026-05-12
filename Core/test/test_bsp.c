#include "test_bsp.h"
#include <stdio.h>


#ifndef TEST_SRAM_DEBUG
#define TEST_SRAM_DEBUG 0
#endif

#if TEST_SRAM_DEBUG

#define EXT_SRAM_ADDR    ((uint32_t)0x68000000)
#define EXT_SRAM_SIZE    (1024 * 1024) // 1MB

void SRAM_Test(void)
{
    uint32_t i;
    uint32_t err_count = 0;
    uint16_t read_val;
    
    printf("--- External SRAM Test Start ---\n");
    printf("Address: 0x%08X, Size: 1MB\n", (unsigned int)EXT_SRAM_ADDR);

    // 1. 写入测试数据
    printf("Writing data...\n");
    for (i = 0; i < EXT_SRAM_SIZE / 2; i++)
    {
        *(__IO uint16_t *)(EXT_SRAM_ADDR + i * 2) = (uint16_t)(i & 0xFFFF);
    }

    // 2. 读取并验证
    printf("Verifying data...\n");
    for (i = 0; i < EXT_SRAM_SIZE / 2; i++)
    {
        read_val = *(__IO uint16_t *)(EXT_SRAM_ADDR + i * 2);
        if (read_val != (uint16_t)(i & 0xFFFF))
        {
            if (err_count < 10) // 只打印前10个错误
            {
                printf("Error at 0x%08X: Write 0x%04X, Read 0x%04X\n", 
                       (unsigned int)(EXT_SRAM_ADDR + i * 2), (unsigned int)(i & 0xFFFF), (unsigned int)read_val);
            }
            err_count++;
        }
    }

    if (err_count == 0)
    {
        printf("External SRAM Test PASSED!\n");
    }
    else
    {
        printf("External SRAM Test FAILED! Total errors: %u\n", (unsigned int)err_count);
    }
    printf("--- External SRAM Test End ---\n");
}

/* 定义变量到外部 SRAM 段 */
uint8_t my_buffer[1024] __attribute__((section(".ext_sram")));
uint32_t my_counter __attribute__((section(".ext_sram")));

void SRAM_Section_Test(void)
{
    printf("--- External SRAM Section Test Start ---\n");
    
    // 检查变量地址是否在外部 SRAM 范围内 (0x68000000)
    printf("my_buffer addr: 0x%08X\n", (unsigned int)my_buffer);
    printf("my_counter addr: 0x%08X\n", (unsigned int)&my_counter);

    if (((uint32_t)my_buffer & 0xF0000000) != 0x60000000)
    {
        printf("Error: Variables are NOT in External SRAM range!\n");
        return;
    }

    // 测试读写
    my_counter = 0x12345678;
    for (int i = 0; i < 1024; i++)
    {
        my_buffer[i] = (uint8_t)(i & 0xFF);
    }

    // 验证
    uint32_t err_count = 0;
    if (my_counter != 0x12345678) err_count++;
    for (int i = 0; i < 1024; i++)
    {
        if (my_buffer[i] != (uint8_t)(i & 0xFF)) err_count++;
    }

    if (err_count == 0)
    {
        printf("SRAM Section Test PASSED!\n");
    }
    else
    {
        printf("SRAM Section Test FAILED! Errors: %u\n", (unsigned int)err_count);
    }
    printf("--- External SRAM Section Test End ---\n");
}

#endif


/**
 * @brief 测试BSP函数，包含SRAM_Test和SRAM_Section_Test
 */
void Test_BSP(void)
{
#if TEST_SRAM_DEBUG
    SRAM_Test();     //test SRAM access
    SRAM_Section_Test();//test SRAM section
#endif

    printf("Test_BSP done!\n");
}
