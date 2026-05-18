#ifndef __APP_DATA_PROCESS_H__
#define __APP_DATA_PROCESS_H__

#include "main.h"
#include "app_data_fft.h"


/**
 * @brief 数据处理结果结构体
 */
typedef struct {
    float rms;           /* 有效值 */
    float peak;          /* 周期最大值 */
    float freq_50hz;     /* 50Hz 分量 */
    float freq_100hz;    /* 100Hz 分量 */
} app_data_result_t;

extern app_data_result_t g_app_data_result;

/**
 * @brief 数据处理任务初始化
 */
void app_data_process_init(void);

/**
 * @brief 获取数据处理结果
 * @return app_data_result_t 数据处理结果
 */
app_data_result_t* app_data_process_get_result(void);

#endif /* __APP_DATA_PROCESS_H__ */
