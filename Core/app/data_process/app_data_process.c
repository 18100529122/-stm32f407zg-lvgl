#include "app_data_process.h"
#include "bsp_adc_fifo.h"
#include "bsp_adc.h"
#include "app_data_fft.h"
#include "app_data_create.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cmsis_os.h"
#include "main.h"
#include "arm_math.h"
#include <stdio.h>
#include <string.h>
#include "bsp_time.h"
#include "elog.h"

app_data_result_t g_app_data_result;

/* 外部 SRAM 中的 PRPD 和 TOF 矩阵 */
static __attribute__((section(".ext_sram_data"))) uint16_t s_prpd_matrix[PRPD_AMP_BINS][PRPD_PHASE_BINS];
static __attribute__((section(".ext_sram_data"))) uint16_t s_tof_matrix[TOF_AMP_BINS][TOF_TIME_BINS];

/* FFT 输入缓冲区 (片内 SRAM) */
static float32_t f32_data[ADC_DMA_BUFF_SIZE];

static void app_data_process_task(void *argument);
static void app_data_process_update_tof(float32_t *data, uint32_t len, uint32_t base_sample_idx);
static void app_data_process_update_prpd(float32_t *data, uint32_t len, uint32_t base_sample_idx);

/**
 * @brief 数据处理任务初始化
 */
void app_data_process_init(void)
{
	app_data_fft_init();
	app_data_create_init();

	/* 初始化数据处理结果结构体中的各项参数 */
	g_app_data_result.trigger_thr_mv = 5.0f;	 /* 触发阈值设为 5.0mV，适应 0-20mV 图谱范围 */
	g_app_data_result.common_data = g_app_common_data; /* 使用公共数据的默认值 */

	g_app_data_result.adc_restart_cnt = 0;		/* 初始化 ADC 重启计数 */
	g_app_data_result.adc_sample_cnt = 0;		/* 初始化 ADC 采样点计数 */
	g_app_data_result.adc_valid_sample_cnt = 0; /* 初始化 ADC 有效采样点计数 */

	/* 将外部 SRAM 数组的地址赋值给结构体中的指针 */
	g_app_data_result.prpd_matrix_ptr = s_prpd_matrix;
	g_app_data_result.tof_matrix_ptr = s_tof_matrix;

	app_data_process_reset_tof();
	app_data_process_reset_prpd();

	/* 增加堆栈大小到 4096，防止 FFT 和 easylogger 导致溢出 */
	xTaskCreate(app_data_process_task, "adc_process", 4096, NULL, osPriorityAboveNormal, NULL);
}

/**
 * @brief 重置飞行图谱矩阵
 */
void app_data_process_reset_tof(void)
{
	memset(g_app_data_result.tof_matrix_ptr, 0, sizeof(s_tof_matrix));
	g_app_data_result.tof_point_cnt = 0;
	g_app_data_result.last_pulse_sample_idx = 0;
}

/**
 * @brief 重置PRPD图谱矩阵
 */
void app_data_process_reset_prpd(void)
{
	memset(g_app_data_result.prpd_matrix_ptr, 0, sizeof(s_prpd_matrix));
	g_app_data_result.prpd_point_cnt = 0;
}

/**
 * @brief 获取数据处理结果
 * @return app_data_result_t 数据处理结果
 */
app_data_result_t *app_data_process_get_result(void)
{
	return &g_app_data_result;
}

/**
 * @brief 增加 ADC 重启计数
 */
void app_data_process_inc_adc_restart_cnt(void)
{
	g_app_data_result.adc_restart_cnt++;
}

void app_data_process_inc_adc_sample_cnt(uint32_t add)
{
	g_app_data_result.adc_sample_cnt += add;
}

// char *app_data_process_get_rms_str(void)
// {
// 	static char rms_data[10];
// 	snprintf(rms_data, sizeof(rms_data), "%.2f", g_app_data_result.rms);
// 	return rms_data;
// }

/**
 * @brief 数据处理任务主体
 */
