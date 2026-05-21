#include "app.h"
#include "app_data_process.h"
#include "elog.h"

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
