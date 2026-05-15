#include "middleware.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

/**
 * @brief 初始化中间件 (LVGL 等)
 */
void middleware_init(void)
{
    /* 初始化 LVGL 核心 */
    lv_init();
    
    /* 初始化显示接口 */
    lv_port_disp_init();
    
    /* 初始化触摸接口 */
    lv_port_indev_init();

    /* 初始化 FreeRTOS 任务 */
    lv_freertos_init();
}
