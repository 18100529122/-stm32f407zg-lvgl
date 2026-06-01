#ifndef LV_UI_EVENT_H
#define LV_UI_EVENT_H

#include "lvgl.h"
#include "app_data_process.h" // 添加此行

#ifdef __cplusplus
extern "C"
{
#endif


void screen_main_btn_tail_01_event_cb(lv_event_t *e);
void screen_main_btn_set_09_01_event_cb(lv_event_t *e);
void screen_main_btn_set_09_02_event_cb(lv_event_t *e);
void screen_main_btn_set_08_01_event_cb(lv_event_t *e);
void screen_main_btn_set_08_02_event_cb(lv_event_t *e);
void screen_main_btn_set_08_03_event_cb(lv_event_t *e);
void screen_main_btn_set_07_01_event_cb(lv_event_t *e);
void screen_main_btn_set_07_02_event_cb(lv_event_t *e);
void screen_main_btn_set_06_01_event_cb(lv_event_t *e);
void screen_main_btn_set_06_02_event_cb(lv_event_t *e);
void screen_main_btn_set_06_03_event_cb(lv_event_t *e);
void screen_main_btn_set_05_01_event_cb(lv_event_t *e);
void screen_main_btn_set_05_02_event_cb(lv_event_t *e);
void screen_main_btn_set_tail_01_event_cb(lv_event_t *e);
void screen_main_btn_show_tab1_1_event_cb(lv_event_t *e);
void screen_main_btn_show_tab1_2_event_cb(lv_event_t *e);
void screen_main_btn_tab1_event_cb(lv_event_t *e);
void screen_main_btn_tab2_event_cb(lv_event_t *e);
void screen_main_btn_tab3_event_cb(lv_event_t *e);
void screen_main_btn_tab4_event_cb(lv_event_t *e);

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

	uint16_t (*prpd_matrix_ptr)[PRPD_PHASE_BINS]; /**< PRPD图谱矩阵数据指针 */
	uint16_t (*tof_matrix_ptr)[TOF_TIME_BINS];  /**< 飞行图谱矩阵数据指针 */
	uint16_t *adc_wave_ptr;  /**< ADC 波形数据指针 */
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
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_UI_EVENT_H*/
