#include "middleware.h"
#include "lvgl.h"
#include "lv_port_disp.h"

/**
 * @brief 初始化中间件 (LVGL 等)
 */
void middleware_init(void)
{
    /* 初始化 LVGL 核心 */
    lv_init();
    
    /* 初始化显示接口 */
    lv_port_disp_init();
    
    /* 这里可以添加其他中间件初始化，如触摸屏接口 lv_port_indev_init() */
}
