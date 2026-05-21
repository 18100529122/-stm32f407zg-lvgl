#include "app_data_create.h"
#include "bsp_dac.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>

static void app_data_create_task(void *argument);

/**
 * @brief 初始化信号生成任务
 */
void app_data_create_init(void)
{
	xTaskCreate(app_data_create_task, "dac_cycle", 512, NULL, osPriorityNormal, NULL);
}

/**
 * @brief 频率切换任务主体 (每3秒改变一次频率)
 */
static void app_data_create_task(void *argument)
{
	uint16_t test_freq = 50;

	while (1)
	{
		/* 设置 DAC 输出频率 */
		bsp_dac_set_sine_wave(test_freq);

		/* 增加频率步进 (50Hz - 100Hz) */
		test_freq += 50;
		if (test_freq > 100)
		{
			test_freq = 50;
		}

		/* 延迟 10s */
		osDelay(10000);
	}
}
