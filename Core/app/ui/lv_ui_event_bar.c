/**
 * @file    lv_ui_event_bar.c
 * @brief   Bar 相关事件处理
 */

/*========================= 头文件包含 (Includes) ==========================*/
#include "lv_ui_event.h"

/*========================= 宏定义 (Macros) ================================*/

/*========================= 类型定义 (Typedefs) ============================*/

/*========================= 全局变量 (Global Variables) ====================*/

/*========================= 静态变量 (Static Variables) ====================*/

/*========================= 静态函数声明 (Static Function Declarations) ====*/

/*========================= 函数实现 (Function Definitions) ================*/

void bar_set_rms(void)
{
	int32_t value = (int)(lv_ui_data.common_data.rms * 0.02);
	if (value < 0)
	{
		value = 0;
	}
	else if (value > 100)
	{
		value = 100;
	}
	lv_bar_set_value(screen_main_bar_show_tab2_1, value, LV_ANIM_OFF);
}

void bar_set_max(void)
{
	int32_t value = (int)(lv_ui_data.common_data.peak * 0.02);
	if (value < 0)
	{
		value = 0;
	}
	else if (value > 100)
	{
		value = 100;
	}
	lv_bar_set_value(screen_main_bar_show_tab2_2, value, LV_ANIM_OFF);
}

void bar_set_data50hz(void)
{
	int32_t value = (int)(lv_ui_data.common_data.freq_50hz * 0.02);
	if (value < 0)
	{
		value = 0;
	}
	else if (value > 100)
	{
		value = 100;
	}
	lv_bar_set_value(screen_main_bar_show_tab2_3, value, LV_ANIM_OFF);
}

void bar_set_data100hz(void)
{
	int32_t value = (int)(lv_ui_data.common_data.freq_100hz * 0.02);
	if (value < 0)
	{
		value = 0;
	}
	else if (value > 100)
	{
		value = 100;
	}
	lv_bar_set_value(screen_main_bar_show_tab2_4, value, LV_ANIM_OFF);
}