static void app_data_process_task(void *argument)
{
	/* 启动 ADC 采样 (此时任务已启动，可以接收信号量) */
	osDelay(500);
	bsp_adc_start();

	while (1)
	{
		if (xSemaphoreTake(g_adc_data_sem, portMAX_DELAY) == pdTRUE)
		{
			bsp_adc_fifo_t *fifo = bsp_adc_get_fifo_dev();
			uint8_t r_idx = fifo->read_idx;

			/* 检查是否有未处理 of 已满块 */
			while (fifo->status[r_idx].is_full)
			{
				/* 记录当前时间戳 */
				g_app_data_result.start_time = bsp_time_get_us();

				/* 1. 批量转换为浮点数 */
				for (uint32_t i = 0; i < ADC_DMA_BUFF_SIZE; i++)
				{
					f32_data[i] = (float32_t)fifo->data[r_idx][i];
				}

				/* 2. 执行 FFT 计算 */
				app_data_fft_compute(f32_data, ADC_DMA_BUFF_SIZE);

				uint32_t current_base_sample_idx = g_app_data_result.adc_valid_sample_cnt;
				g_app_data_result.adc_valid_sample_cnt += ADC_DMA_BUFF_SIZE;  // 有效采样点计数

				/* 3. 直接使用 float32_t 数据进行峰值和 RMS 计算 */
				float32_t current_max_val = 0;
				uint32_t max_idx = 0;
				arm_max_f32(f32_data, ADC_DMA_BUFF_SIZE, &current_max_val, &max_idx);
				g_app_data_result.common_data.peak = current_max_val;

				/* 使用 CMSIS-DSP 库计算有效值 (RMS) */
				arm_rms_f32(f32_data, ADC_DMA_BUFF_SIZE, &g_app_data_result.common_data.rms);

				/* 更新频率分量 (50Hz 和 100Hz) */
				g_app_data_result.common_data.freq_50hz = app_data_fft_get_freq_value(0);
				g_app_data_result.common_data.freq_100hz = app_data_fft_get_freq_value(1);

				/* 更新 ADC 波形数据 (用于 UI 显示) */
				/* 100kHz 采样下，每 4 个点抽取 1 个点，显示前 512 个点 (约 5.12ms) */
				for (uint32_t i = 0; i < ADC_WAVE_SIZE; i++)
				{
					g_app_data_result.adc_wave[i] = fifo->data[r_idx][i * 4];
				}

				/* 更新飞行图谱 (ToF) */
				app_data_process_update_tof(f32_data, ADC_DMA_BUFF_SIZE, current_base_sample_idx);

				/* 更新PRPD图谱 */
				app_data_process_update_prpd(f32_data, ADC_DMA_BUFF_SIZE, current_base_sample_idx);

				/* 当累计采样点数超过 flight_period 个工频周期时，只重置飞行图（滑动窗口）
				PRPD图保持累计以形成稳定的相位分布模式，用于缺陷类型识别
				*/
				uint32_t flight_period = (g_app_data_result.common_data.flight_cycle == 0) ? 2 : 
										(g_app_data_result.common_data.flight_cycle == 1) ? 5 : 10;
				if (g_app_data_result.adc_valid_sample_cnt >= flight_period * 20000)
				{
					app_data_process_reset_tof();
					app_data_process_reset_prpd();
					g_app_data_result.adc_valid_sample_cnt = 0;	 // 重置计数
				}

				/* 清除该块的已满标志 */
				fifo->status[r_idx].is_full = 0;

				/* 移动读取索引 */
				r_idx = (r_idx + 1) % ADC_FIFO_NUM;
				fifo->read_idx = r_idx;

				/* 记录当前时间戳 */
				g_app_data_result.end_time = bsp_time_get_us();
			}
		}
	}
}

/**
 * @brief 更新飞行图谱统计矩阵
 * @param data ADC 原始数据 (抽点后)
 * @param len 数据长度
 */
