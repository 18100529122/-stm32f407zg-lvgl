#include "app_data_fft.h"
#include "arm_math.h"
#include <string.h>
#include <stdio.h>

fft_result_t g_fft_result;

/* 实例结构体和计算大缓存均放在片内 SRAM */
static arm_rfft_fast_instance_f32 fft_instance;
static float32_t fft_input_buf[FFT_LENGTH];
static float32_t fft_output_buf[FFT_LENGTH];

/* 预计算的 50Hz~500Hz Bin 索引 (Fs=100kHz, N=2048, Bin_Res≈48.828Hz) */
static uint16_t s_freq_bin_idx[FREQ_COMP_NUM];

/**
 * @brief 使用 arm_math 库进行实数 FFT 计算
 */
void app_data_fft_compute(float32_t *input_data, uint32_t length)
{
	if (length > FFT_LENGTH) length = FFT_LENGTH;

	/* 1. 数据预处理 */
	arm_copy_f32(input_data, fft_input_buf, length);
	if (length < FFT_LENGTH)
	{
		memset(&fft_input_buf[length], 0, (FFT_LENGTH - length) * sizeof(float32_t));
	}

	/* 2. 去除直流分量 (减去平均值) */
	float32_t meanVal;
	arm_mean_f32(fft_input_buf, length, &meanVal);
	arm_offset_f32(fft_input_buf, -meanVal, fft_input_buf, length);

	/* 3. 执行实数 FFT */
	arm_rfft_fast_f32(&fft_instance, fft_input_buf, fft_output_buf, 0);

	/* 4. 计算复数幅值 */
	arm_cmplx_mag_f32(fft_output_buf, g_fft_result.magnitudes, FFT_LENGTH / 2);

	/* 5. 归一化 (除 DC 外所有频率点幅值乘以 2/N) */
	float32_t scale = 2.0f / FFT_LENGTH;
	arm_scale_f32(&g_fft_result.magnitudes[1], scale, &g_fft_result.magnitudes[1], FFT_LENGTH / 2 - 1);

	/* 强制 DC 为 0 以便观察交流分量 */
	g_fft_result.magnitudes[0] = 0.0f;

	/* 6. 查表提取 50Hz ~ 500Hz 频率分量 */
	for (int i = 0; i < FREQ_COMP_NUM; i++)
	{
		g_fft_result.freq_values[i] = g_fft_result.magnitudes[s_freq_bin_idx[i]];
	}
}

void app_data_fft_init(void)
{
	memset(&g_fft_result, 0, sizeof(fft_result_t));
	arm_rfft_fast_init_f32(&fft_instance, FFT_LENGTH);

	/* 预计算 50Hz~500Hz 对应的 FFT Bin 索引 */
	float32_t bin_res = 100000.0f / FFT_LENGTH;
	for (int i = 0; i < FREQ_COMP_NUM; i++)
	{
		s_freq_bin_idx[i] = (uint16_t)((50.0f * (i + 1)) / bin_res + 0.5f);
	}
}

/**
 * @brief 获取指定索引的频率分量值
 */
float app_data_fft_get_freq_value(int index)
{
	if (index >= 0 && index < FREQ_COMP_NUM)
	{
		return g_fft_result.freq_values[index];
	}
	return 0.0f;
}
