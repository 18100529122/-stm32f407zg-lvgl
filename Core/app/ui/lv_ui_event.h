#ifndef LV_UI_EVENT_H
#define LV_UI_EVENT_H

/*========================= 头文件包含 (Includes) ==========================*/
#include "lvgl.h"
#include "setup_ui.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "elog.h"

#include "app_data_fft.h"
#include "app_data_process.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*========================= 宏定义 (Macros) ================================*/
#define ADC_RANGE_MAX  50	// lv_ui_data.y_axis_range * 5000/100 = *50
#define PRPD_RANGE_MAX 0.4	// 40
#define TOF_RANGE_MAX  0.4	// 40

/*========================= 类型定义 (Typedefs) ============================*/

/**
 * @brief UI 数据结构体
 */
typedef struct
{
	int time;		   /**< 时间 */
	int battery_level; /**< 电量 */
	// cont menu 界面显示参数
	float internal_ultrasound; /**< 内置超声 */
	float peak_value;		   /**< 峰值 */
	float noise;			   /**< 噪声 */
	int pulse;				   /**< 脉冲 */
	// cont show 界面显示与控制参数
	int chart_selection;						  /**< 图表选择 0脉冲波形 1PRPD图 2四要素图 3飞行图谱 默认0*/
	int y_axis_range;							  /**< Y轴量程0-100 默认50 */
	uint16_t adc_wave_100[100];					  /**< ADC 波形数据(100点) 脉冲波形 */
	uint16_t (*prpd_matrix_ptr)[PRPD_PHASE_BINS]; /**< PRPD图谱矩阵数据指针 */
	uint16_t (*tof_matrix_ptr)[TOF_TIME_BINS];	  /**< 飞行图谱矩阵数据指针 */
	// 四要素图
	float rms;		 /**< RMS 值 */
	float max;		 /**< 最大值 */
	float data50hz;	 /**< 50Hz 值 */
	float data100hz; /**< 100Hz 值 */

	// cont tail 界面显示参数
	int sync_method;	   /**< 同步方式 0内同步 */
	int sync_frequency;	   /**< 同步频率 默认50Hz*/
	int channel_gain;	   /**< 通道增益 默认40dB*/
	int channel_threshold; /**< 通道阈值 默认20*/
	int phase_offset;	   /**< 相位偏移 0-360默认0*/
	int filter_enabled;	   /**< 滤波是否开启 0关闭 1开启 默认0*/

	// cont set 界面显示与控制参数
	float attention_threshold;	 /**< 注意阈值 0-70.0 默认20*/
	float alarm_threshold;		 /**< 告警阈值 0-70.0 默认20*/
	uint8_t count_threshold;	 /**< 计数阈值 0-160 默认5 */
	uint16_t phase_offset_angle; /**< 相位偏移角度 0-360默认0*/
	int gain_type;				 /**< 增益类型 0自动 1手动 默认1*/
	uint8_t signal_gain;		 /**< 信号增益 0 40db 1 60db 2 80db 默认0 */
	int unit_selection;			 /**< 单位选择 0 dbuv 1uv 默认0*/
	uint8_t flight_cycle;		 /**< 飞行周期 0 2T 1 5T 2 10T 默认0*/
	int laser_enabled;			 /**< 激光是否开启 0关闭 1开启 默认0*/
} lv_ui_data_t;

/*========================= 全局变量 (Global Variables) ====================*/
extern lv_ui_data_t lv_ui_data;

extern lv_obj_t *screen_main_chart_scale_y;
extern lv_obj_t *screen_main_chart_scale_x;

