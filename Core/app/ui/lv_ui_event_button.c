/**
 * @file    lv_ui_event_button.c
 * @brief   Button 相关事件处理
 */

/*========================= 头文件包含 (Includes) ==========================*/
#include "lv_ui_event.h"

/*========================= 宏定义 (Macros) ================================*/

/*========================= 类型定义 (Typedefs) ============================*/

/*========================= 全局变量 (Global Variables) ====================*/

/*========================= 静态变量 (Static Variables) ====================*/

/*========================= 静态函数声明 (Static Function Declarations) ====*/

/**
 * @brief 隐藏主界面,显示设置界面
 *
 * 该函数将 `screen_main_cont_main_show`、`screen_main_cont_tail`、
 * `screen_main_label_tail_01` 到 `screen_main_label_tail_06`、
 * `screen_main_btn_tail_01` 等对象的隐藏标志移除，
 * 从而显示连续尾部界面。
 */
static void hidden_count_show(void)
{
	// 隐藏
	lv_obj_add_flag(screen_main_cont_main_show, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_tail, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_02, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_03, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_04, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_05, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_06, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_show_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_a1eThAfj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_11, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_12, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_13, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_zqAwibOK, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_21, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_22, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_23, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_sYPD6Gkz, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_31, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_32, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_33, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_Mif8nq4s, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_4, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_41, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_42, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_43, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_tab, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab4, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief 显示主界面,隐藏设置界面
 *
 * 该函数将 `screen_main_cont_main_show`、`screen_main_cont_tail`、
 * `screen_main_label_tail_01` 到 `screen_main_label_tail_06`、
 * `screen_main_btn_tail_01` 等对象的隐藏标志移除，
 * 从而显示连续尾部界面。
 */
static void show_count_show(void)
{
	lv_obj_clear_flag(screen_main_cont_main_show, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_tail, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_02, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_03, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_04, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_05, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_06, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_show_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_a1eThAfj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_11, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_12, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_13, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_zqAwibOK, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_21, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_22, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_23, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_sYPD6Gkz, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_31, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_32, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_33, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_Mif8nq4s, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_4, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_41, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_42, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_43, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_tab, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab4, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief 隐藏折线图表,显示柱状图
 *
 */
static void hidden_tab1(void)
{
	lv_obj_add_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief 显示柱状图,隐藏折线图表
 *
 */
static void show_tab1(void)
{
	lv_obj_clear_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief 控制界面的图表显示
 *
 * 根据 `tab` 参数的值，切换显示界面的图表。
 * - 0：显示柱状图
 * - 1：显示折线图表
 * - 2：隐藏折线图表
 * - 3：显示柱状图
 *
 * @param tab 图表选择值，0-3 之间的整数
 */
static void control_cont_tab1(int tab)
{
	switch (tab)
	{
	case 0:
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		show_tab1();
		lv_ui_data.chart_selection = 0;
		break;
	case 1:
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		show_tab1();
		lv_ui_data.chart_selection = 1;
		break;
	case 2:
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		hidden_tab1();
		lv_ui_data.chart_selection = 2;
		break;
	case 3:
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		show_tab1();
		lv_ui_data.chart_selection = 3;
		break;
	default:
		break;
	}
	chart_set_style();
}

/*========================= 函数实现 (Function Definitions) ================*/

void screen_main_btn_tail_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tail_01 clicked");
		hidden_count_show();
	}
}

void screen_main_btn_set_09_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_09_01 clicked");
		ui_state_modify(screen_main_btn_set_09_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_09_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		lv_ui_data.laser_enabled = 1;
	}
}

void screen_main_btn_set_09_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_09_02 clicked");
		ui_state_modify(screen_main_btn_set_09_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_09_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		lv_ui_data.laser_enabled = 0;
	}
}

void screen_main_btn_set_08_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_01 clicked");
		ui_state_modify(screen_main_btn_set_08_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_08_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.flight_cycle = 0;
		g_app_data_result.flight_period = 2;
		__enable_irq();
	}
}

void screen_main_btn_set_08_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_02 clicked");
		ui_state_modify(screen_main_btn_set_08_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_08_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.flight_cycle = 1;
		g_app_data_result.flight_period = 5;
		__enable_irq();
	}
}

void screen_main_btn_set_08_03_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_03 clicked");
		ui_state_modify(screen_main_btn_set_08_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_03, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.flight_cycle = 2;
		g_app_data_result.flight_period = 10;
		__enable_irq();
	}
}

void screen_main_btn_set_07_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_07_01 clicked");
		ui_state_modify(screen_main_btn_set_07_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_07_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.unit_selection = 0;
		g_app_data_result.unit_select_dBuV = true;
		__enable_irq();
	}
}

void screen_main_btn_set_07_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_07_02 clicked");
		ui_state_modify(screen_main_btn_set_07_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_07_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.unit_selection = 1;
		g_app_data_result.unit_select_dBuV = false;
		__enable_irq();
	}
}

void screen_main_btn_set_06_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_01 clicked");
		ui_state_modify(screen_main_btn_set_06_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_06_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.signal_gain = 0;
		g_app_data_result.gain = 40;
		__enable_irq();
	}
}

void screen_main_btn_set_06_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_02 clicked");
		ui_state_modify(screen_main_btn_set_06_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_06_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.signal_gain = 1;
		g_app_data_result.gain = 60;
		__enable_irq();
	}
}

void screen_main_btn_set_06_03_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_03 clicked");
		ui_state_modify(screen_main_btn_set_06_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_03, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.signal_gain = 2;
		g_app_data_result.gain = 80;
		__enable_irq();
	}
}

void screen_main_btn_set_05_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_05_01 clicked");
		ui_state_modify(screen_main_btn_set_05_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_05_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.gain_type = 0;
		g_app_data_result.gain_type_auto = true;
		__enable_irq();
	}
}

void screen_main_btn_set_05_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_05_02 clicked");
		ui_state_modify(screen_main_btn_set_05_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_05_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		// 关闭开启中断
		__disable_irq();
		lv_ui_data.gain_type = 1;
		g_app_data_result.gain_type_auto = false;
		__enable_irq();
	}
}

void screen_main_btn_set_tail_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_tail_01 clicked");
		show_count_show();
		control_cont_tab1(lv_ui_data.chart_selection);
	}
}

void screen_main_btn_show_tab1_1_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_show_tab1_1 clicked");
		if (lv_ui_data.y_axis_range < 100)
		{
			lv_ui_data.y_axis_range += 10;
			update_chart_y_axis_and_labels();
			label_set_y_axis_range();
		}
	}
}

void screen_main_btn_show_tab1_2_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_show_tab1_2 clicked");
		if (lv_ui_data.y_axis_range > 10)
		{
			lv_ui_data.y_axis_range -= 10;
			update_chart_y_axis_and_labels();
			label_set_y_axis_range();
		}
	}
}

void screen_main_btn_tab1_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab1 clicked");
		control_cont_tab1(0);
	}
}

void screen_main_btn_tab2_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab2 clicked");
		control_cont_tab1(1);
	}
}

void screen_main_btn_tab3_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab3 clicked");
		control_cont_tab1(2);
	}
}

void screen_main_btn_tab4_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab4 clicked");
		control_cont_tab1(3);
	}
}
