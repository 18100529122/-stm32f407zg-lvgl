#ifndef __APP_DATA_PROCESS_H__
#define __APP_DATA_PROCESS_H__

#include "main.h"
#include "app_data_fft.h"


/**
 * @brief 飞行图谱配置
 */
#define TOF_AMP_BINS    40   /* Y轴: 0-20mV, 每 0.5mV 一个区间 */
#define TOF_TIME_BINS   100  /* X轴: 0-200ms, 每 2ms 一个区间 */
#define ADC_WAVE_SIZE   512  /* ADC 波形数据大小 (用于 UI 显示) */

/**
 * @brief 数据处理结果结构体
 */
typedef struct {
    float rms;           /* 有效值 */
    float peak;          /* 周期最大值 */
    float freq_50hz;     /* 50Hz 分量 */
    float freq_100hz;    /* 100Hz 分量 */
    
    /* 飞行图谱相关数据 */
    uint16_t tof_matrix[TOF_AMP_BINS][TOF_TIME_BINS]; /* 飞行图谱统计矩阵 */
    uint32_t tof_point_cnt;                           /* 飞行图谱总点数 */
    uint32_t last_pulse_sample_idx;                   /* 上一个脉冲的采样点索引 */
    float trigger_thr_mv;                             /* 触发阈值(mV) */
    
    /* ADC 波形数据 (用于 UI 显示) */
    uint16_t adc_wave[ADC_WAVE_SIZE];                           /* 抽点后的 ADC 波形数据 */

    /* 统计数据 用于测试*/
    uint32_t adc_restart_cnt;                         /* ADC 重启计数 */
    uint32_t adc_sample_cnt;                          /* ADC 采样点计数 */
    uint32_t adc_valid_sample_cnt;                   /* ADC 有效采样点计数 */

    uint32_t start_time;                             /* 数据处理开始时间 */
    uint32_t end_time;                               /* 数据处理结束时间 */
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
void app_data_process_inc_adc_restart_cnt(void);
void app_data_process_inc_adc_sample_cnt(uint32_t add);

/**
 * @brief 获取数据处理结果
 * @return app_data_result_t 数据处理结果
 */
app_data_result_t* app_data_process_get_result(void);
uint8_t app_data_process_get_rms_uint8(void);
uint8_t app_data_process_get_peak_uint8(void);
uint8_t app_data_process_get_freq_50hz_uint8(void);
uint8_t app_data_process_get_freq_100hz_uint8(void);
char *app_data_process_get_rms_str(void);
char *app_data_process_get_peak_str(void);
char *app_data_process_get_freq_50hz_str(void);
char *app_data_process_get_freq_100hz_str(void);
char *app_data_process_get_threshold_str(void);

/**
 * @brief 获取飞行图谱矩阵中指定区间的值
 */
uint16_t app_data_process_get_tof_bin(uint8_t amp_idx, uint8_t time_idx);

#endif /* __APP_DATA_PROCESS_H__ */