// setup_screen_main.c中变量
extern lv_obj_t *screen_main;
extern lv_obj_t *screen_main_cont_main_set;
extern lv_obj_t *screen_main_cont_main_set_09;
extern lv_obj_t *screen_main_label_set_09_01;
extern lv_obj_t *screen_main_btn_set_09_01;
extern lv_obj_t *screen_main_btn_set_09_01_label;
extern lv_obj_t *screen_main_btn_set_09_02;
extern lv_obj_t *screen_main_btn_set_09_02_label;
extern lv_obj_t *screen_main_cont_main_set_08;
extern lv_obj_t *screen_main_label_set_08_01;
extern lv_obj_t *screen_main_btn_set_08_01;
extern lv_obj_t *screen_main_btn_set_08_01_label;
extern lv_obj_t *screen_main_btn_set_08_02;
extern lv_obj_t *screen_main_btn_set_08_02_label;
extern lv_obj_t *screen_main_btn_set_08_03;
extern lv_obj_t *screen_main_btn_set_08_03_label;
extern lv_obj_t *screen_main_cont_main_set_07;
extern lv_obj_t *screen_main_label_set_07_01;
extern lv_obj_t *screen_main_btn_set_07_01;
extern lv_obj_t *screen_main_btn_set_07_01_label;
extern lv_obj_t *screen_main_btn_set_07_02;
extern lv_obj_t *screen_main_btn_set_07_02_label;
extern lv_obj_t *screen_main_cont_main_set_06;
extern lv_obj_t *screen_main_label_set_06_01;
extern lv_obj_t *screen_main_btn_set_06_01;
extern lv_obj_t *screen_main_btn_set_06_01_label;
extern lv_obj_t *screen_main_btn_set_06_02;
extern lv_obj_t *screen_main_btn_set_06_02_label;
extern lv_obj_t *screen_main_btn_set_06_03;
extern lv_obj_t *screen_main_btn_set_06_03_label;
extern lv_obj_t *screen_main_cont_main_set_05;
extern lv_obj_t *screen_main_label_set_05_01;
extern lv_obj_t *screen_main_btn_set_05_01;
extern lv_obj_t *screen_main_btn_set_05_01_label;
extern lv_obj_t *screen_main_btn_set_05_02;
extern lv_obj_t *screen_main_btn_set_05_02_label;
extern lv_obj_t *screen_main_cont_main_set_04;
extern lv_obj_t *screen_main_label_set_04_01;
extern lv_obj_t *screen_main_slider_set_04_01;
extern lv_obj_t *screen_main_label_set_04_02;
extern lv_obj_t *screen_main_label_set_04_03;
extern lv_obj_t *screen_main_cont_main_set_03;
extern lv_obj_t *screen_main_label_set_03_01;
extern lv_obj_t *screen_main_slider_set_03_01;
extern lv_obj_t *screen_main_label_set_03_02;
extern lv_obj_t *screen_main_label_set_03_03;
extern lv_obj_t *screen_main_cont_main_set_02;
extern lv_obj_t *screen_main_label_set_02_01;
extern lv_obj_t *screen_main_slider_set_02_01;
extern lv_obj_t *screen_main_label_set_02_02;
extern lv_obj_t *screen_main_label_set_02_03;
extern lv_obj_t *screen_main_cont_main_set_01;
extern lv_obj_t *screen_main_label_set_01_01;
extern lv_obj_t *screen_main_slider_set_01_01;
extern lv_obj_t *screen_main_label_set_01_02;
extern lv_obj_t *screen_main_label_set_01_03;
extern lv_obj_t *screen_main_cont_main_set_tail;
extern lv_obj_t *screen_main_label_set_tail_01;
extern lv_obj_t *screen_main_btn_set_tail_01;
extern lv_obj_t *screen_main_btn_set_tail_01_label;
extern lv_obj_t *screen_main_cont_main_show;
extern lv_obj_t *screen_main_cont_tail;
extern lv_obj_t *screen_main_label_tail_01;
extern lv_obj_t *screen_main_label_tail_02;
extern lv_obj_t *screen_main_label_tail_03;
extern lv_obj_t *screen_main_label_tail_04;
extern lv_obj_t *screen_main_label_tail_05;
extern lv_obj_t *screen_main_label_tail_06;
extern lv_obj_t *screen_main_btn_tail_01;
extern lv_obj_t *screen_main_btn_tail_01_label;
extern lv_obj_t *screen_main_cont_show_tab2;
extern lv_obj_t *screen_main_cont_a1eThAfj;
extern lv_obj_t *screen_main_bar_show_tab2_1;
extern lv_obj_t *screen_main_label_show_tab2_11;
extern lv_obj_t *screen_main_label_show_tab2_12;
extern lv_obj_t *screen_main_label_show_tab2_13;
extern lv_obj_t *screen_main_cont_zqAwibOK;
extern lv_obj_t *screen_main_bar_show_tab2_2;
extern lv_obj_t *screen_main_label_show_tab2_21;
extern lv_obj_t *screen_main_label_show_tab2_22;
extern lv_obj_t *screen_main_label_show_tab2_23;
extern lv_obj_t *screen_main_cont_sYPD6Gkz;
extern lv_obj_t *screen_main_bar_show_tab2_3;
extern lv_obj_t *screen_main_label_show_tab2_31;
extern lv_obj_t *screen_main_label_show_tab2_32;
extern lv_obj_t *screen_main_label_show_tab2_33;
extern lv_obj_t *screen_main_cont_Mif8nq4s;
extern lv_obj_t *screen_main_bar_show_tab2_4;
extern lv_obj_t *screen_main_label_show_tab2_41;
extern lv_obj_t *screen_main_label_show_tab2_42;
extern lv_obj_t *screen_main_label_show_tab2_43;
extern lv_obj_t *screen_main_cont_show_tab1;
extern lv_obj_t *screen_main_chart_show_tab1;
extern lv_obj_t *screen_main_btn_show_tab1_1;
extern lv_obj_t *screen_main_btn_show_tab1_1_label;
extern lv_obj_t *screen_main_btn_show_tab1_2;
extern lv_obj_t *screen_main_btn_show_tab1_2_label;
extern lv_obj_t *screen_main_label_show_tab1;
extern lv_obj_t *screen_main_cont_tab;
extern lv_obj_t *screen_main_btn_tab1;
extern lv_obj_t *screen_main_btn_tab1_label;
extern lv_obj_t *screen_main_btn_tab2;
extern lv_obj_t *screen_main_btn_tab2_label;
extern lv_obj_t *screen_main_btn_tab3;
extern lv_obj_t *screen_main_btn_tab3_label;
extern lv_obj_t *screen_main_btn_tab4;
extern lv_obj_t *screen_main_btn_tab4_label;
extern lv_obj_t *screen_main_cont_menu1;
extern lv_obj_t *screen_main_cont_menu3;
extern lv_obj_t *screen_main_label_menu3_num1;
extern lv_obj_t *screen_main_label_menu3_num2;
extern lv_obj_t *screen_main_label_menu3_num3;
extern lv_obj_t *screen_main_cont_menu2;
extern lv_obj_t *screen_main_label_menu2_3;
extern lv_obj_t *screen_main_label_menu2_2;
extern lv_obj_t *screen_main_label_menu2_1;
extern lv_obj_t *screen_main_label_menu1;
extern lv_obj_t *screen_main_cont_title1;
extern lv_obj_t *screen_main_label_time1;
extern lv_obj_t *screen_main_img_battery1;
/*========================= 函数声明 (Function Declarations) ===============*/
/**
 * @brief UI 初始化包装函数
 */
