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
 * @brief 更新图表数据
 * @param rms RMS 值
 * @param max 最大值
 * @param data50hz 50Hz 值
 * @param data100hz 100Hz 值
 * @param rms_data RMS 值数据
 * @param max_data 最大值数据
 * @param data50hz_data 50Hz 值数据
 * @param data100hz_data 100Hz 值数据
 */
void lv_ui_data_update(uint8_t rms,uint8_t max,uint8_t data50hz,uint8_t data100hz,char * rms_data,char * max_data,char * data50hz_data,char * data100hz_data);


/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_UI_EVENT_H*/
