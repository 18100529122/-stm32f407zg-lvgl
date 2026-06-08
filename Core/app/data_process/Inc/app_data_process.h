#ifndef __APP_DATA_PROCESS_H__
#define __APP_DATA_PROCESS_H__

#include "main.h"
#include "app_data_fft.h"
#include <stdbool.h> // 添加此行以支持 bool 类型

// 假设采样率为 100kHz，工频为 50Hz
#define SAMPLES_PER_50HZ_CYCLE (100000 / 50) // 一个 50Hz 周期内的采样点数 (2000点)

/**
 * @brief 飞行图谱配置
 */
#define TOF_AMP_BINS  40  /* Y轴: 0-20mV, 每 0.5mV 一个区间 */
// TOF_TIME_BINS 的 X轴范围由 flight_period 动态决定。例如 flight_period=2，则 X轴覆盖 2T (40ms)
#define TOF_TIME_BINS 100 /* X轴: 时间周期分档数。将 (flight_period * SAMPLES_PER_50HZ_CYCLE) 映射到此分档数 */
#define ADC_WAVE_SIZE 512 /* 抽点后的 ADC 波形数据 (用于 UI 显示), 覆盖约 1T (20ms) */

/**
 * @brief PRPD图谱配置
 */
#define PRPD_PHASE_BINS 100 /* 相位轴: 0-360度, 每 3.6度 一个区间 */
#define PRPD_AMP_BINS   40  /* 幅值轴: 0-20mV, 每 0.5mV 一个区间 */


/**
 * @brief 数据处理结果结构体
 */
typedef struct
{
	/* 脉冲波形 */
	uint16_t adc_wave[ADC_WAVE_SIZE]; /* 抽点后的 ADC 波形数据 (用于 UI 显示) */

	/* PRPD图 */
	uint16_t (*prpd_matrix_ptr)[PRPD_PHASE_BINS]; /* PRPD图谱统计矩阵指针 */
	uint32_t prpd_point_cnt;							  /* PRPD图谱总点数 */


	/* 四要素值 */
	float rms;		  /* 有效值 */
	float peak;		  /* 周期最大值 */
	float freq_50hz;  /* 50Hz 分量 */
	float freq_100hz; /* 100Hz 分量 */

	/* 飞行图 */
	uint16_t (*tof_matrix_ptr)[TOF_TIME_BINS]; /* 飞行图谱统计矩阵指针 */
	uint32_t tof_point_cnt;							  /* 飞行图谱总点数 */
	uint32_t last_pulse_sample_idx;					  /* 上一个脉冲的采样点索引 */
	float trigger_thr_mv;							  /* 触发阈值(mV) */

	uint32_t adc_valid_sample_cnt; /* ADC 有效采样点计数 (自上次重置以来，用于图谱累积周期控制) */

	/* 设置参数 */
	float note_thr_mv;			  /* 注意阈值(mV) 0-70 默认20.0 */
	float alarm_thr_mv;			  /* 告警阈值(mV) 0-70 默认20.0 */
	uint32_t count_thr;			  /* 计数阈值 0-160 默认 5 */
	uint32_t phase_offset;		  /* 相位偏移 0-360 默认0 */
	bool gain_type_auto;		  /* 增益类型 true自动 false手动 默认手动 */
	uint32_t gain;				  /* 信号增益 40 60 80 默认40 */
	bool unit_select_dBuV;		  /* 单位选择 true:dBuV false:uV 默认dBuV */
	uint32_t flight_period;		  /* 飞行周期 2T 5T 10T 默认2T */
	bool channel_select_int;	  /* 通道选择 true:内置超声 false:外置超声 默认内置超声 */

	/* 统计数据 用于测试*/
	uint32_t adc_restart_cnt;	   /* ADC 重启计数 */
	uint32_t adc_sample_cnt;	   /* ADC 采样点计数 */
	uint32_t start_time;		   /* 数据处理开始时间 */
	uint32_t end_time;			   /* 数据处理结束时间 */
} app_data_result_t;

extern app_data_result_t g_app_data_result;

/**
 * @brief 数据处理任务初始化
 */
void app_data_process_init(void);

/**
 * @brief 重置飞行图谱矩阵
 */
void app_data_process_reset_tof(void);
/**
 * @brief 重置PRPD图谱矩阵
 */
void app_data_process_reset_prpd(void);
void app_data_process_inc_adc_restart_cnt(void);
void app_data_process_inc_adc_sample_cnt(uint32_t add);

/**
 * @brief 获取数据处理结果
 * @return app_data_result_t 数据处理结果
 */
app_data_result_t *app_data_process_get_result(void);


#endif /* __APP_DATA_PROCESS_H__ */