static void app_data_process_update_tof(float32_t *data, uint32_t len, uint32_t base_sample_idx)
{
	uint32_t flight_period = (g_app_data_result.common_data.flight_cycle == 0) ? 2 : 
	                         (g_app_data_result.common_data.flight_cycle == 1) ? 5 : 10;
	for (uint32_t i = 0; i < len; i++)
	{
		/* 转换为 mV (ADC 12bit, 3.3V基准)
		   预计算常量: 3300.0f / 4096.0f * 0.005f = 0.0040283203125f
		   或者简化为 3.3f * 0.005f / 4096.0f = 0.0165f / 4096.0f
		   实际: 0.0040283203f
		   这里使用 0.0040283203f
		 */
		float32_t mv = data[i] * 0.0040283203f;

		/* 脉冲峰值检测：
		   1. 超过阈值 trigger_thr_mv
		   2. 局部最大值 (当前值 > 前一个值 且 当前值 >= 后一个值)
		*/
		if (mv > g_app_data_result.trigger_thr_mv)
		{
			/* 边界处理：忽略块两端的极值以简化逻辑，或使用持久化状态 */
			if (i > 0 && i < len - 1)
			{
				if (data[i] > data[i - 1] && data[i] >= data[i + 1])
				{
					/* 检测到有效脉冲峰值 */

					/* 计算时间索引 (映射到 flight_period 个工频周期) */
					uint32_t total_tof_samples = SAMPLES_PER_50HZ_CYCLE * flight_period;
					int time_idx = ((base_sample_idx + i) % total_tof_samples) / (total_tof_samples / TOF_TIME_BINS);

					/* 映射到幅值矩阵索引 (0-20mV -> 40 bins, 0.5mV/bin) */
					int amp_idx = (int)(mv * 2.0f);	 // mv / 0.5f 等价于 mv * 2.0f

					if (amp_idx < TOF_AMP_BINS && time_idx < TOF_TIME_BINS)
					{
						/* 增加计数，限制最大值为 65535 */
						if (g_app_data_result.tof_matrix_ptr[amp_idx][time_idx] < 65535)
						{
							g_app_data_result.tof_matrix_ptr[amp_idx][time_idx]++;
							g_app_data_result.tof_point_cnt++;
						}
						else
						{
							/* 计数溢出，重置矩阵 */
							app_data_process_reset_tof();
						}
					}
					/* 更新上一个脉冲的时间戳 (保留用于其他可能的统计) */
					g_app_data_result.last_pulse_sample_idx = base_sample_idx + i;
				}
			}
		}
	}
}

/**
 * @brief 更新PRPD图谱统计矩阵
 * @param data ADC 原始数据 (抽点后)
 * @param len 数据长度
 */
static void app_data_process_update_prpd(float32_t *data, uint32_t len, uint32_t base_sample_idx)
{
	for (uint32_t i = 0; i < len; i++)
	{
		float32_t mv = data[i] * 0.0040283203f;	 // 转换为 mV (同 tof 转换方式)

		/* 脉冲峰值检测 (同 tof 逻辑) */
		if (mv > g_app_data_result.trigger_thr_mv)
		{
			if (i > 0 && i < len - 1)
			{
				if (data[i] > data[i - 1] && data[i] >= data[i + 1])
				{
					/* 检测到有效脉冲峰值 */

					/* 计算相位索引 (采样率 100,000Hz, 工频 50Hz -> 每周期 2000 个点) */
					/* 映射到 PRPD_PHASE_BINS 个相位区间 */
					uint32_t sample_offset_equivalent = (uint32_t)(g_app_data_result.common_data.phase_offset * (SAMPLES_PER_50HZ_CYCLE / 360.0f));
					int adjusted_sample_pos = ((base_sample_idx + i) % SAMPLES_PER_50HZ_CYCLE + sample_offset_equivalent) % SAMPLES_PER_50HZ_CYCLE;
					int phase_idx = adjusted_sample_pos / (SAMPLES_PER_50HZ_CYCLE / PRPD_PHASE_BINS);

					/* 映射到幅值矩阵索引 (0-20mV -> PRPD_AMP_BINS bins, 0.5mV/bin) */
					int amp_idx = (int)(mv * 2.0f);	 // mv / 0.5f 等价于 mv * 2.0f

					if (amp_idx < PRPD_AMP_BINS && phase_idx < PRPD_PHASE_BINS)
					{
						/* 增加计数，限制最大值为 65535 */
						if (g_app_data_result.prpd_matrix_ptr[amp_idx][phase_idx] < 65535)
						{
							g_app_data_result.prpd_matrix_ptr[amp_idx][phase_idx]++;
							g_app_data_result.prpd_point_cnt++;
						}
						else
						{
							/* 计数溢出，重置矩阵 */
							app_data_process_reset_prpd();
						}
					}
				}
			}
		}
	}
}
