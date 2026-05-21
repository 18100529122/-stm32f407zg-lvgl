#ifndef LV_FREERTOS_APP_H
#define LV_FREERTOS_APP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "cmsis_os.h"
#include "FreeRTOS.h"

/**
 * @brief 初始化 LVGL FreeRTOS 刷新线程
 */
void lv_freertos_init(void);

/**
 * @brief 初始化 LVGL 控件和 UI
 */
void lv_widgets_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_FREERTOS_APP_H*/
