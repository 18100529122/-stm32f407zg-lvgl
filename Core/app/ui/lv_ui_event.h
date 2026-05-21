#ifndef LV_UI_EVENT_H
#define LV_UI_EVENT_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief 切换为柱状图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_bar_event_cb(lv_event_t *e);

/**
 * @brief 切换为折线图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_line_event_cb(lv_event_t *e);

/**
 * @brief UI 数据结构体
 */
typedef struct
{
	uint8_t rms;			 /**< RMS 值 */
	uint8_t max;			 /**< 最大值 */
	uint8_t data50hz;		  /**< 50Hz 值 */
	uint8_t data100hz;	   /**< 100Hz 值 */
	char *rms_data;		/**< RMS 值数据字符串 */
	char *max_data;		/**< 最大值数据字符串 */
	char *data50hz_data;	 /**< 50Hz 值数据字符串 */
	char *data100hz_data;  /**< 100Hz 值数据字符串 */

	uint16_t *tof_matrix;  /**< 飞行图谱矩阵数据指针 */
	uint16_t adc_wave[512]; /**< ADC 波形数据指针 */
} lv_ui_data_t;

/**
 * @brief UI 初始化包装函数
 */
void lv_ui_init(void);

/**
 * @brief 更新图表数据
 * @param data UI 数据结构体指针
 */
void lv_ui_data_update(lv_ui_data_t *data);

/**
 * @brief PRPD 图谱自定义绘图回调
 * @param e 事件对象
 */
void prpd_chart_draw_event_cb(lv_event_t *e);

/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_UI_EVENT_H*/
