#include "app.h"
#include "app_data_process.h"
#include "elog.h"

app_common_data_t g_app_common_data = {
	/* 四要素值 */
	.rms = 0.0f,
	.peak = 0.0f,
	.freq_50hz = 0.0f,
	.freq_100hz = 0.0f,

	/* 设置参数 */
	.attention_threshold = 20.0f,
	.alarm_threshold = 20.0f,
	.count_threshold = 5,
	.phase_offset = 0,
	.gain_type = 1,
	.signal_gain = 0,
	.unit_selection = 0,
	.flight_cycle = 0
};

/**
 * @brief 应用程序级初始化
 */
void app_init(void)
{
	/* 初始化数据处理后台任务 */
	app_data_process_init();
	log_i("app_data_process_init done");

	/* 后续可在此添加其他业务任务的初始化 */
}
