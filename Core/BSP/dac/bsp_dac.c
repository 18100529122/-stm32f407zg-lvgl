#include "bsp_dac.h"
#include "dac.h"
#include <math.h>
#include <stdlib.h>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

uint16_t g_dac_buff[DAC_BUFF_SIZE];

/**
 * @brief 添加PD脉冲到正弦波
 * @param pd_phase 脉冲相位 (0-360度)
 * @param pd_amplitude 脉冲幅度 (mV，叠加在正弦波上)
 */
static void add_pd_pulse(int pd_phase, float pd_amplitude)
{
	/* 将相位转换为缓冲区索引 */
	int pd_idx = (pd_phase * DAC_BUFF_SIZE) / 360;
	
	/* 转换mV到ADC计数值 (3.3V/4096 = 0.80566mV/LSB) */
	float pd_count = pd_amplitude / 0.80566f;
	
	/* 添加窄脉冲（10个点宽） */
	for (int j = -5; j <= 5; j++)
	{
		int idx = (pd_idx + j + DAC_BUFF_SIZE) % DAC_BUFF_SIZE;
		/* 使用高斯脉冲形状，让脉冲看起来更自然 */
		float pulse_shape = expf(-(float)(j * j) / 4.0f);
		g_dac_buff[idx] += (uint16_t)(pd_count * pulse_shape);
	}
}

/**
 * @brief 配置并启动 DAC 输出带PD脉冲的正弦波
 * @param frequency 目标频率 (Hz)
 * @param pd_phase1 PD脉冲相位1 (0-360度，对应正半周)
 * @param pd_phase2 PD脉冲相位2 (0-360度，对应负半周)
 * @param pd_amplitude PD脉冲幅度 (mV)
 * @param pd_enabled 是否启用PD脉冲 (0=禁用，1=启用)
 */
void bsp_dac_set_pd_wave(uint32_t frequency, float pd_phase1, float pd_phase2, float pd_amplitude, uint8_t pd_enabled)
{
	/* 1. 生成基础正弦波数据表 (0 - 4095) */
	for (int i = 0; i < DAC_BUFF_SIZE; i++)
	{
		/* 1.65V 偏置，约 1.5V 幅值的正弦波 (避免满量程削波) */
		float sine_val = (sinf(2.0f * PI * i / DAC_BUFF_SIZE) + 1.0f) * 2047.0f * 0.9f + 200.0f;

		/* 增加随机噪声模拟真实环境 (约 +/- 8mV 的抖动) */
		int16_t noise = (int16_t)((rand() % 21) - 10);

		g_dac_buff[i] = (uint16_t)(sine_val + (float)noise);
	}
	
	/* 2. 如果启用，添加PD脉冲 */
	if (pd_enabled)
	{
		add_pd_pulse((int)pd_phase1, pd_amplitude);
		add_pd_pulse((int)pd_phase2, pd_amplitude);
	}

	/* 3. 配置定时器 6 (TIM6) 作为触发源 */
	__HAL_RCC_TIM6_CLK_ENABLE();

	/* 定时器触发频率 = 目标频率 * 缓冲区点数 */
	/* F407 APB1 Timer 时钟频率为 84MHz */
	uint32_t pclk1_timer = HAL_RCC_GetPCLK1Freq() * 2;
	uint32_t arr = pclk1_timer / (frequency * DAC_BUFF_SIZE) - 1;

	TIM6->PSC = 0;
	TIM6->ARR = arr;
	TIM6->CR2 &= ~TIM_CR2_MMS;
	TIM6->CR2 |= TIM_TRGO_UPDATE; /* 更新事件触发 TRGO */
	TIM6->CR1 |= TIM_CR1_CEN;	  /* 开启定时器 */

	/* 4. 配置 DAC 为定时器触发模式 */
	HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);

	DAC_ChannelConfTypeDef sConfig = {0};
	sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO; /* 使用 TIM6 触发 */
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1);

	/* 5. 启动 DMA 循环输出 */
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)g_dac_buff, DAC_BUFF_SIZE, DAC_ALIGN_12B_R);
}

/**
 * @brief 配置并启动 DAC 输出指定频率的正弦波
 * @param frequency 目标频率 (Hz)
 */
void bsp_dac_set_sine_wave(uint32_t frequency)
{
	bsp_dac_set_pd_wave(frequency, 90.0f, 270.0f, 10.0f, 0);
}

/**
 * @brief 初始化DAC并开启DMA输出
 */
void bsp_dac_init(void)
{
	/* 默认初始化为带PD脉冲的50Hz正弦波，用于测试 */
	/* 内部放电模式：90度和270度有脉冲，10mV幅度 */
	bsp_dac_set_pd_wave(50, 90.0f, 270.0f, 10.0f, 1);
}

/**
 * @brief 设置DAC输出值 (0-4095)
 */
void bsp_dac_set_value(uint16_t value)
{
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
}
