#include "test_bsp.h"
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "touch.h"
#include "driver_w25qxx_basic.h"
#include "elog.h"
#include "easyflash.h"


#ifndef TEST_SRAM_DEBUG
#define TEST_SRAM_DEBUG 0
#endif

#if TEST_SRAM_DEBUG

/* 避开 LVGL 使用的区域 (0x68000000 - 0x68070000) */
#define EXT_SRAM_ADDR ((uint32_t)0x68070000)
#define EXT_SRAM_SIZE (576 * 1024) // 剩余 576KB

void SRAM_Test(void)
{
	uint32_t i;
	uint32_t err_count = 0;
	uint16_t read_val;

	log_i("--- External SRAM Test Start ---\n");
	log_i("Address: 0x%08X, Size: 1MB\n", (unsigned int)EXT_SRAM_ADDR);

	// 1. 写入测试数据
	log_i("Writing data...\n");
	for (i = 0; i < EXT_SRAM_SIZE / 2; i++)
	{
		*(__IO uint16_t *)(EXT_SRAM_ADDR + i * 2) = (uint16_t)(i & 0xFFFF);
	}

	// 2. 读取并验证
	log_i("Verifying data...\n");
	for (i = 0; i < EXT_SRAM_SIZE / 2; i++)
	{
		read_val = *(__IO uint16_t *)(EXT_SRAM_ADDR + i * 2);
		if (read_val != (uint16_t)(i & 0xFFFF))
		{
			if (err_count < 10) // 只打印前10个错误
			{
				log_i("Error at 0x%08X: Write 0x%04X, Read 0x%04X\n", (unsigned int)(EXT_SRAM_ADDR + i * 2), (unsigned int)(i & 0xFFFF), (unsigned int)read_val);
			}
			err_count++;
		}
	}

	if (err_count == 0)
	{
		log_i("External SRAM Test PASSED!\n");
	}
	else
	{
		log_i("External SRAM Test FAILED! Total errors: %u\n", (unsigned int)err_count);
	}
	log_i("--- External SRAM Test End ---\n");
}

/* 定义变量到外部 SRAM 段 */
uint8_t my_buffer[1024] __attribute__((section(".ext_sram")));
uint32_t my_counter __attribute__((section(".ext_sram")));

void SRAM_Section_Test(void)
{
	log_i("--- External SRAM Section Test Start ---\n");

	// 检查变量地址是否在外部 SRAM 范围内 (0x68000000)
	log_i("my_buffer addr: 0x%08X\n", (unsigned int)my_buffer);
	log_i("my_counter addr: 0x%08X\n", (unsigned int)&my_counter);

	if (((uint32_t)my_buffer & 0xF0000000) != 0x60000000)
	{
		log_i("Error: Variables are NOT in External SRAM range!\n");
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
		log_i("SRAM Section Test PASSED!\n");
	}
	else
	{
		log_i("SRAM Section Test FAILED! Errors: %u\n", (unsigned int)err_count);
	}
	log_i("--- External SRAM Section Test End ---\n");
}

#endif

/**
 * @brief LCD 显示测试
 */
void LCD_Test(void)
{
	log_i("--- LCD Test Start ---\n");
	log_i("LCD ID: 0x%04X\n", lcddev.id);
	log_i("LCD Width: %u, Height: %u\n", lcddev.width, lcddev.height);

	// 0. 设置显示方向
	log_i("Setting display direction...\n");
	lcd_display_dir(1);
	lcd_scan_dir(3);

	// 1. 清屏测试
	log_i("Clearing screen to WHITE...\n");
	lcd_clear(WHITE);
	HAL_Delay(500);

	// 2. 画点测试
	log_i("Drawing points...\n");
	for (uint16_t i = 0; i < 100; i++)
	{
		lcd_draw_point(100 + i, 100 + i, RED);
	}

	// 3. 画线测试
	log_i("Drawing lines...\n");
	lcd_draw_line(0, 0, lcddev.width - 1, lcddev.height - 1, GREEN);
	lcd_draw_line(lcddev.width - 1, 0, 0, lcddev.height - 1, GREEN);

	// 4. 文字显示测试
	log_i("Showing strings...\n");
	lcd_show_string(10, 10, 200, 32, 32, "STM32F407 LCD TEST", BLACK);
	lcd_show_string(10, 60, 200, 32, 32, "By Gemini Code Assistant", BLACK);

	log_i("--- LCD Test End ---\n");
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

	log_i("--- W25Q128 Test Start ---\n");

	/* 1. 驱动已在 BSP_Init 中初始化，这里直接测试 */

	/* 2. 获取芯片 ID */
	res = w25qxx_basic_get_id(&manufacturer, &device_id);
	if (res != 0)
	{
		log_i("Get ID Failed!\n");
	}
	else
	{
		log_i("Manufacturer: 0x%02X, Device ID: 0x%02X (Expected: 0xEF, 0x17)\n", manufacturer, device_id);
	}

	/* 3. 读写测试 */
	log_i("Writing test data to address 0x000000...\n");
	res = w25qxx_basic_write(0x000000, test_data, sizeof(test_data));
	if (res != 0)
	{
		log_i("Write Failed!\n");
	}
	else
	{
		log_i("Write Success.\n");
	}

	log_i("Reading data from address 0x000000...\n");
	res = w25qxx_basic_read(0x000000, read_buf, sizeof(read_buf));
	if (res != 0)
	{
		log_i("Read Failed!\n");
	}
	else
	{
		log_i("Read Data: %s\n", (char *)read_buf);

		/* 验证数据 */
		if (memcmp(test_data, read_buf, sizeof(test_data)) == 0)
		{
			log_i("W25Q128 Data Verification PASSED!\n");
		}
		else
		{
			log_i("W25Q128 Data Verification FAILED! (Did you erase the sector first?)\n");
		}
	}

	log_i("--- W25Q128 Test End ---\n");
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
					log_i("Touch Point %d: X=%d, Y=%d\r\n", i, tp_dev.x[i], tp_dev.y[i]);
				}
			}
		}
		else // 电阻屏
		{
			log_i("Touch Point: X=%d, Y=%d\r\n", tp_dev.x[0], tp_dev.y[0]);
		}
	}
}


