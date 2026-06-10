#ifndef LV_UI_EVENT_H
#define LV_UI_EVENT_H

#include "lvgl.h"
#include "app_data_process.h" // 添加此行

#ifdef __cplusplus
extern "C"
{
#endif

#define Y_AXIS_GLOBAL_MAX 5000
#define Y_AXIS_GLOBAL_MIN -5000


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

void screen_main_slider_set_01_01_event_cb(lv_event_t *e);
void screen_main_slider_set_02_01_event_cb(lv_event_t *e);
void screen_main_slider_set_03_01_event_cb(lv_event_t *e);
void screen_main_slider_set_04_01_event_cb(lv_event_t *e);

/**
 * @brief UI 数据结构体
 */
typedef struct
{
	int time;               /**< 时间 */
	int battery_level;      /**< 电量 */
	// cont menu 界面显示参数
	float internal_ultrasound; /**< 内置超声 */
	float peak_value;            /**< 峰值 */
	float noise;            /**< 噪声 */
	int pulse;              /**< 脉冲 */
	// cont show 界面显示与控制参数
	int chart_selection;    /**< 图表选择 0脉冲波形 1PRPD图 2四要素图 3飞行图谱 默认0*/
	int y_axis_range;       /**< Y轴量程0-100 默认25 */
	uint16_t *adc_wave_ptr;  /**< ADC 波形数据指针 脉冲波形 */
	uint16_t (*prpd_matrix_ptr)[PRPD_PHASE_BINS]; /**< PRPD图谱矩阵数据指针 */
	uint16_t (*tof_matrix_ptr)[TOF_TIME_BINS];  /**< 飞行图谱矩阵数据指针 */
	//四要素图
	uint8_t rms;			 /**< RMS 值 */
	uint8_t max;			 /**< 最大值 */
	uint8_t data50hz;		  /**< 50Hz 值 */
	uint8_t data100hz;	   /**< 100Hz 值 */

	// cont tail 界面显示参数
	int sync_method;        /**< 同步方式 0内同步 */
	int sync_frequency;     /**< 同步频率 默认50Hz*/
	int channel_gain;       /**< 通道增益 默认40dB*/
	int channel_threshold;  /**< 通道阈值 默认20*/
	int phase_offset;       /**< 相位偏移 0-360默认0*/
	int filter_enabled;     /**< 滤波是否开启 0关闭 1开启 默认0*/

	// cont set 界面显示与控制参数
	float attention_threshold; /**< 注意阈值 0-70.0 默认20*/
	float alarm_threshold;  /**< 告警阈值 0-70.0 默认20*/
	uint8_t count_threshold;    /**< 计数阈值 0-160 默认5 */
	uint16_t phase_offset_angle; /**< 相位偏移角度 0-360默认0*/
	int gain_type;          /**< 增益类型 0自动 1手动 默认1*/
	uint8_t signal_gain;        /**< 信号增益 0 40db 1 60db 2 80db 默认0 */
	int unit_selection;     /**< 单位选择 0 dbuv 1uv 默认0*/
	uint8_t flight_cycle;       /**< 飞行周期 0 2T 1 5T 2 10T 默认0*/
	int channel_selection;  /**< 通道选择 0内置超声 1外部超声 默认0*/
} lv_ui_data_t;
extern lv_ui_data_t lv_ui_data;
/**
 * @brief UI 初始化包装函数
 */
void lv_ui_init(void);

/**
 * @brief 更新图表数据
 * @param data UI 数据结构体指针
 */
void lv_ui_data_update(void);

/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_UI_EVENT_H*/
