#include "app_data_create.h"
#include "bsp_dac.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "elog.h"

static void app_data_create_task(void *argument);

/**
 * @brief 初始化信号生成任务
 */
void app_data_create_init(void)
{
	xTaskCreate(app_data_create_task, "dac_cycle", 512, NULL, osPriorityNormal, NULL);
}

/**
 * @brief PD模式切换任务主体
 */
static void app_data_create_task(void *argument)
{
	uint8_t test_mode = 0;

	while (1)
	{
		switch (test_mode)
		{
			case 0:
				/* 模式1：内部放电 (Internal Discharge) */
				/* 特点：正半周90度和负半周270度有脉冲，形成三角形模式 */
				bsp_dac_set_pd_wave(50, 90.0f, 270.0f, 12.0f, 1);
				log_i("Mode 1: Internal Discharge (90+270 degrees, 12mV)\r\n");
				break;
				
			case 1:
				/* 模式2：表面放电 (Surface Discharge) */
				/* 特点：正半周脉冲分布较宽，负半周也有脉冲 */
				bsp_dac_set_pd_wave(50, 60.0f, 240.0f, 8.0f, 1);
				log_i("Mode 2: Surface Discharge (60+240 degrees, 8mV)\r\n");
				break;
				
			case 2:
				/* 模式3：电晕放电 (Corona Discharge) */
				/* 特点：只在正半周峰值附近有脉冲 */
				bsp_dac_set_pd_wave(50, 90.0f, 90.0f, 15.0f, 1);
				log_i("Mode 3: Corona Discharge (only 90 degrees, 15mV)\r\n");
				break;
				
			case 3:
				/* 模式4：无PD (正常状态) */
				bsp_dac_set_pd_wave(50, 90.0f, 270.0f, 10.0f, 0);
				log_i("Mode 4: No PD (Normal)\r\n");
				break;
				
			case 4:
				/* 模式5：多脉冲模式 */
				/* 特点：多个不同幅度的脉冲 */
				bsp_dac_set_pd_wave(50, 45.0f, 225.0f, 6.0f, 1);
				log_i("Mode 5: Multi-pulse (45+225 degrees, 6mV)\r\n");
				break;
		}

		/* 切换到下一个模式 */
		test_mode++;
		if (test_mode > 4)
		{
			test_mode = 0;
		}

		/* 每个模式持续 15 秒，让你有足够时间观察图谱 */
		osDelay(5000);
	}
}
