#include "test_bsp.h"
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "touch.h"
#include "driver_w25qxx_basic.h"


#ifndef TEST_SRAM_DEBUG
#define TEST_SRAM_DEBUG 0
#endif

#if TEST_SRAM_DEBUG

/* 避开 LVGL 使用的区域 (0x68000000 - 0x68070000) */
#define EXT_SRAM_ADDR    ((uint32_t)0x68070000)
#define EXT_SRAM_SIZE    (576 * 1024) // 剩余 576KB

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
 * @brief LCD 显示测试
 */
void LCD_Test(void)
{
    printf("--- LCD Test Start ---\n");
    printf("LCD ID: 0x%04X\n", lcddev.id);
    printf("LCD Width: %u, Height: %u\n", lcddev.width, lcddev.height);

    // 0. 设置显示方向
    printf("Setting display direction...\n");
    lcd_display_dir(1);
    lcd_scan_dir(3);

    // 1. 清屏测试
    printf("Clearing screen to WHITE...\n");
    lcd_clear(WHITE);
    HAL_Delay(500);

    // 2. 画点测试
    printf("Drawing points...\n");
    for (uint16_t i = 0; i < 100; i++)
    {
        lcd_draw_point(100 + i, 100 + i, RED);
    }

    // 3. 画线测试
    printf("Drawing lines...\n");
    lcd_draw_line(0, 0, lcddev.width - 1, lcddev.height - 1, GREEN);
    lcd_draw_line(lcddev.width - 1, 0, 0, lcddev.height - 1, GREEN);

    // 4. 文字显示测试
    printf("Showing strings...\n");
    lcd_show_string(10, 10, 200, 32, 32, "STM32F407 LCD TEST", BLACK);
    lcd_show_string(10, 60, 200, 32, 32, "By Gemini Code Assistant", BLACK);

    printf("--- LCD Test End ---\n");
}

/**
 * @brief W25QXX SPI Flash 测试
 */
void W25QXX_Test(void)
{
    uint8_t res;
    uint8_t manufacturer, device_id;
    uint8_t test_data[32] = "LibDriver W25Q128 Test Data";
    uint8_t read_buf[32];

    printf("--- W25Q128 Test Start ---\n");

    /* 1. 驱动已在 BSP_Init 中初始化，这里直接测试 */

    /* 2. 获取芯片 ID */
    res = w25qxx_basic_get_id(&manufacturer, &device_id);
    if (res != 0)
    {
        printf("Get ID Failed!\n");
    }
    else
    {
        printf("Manufacturer: 0x%02X, Device ID: 0x%02X (Expected: 0xEF, 0x17)\n", manufacturer, device_id);
    }
    
    /* 3. 读写测试 */
    printf("Writing test data to address 0x000000...\n");
    res = w25qxx_basic_write(0x000000, test_data, sizeof(test_data));
    if (res != 0)
    {
        printf("Write Failed!\n");
    }
    else
    {
        printf("Write Success.\n");
    }

    printf("Reading data from address 0x000000...\n");
    res = w25qxx_basic_read(0x000000, read_buf, sizeof(read_buf));
    if (res != 0)
    {
        printf("Read Failed!\n");
    }
    else
    {
        printf("Read Data: %s\n", (char *)read_buf);
        
        /* 验证数据 */
        if (memcmp(test_data, read_buf, sizeof(test_data)) == 0)
        {
            printf("W25Q128 Data Verification PASSED!\n");
        }
        else
        {
            printf("W25Q128 Data Verification FAILED! (Did you erase the sector first?)\n");
        }
    }

    printf("--- W25Q128 Test End ---\n");
}

/**
 * @brief 触摸屏扫描测试
 */
void Touch_Test(void)
{
    tp_dev.scan(0);
    if (tp_dev.sta & TP_PRES_DOWN)
    {
        if (tp_dev.touchtype & 0x80) // 电容屏
        {
            for (int i = 0; i < CT_MAX_TOUCH; i++)
            {
                if ((tp_dev.sta >> i) & 0x01)
                {
                    printf("Touch Point %d: X=%d, Y=%d\r\n", i, tp_dev.x[i], tp_dev.y[i]);
                }
            }
        }
        else // 电阻屏
        {
            printf("Touch Point: X=%d, Y=%d\r\n", tp_dev.x[0], tp_dev.y[0]);
        }
    }
}


/**
 * @brief 测试BSP函数，包含SRAM_Test和SRAM_Section_Test
 */
void Test_BSP(void)
{
#if TEST_SRAM_DEBUG
    SRAM_Test();     //test SRAM access
    SRAM_Section_Test();//test SRAM section
#endif

    // LCD_Test();      // test LCD
    W25QXX_Test();   // test W25QXX SPI Flash

    printf("Test_BSP done!\n");
}
