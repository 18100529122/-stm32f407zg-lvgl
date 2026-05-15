#ifndef LV_UI_EVENT_H
#define LV_UI_EVENT_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 切换为柱状图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_bar_event_cb(lv_event_t * e);

/**
 * @brief 切换为折线图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_line_event_cb(lv_event_t * e);

/**
 * @brief UI 初始化包装函数
 */
void lv_ui_init(void);

/**
 * @brief 更新柱状图数据
 */
void lv_ui_update_bar_chart_data(float * data, int len);

/**
 * @brief 更新折线图数据
 */
void lv_ui_update_line_chart_data(float * data);

/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_UI_EVENT_H*/