/**
 * @brief EasyFlash 测试
 */
void EasyFlash_Test(void)
{
    log_i("--- EasyFlash Test Start ---\n");

    /* 1. 设置字符串环境变量 */
    const char *str_key = "hello_easyflash";
    const char *str_value = "Hello from EasyFlash!";
    ef_set_env(str_key, str_value);
    log_i("Set string env '%s' = '%s'\n", str_key, str_value);

    /* 2. 获取并验证字符串环境变量 */
    char *read_str_value = ef_get_env(str_key);
    if (read_str_value != NULL)
    {
        log_i("Get string env '%s' = '%s'\n", str_key, read_str_value);
        if (strcmp(read_str_value, str_value) == 0)
        {
            log_i("String env verification PASSED!\n");
        }
        else
        {
            log_e("String env verification FAILED!\n");
        }
        // 注意：ef_get_env 返回的字符串通常指向内部缓冲区，不需要手动释放
    }
    else
    {
        log_e("Failed to get string env '%s'\n", str_key);
    }

    /* 3. 设置 blob (二进制) 环境变量 */
    typedef struct {
        uint32_t magic;
        float temperature;
        char name[16];
    } my_data_t;

    my_data_t write_blob_data = {
        .magic = 0xDEADBEEF,
        .temperature = 25.5f,
        .name = "SensorData"
    };
    const char *blob_key = "sensor_data";
    ef_set_env_blob(blob_key, &write_blob_data, sizeof(my_data_t));
    log_i("Set blob env '%s' with size %u\n", blob_key, sizeof(my_data_t));

    /* 4. 获取并验证 blob 环境变量 */
    my_data_t read_blob_data;
    size_t read_len;
    size_t get_blob_result = ef_get_env_blob(blob_key, &read_blob_data, sizeof(my_data_t), &read_len);
    if (get_blob_result > 0)
    {
        log_i("Get blob env '%s': magic=0x%X, temp=%.1f, name='%s', read_len=%u\n",
              blob_key, (unsigned int)read_blob_data.magic, read_blob_data.temperature,
              read_blob_data.name, (unsigned int)read_len);
        if (memcmp(&write_blob_data, &read_blob_data, sizeof(my_data_t)) == 0)
        {
            log_i("Blob env verification PASSED!\n");
        }
        else
        {
            log_e("Blob env verification FAILED!\n");
        }
    }
    else
    {
        log_e("Failed to get blob env '%s'\n", blob_key);
    }

    /* 5. 打印所有环境变量 */
    log_i("--- All EasyFlash Environment Variables ---\n");
    ef_print_env();
    log_i("-------------------------------------------\n");

    /* 6. 删除一个环境变量 */
    ef_del_env(str_key);
    log_i("Deleted env '%s'\n", str_key);

    /* 7. 再次打印，确认删除成功 */
    log_i("--- After Deletion ---\n");
    ef_print_env();
    log_i("----------------------\n");

    log_i("--- EasyFlash Test End ---\n");
}

/**
 * @brief 测试BSP函数，包含SRAM_Test和SRAM_Section_Test
 */
void Test_BSP(void)
{
#if TEST_SRAM_DEBUG
	SRAM_Test();  // test SRAM access
	SRAM_Section_Test();// test SRAM section
#endif

	// LCD_Test();      // test LCD
	W25QXX_Test();	// test W25QXX SPI Flash
    EasyFlash_Test(); // test EasyFlash

	log_i("Test_BSP done!\n");
}

