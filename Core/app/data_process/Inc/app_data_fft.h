#ifndef __APP_DATA_FFT_H__
#define __APP_DATA_FFT_H__

#include "main.h"

#define FFT_LENGTH      512
#define FREQ_COMP_NUM   10

/* 结果结构体 */
typedef struct {
    float freq_values[FREQ_COMP_NUM];  /* 50Hz, 100Hz, ..., 500Hz 的幅值 */
    float magnitudes[FFT_LENGTH / 2];  /* 全频谱幅值 */
} fft_result_t;

extern fft_result_t g_fft_result;

void app_data_fft_init(void);
void app_data_fft_compute(uint16_t *input_data, uint32_t length);

/**
 * @brief 获取指定索引的频率分量值
 * @param index 索引 (0-9)
 * @return float 频率分量值
 */
float app_data_fft_get_freq_value(int index);

#endif /* __APP_DATA_FFT_H__ */
