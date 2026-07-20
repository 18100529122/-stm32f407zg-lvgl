/**
 * @file    lv_ui_event_slider.c
 * @brief   Slider 相关事件处理
 */

/*========================= 头文件包含 (Includes) ==========================*/
#include "lv_ui_event.h"

/*========================= 宏定义 (Macros) ================================*/

/*========================= 类型定义 (Typedefs) ============================*/

/*========================= 全局变量 (Global Variables) ====================*/

/*========================= 静态变量 (Static Variables) ====================*/

/*========================= 静态函数声明 (Static Function Declarations) ====*/

/*========================= 函数实现 (Function Definitions) ================*/

/*
 * @brief 滑块 screen_main_slider_set_01_01 事件回调函数
 * @param e 事件结构体指针
 * @note  当滑块值改变时触发，更新 UI 数据中的 attention_threshold 并刷新显示
 */
void screen_main_slider_set_01_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_01_01);
		log_i("screen_main_slider_set_01_01 value: %d", value);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.common_data.attention_threshold = value * 0.1f;
		g_app_data_result.common_data.attention_threshold = value * 0.1f;
		__enable_irq();
		label_set_attention_threshold();
	}
}

/*
 * @brief 滑块 screen_main_slider_set_02_01 事件回调函数
 * @param e 事件结构体指针
 * @note  当滑块值改变时触发，更新 UI 数据中的 alarm_threshold 并刷新显示
 */
void screen_main_slider_set_02_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_02_01);
		log_i("screen_main_slider_set_02_01 value: %d", value);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.common_data.alarm_threshold = value * 0.1f;
		g_app_data_result.common_data.alarm_threshold = value * 0.1f;
		__enable_irq();
		label_set_alarm_threshold();
	}
}

/*
 * @brief 滑块 screen_main_slider_set_03_01 事件回调函数
 * @param e 事件结构体指针
 * @note  当滑块值改变时触发，更新 UI 数据中的 count_threshold 并刷新显示
 */
void screen_main_slider_set_03_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_03_01);
		log_i("screen_main_slider_set_03_01 value: %d", value);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.common_data.count_threshold = value;
		g_app_data_result.common_data.count_threshold = value;
		__enable_irq();
		label_set_count_threshold();
	}
}

/*
 * @brief 滑块 screen_main_slider_set_04_01 事件回调函数
 * @param e 事件结构体指针
 * @note  当滑块值改变时触发，更新 UI 数据中的 phase_offset_angle 并刷新显示
 */
void screen_main_slider_set_04_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_04_01);
		log_i("screen_main_slider_set_04_01 value: %d", value);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.common_data.phase_offset = value;
		g_app_data_result.common_data.phase_offset = value;
		__enable_irq();
		label_set_phase_offset();
	}
}
