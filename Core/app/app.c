#include "app.h"
#include "data_process/Inc/app_data_process.h"

/**
 * @brief 应用程序级初始化
 */
void app_init(void)
{
    /* 初始化数据处理后台任务 */
    app_data_process_init();
    
    /* 后续可在此添加其他业务任务的初始化 */
}
