#ifndef LV_UI_EVENT_H
#define LV_UI_EVENT_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 屏幕 1 按钮点击事件回调
 * @param e 事件对象
 */
void screen_btn_1_event_cb(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_UI_EVENT_H*/
