#ifndef __APP_H__
#define __APP_H__
/*========================= 头文件包含 (Includes) ==========================*/
#include "main.h"

/**
 * @brief 应用程序级初始化 (包含所有后台任务)
 */
void app_init(void);
/*========================= 宏定义 (Macros) ================================*/

/*========================= 类型定义 (Typedefs) ============================*/

/**
 * @brief 公共数据结构体 (数据处理与UI共享)
 */
typedef struct
{
	/* 四要素值 */
	float rms;          /* 有效值 */
	float peak;         /* 周期最大值 */
	float freq_50hz;    /* 50Hz 分量 */
	float freq_100hz;   /* 100Hz 分量 */

	/* 设置参数 */
	float attention_threshold;   /* 注意阈值 0-70.0 默认20 */
	float alarm_threshold;       /* 告警阈值 0-70.0 默认20 */
	uint8_t count_threshold;     /* 计数阈值 0-160 默认5 */
	uint16_t phase_offset;       /* 相位偏移 0-360 默认0 */
	int gain_type;               /* 增益类型 0自动 1手动 默认1 */
	uint8_t signal_gain;         /* 信号增益 0 40db 1 60db 2 80db 默认0 */
	int unit_selection;          /* 单位选择 0 dbuv 1uv 默认0 */
	uint8_t flight_cycle;        /* 飞行周期 0 2T 1 5T 2 10T 默认0 */
} app_common_data_t;

/*========================= 全局变量 (Global Variables) ====================*/

extern app_common_data_t g_app_common_data;

/*========================= 函数声明 (Function Declarations) ===============*/



#endif /* __APP_H__ */