void lv_ui_init(void);

/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void);

// 更新文本内容
void label_set_internal_ultrasound(void);
void label_set_peak_value(void);
void label_set_noise(void);
void label_set_pulse(void);
void label_set_y_axis_range(void);
void label_set_rms(void);
void label_set_max(void);
void label_set_data50hz(void);
void label_set_data100hz(void);
void label_set_attention_threshold(void);
void label_set_alarm_threshold(void);
void label_set_count_threshold(void);
void label_set_phase_offset(void);
void label_set_cont_tail_sync_method(void);
void label_set_cont_tail_sync_frequency(void);
void label_set_cont_tail_channel_gain(void);
void label_set_cont_tail_channel_threshold(void);
void label_set_cont_tail_phase_offset(void);
void label_set_cont_tail_filter_enabled(void);

// 按键事件
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

// 图表
void update_chart_y_axis_and_labels(void);
void update_chart_x_axis_and_labels(void);
void chart_style_init(lv_obj_t *chart_obj);
void chart_set_style(void);
void updata_chart_data(void);

// 滑块
void screen_main_slider_set_01_01_event_cb(lv_event_t *e);
void screen_main_slider_set_02_01_event_cb(lv_event_t *e);
void screen_main_slider_set_03_01_event_cb(lv_event_t *e);
void screen_main_slider_set_04_01_event_cb(lv_event_t *e);

// Bar
void bar_set_rms(void);
void bar_set_max(void);
void bar_set_data50hz(void);
void bar_set_data100hz(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_UI_EVENT_H*/
