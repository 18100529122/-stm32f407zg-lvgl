#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"
#include "app_data_process.h"
#include <math.h>
#include "elog.h"


extern lv_obj_t * screen_main;
extern lv_obj_t * screen_main_cont_main_set;
extern lv_obj_t * screen_main_cont_main_set_09;
extern lv_obj_t * screen_main_label_set_09_01;
extern lv_obj_t * screen_main_btn_set_09_01;
extern lv_obj_t * screen_main_btn_set_09_01_label;
extern lv_obj_t * screen_main_btn_set_09_02;
extern lv_obj_t * screen_main_btn_set_09_02_label;
extern lv_obj_t * screen_main_cont_main_set_08;
extern lv_obj_t * screen_main_label_set_08_01;
extern lv_obj_t * screen_main_btn_set_08_01;
extern lv_obj_t * screen_main_btn_set_08_01_label;
extern lv_obj_t * screen_main_btn_set_08_02;
extern lv_obj_t * screen_main_btn_set_08_02_label;
extern lv_obj_t * screen_main_btn_set_08_03;
extern lv_obj_t * screen_main_btn_set_08_03_label;
extern lv_obj_t * screen_main_cont_main_set_07;
extern lv_obj_t * screen_main_label_set_07_01;
extern lv_obj_t * screen_main_btn_set_07_01;
extern lv_obj_t * screen_main_btn_set_07_01_label;
extern lv_obj_t * screen_main_btn_set_07_02;
extern lv_obj_t * screen_main_btn_set_07_02_label;
extern lv_obj_t * screen_main_cont_main_set_06;
extern lv_obj_t * screen_main_label_set_06_01;
extern lv_obj_t * screen_main_btn_set_06_01;
extern lv_obj_t * screen_main_btn_set_06_01_label;
extern lv_obj_t * screen_main_btn_set_06_02;
extern lv_obj_t * screen_main_btn_set_06_02_label;
extern lv_obj_t * screen_main_btn_set_06_03;
extern lv_obj_t * screen_main_btn_set_06_03_label;
extern lv_obj_t * screen_main_cont_main_set_05;
extern lv_obj_t * screen_main_label_set_05_01;
extern lv_obj_t * screen_main_btn_set_05_01;
extern lv_obj_t * screen_main_btn_set_05_01_label;
extern lv_obj_t * screen_main_btn_set_05_02;
extern lv_obj_t * screen_main_btn_set_05_02_label;
extern lv_obj_t * screen_main_cont_main_set_04;
extern lv_obj_t * screen_main_label_set_04_01;
extern lv_obj_t * screen_main_slider_set_04_01;
extern lv_obj_t * screen_main_label_set_04_02;
extern lv_obj_t * screen_main_label_set_04_03;
extern lv_obj_t * screen_main_cont_main_set_03;
extern lv_obj_t * screen_main_label_set_03_01;
extern lv_obj_t * screen_main_slider_set_03_01;
extern lv_obj_t * screen_main_label_set_03_02;
extern lv_obj_t * screen_main_label_set_03_03;
extern lv_obj_t * screen_main_cont_main_set_02;
extern lv_obj_t * screen_main_label_set_02_01;
extern lv_obj_t * screen_main_slider_set_02_01;
extern lv_obj_t * screen_main_label_set_02_02;
extern lv_obj_t * screen_main_label_set_02_03;
extern lv_obj_t * screen_main_cont_main_set_01;
extern lv_obj_t * screen_main_label_set_01_01;
extern lv_obj_t * screen_main_slider_set_01_01;
extern lv_obj_t * screen_main_label_set_01_02;
extern lv_obj_t * screen_main_label_set_01_03;
extern lv_obj_t * screen_main_cont_main_set_tail;
extern lv_obj_t * screen_main_label_set_tail_01;
extern lv_obj_t * screen_main_btn_set_tail_01;
extern lv_obj_t * screen_main_btn_set_tail_01_label;
extern lv_obj_t * screen_main_cont_main_show;
extern lv_obj_t * screen_main_cont_tail;
extern lv_obj_t * screen_main_label_tail_01;
extern lv_obj_t * screen_main_label_tail_02;
extern lv_obj_t * screen_main_label_tail_03;
extern lv_obj_t * screen_main_label_tail_04;
extern lv_obj_t * screen_main_label_tail_05;
extern lv_obj_t * screen_main_label_tail_06;
extern lv_obj_t * screen_main_btn_tail_01;
extern lv_obj_t * screen_main_btn_tail_01_label;
extern lv_obj_t * screen_main_cont_show_tab2;
extern lv_obj_t * screen_main_cont_a1eThAfj;
extern lv_obj_t * screen_main_bar_show_tab2_1;
extern lv_obj_t * screen_main_label_show_tab2_11;
extern lv_obj_t * screen_main_label_show_tab2_12;
extern lv_obj_t * screen_main_label_show_tab2_13;
extern lv_obj_t * screen_main_cont_zqAwibOK;
extern lv_obj_t * screen_main_bar_show_tab2_2;
extern lv_obj_t * screen_main_label_show_tab2_21;
extern lv_obj_t * screen_main_label_show_tab2_22;
extern lv_obj_t * screen_main_label_show_tab2_23;
extern lv_obj_t * screen_main_cont_sYPD6Gkz;
extern lv_obj_t * screen_main_bar_show_tab2_3;
extern lv_obj_t * screen_main_label_show_tab2_31;
extern lv_obj_t * screen_main_label_show_tab2_32;
extern lv_obj_t * screen_main_label_show_tab2_33;
extern lv_obj_t * screen_main_cont_Mif8nq4s;
extern lv_obj_t * screen_main_bar_show_tab2_4;
extern lv_obj_t * screen_main_label_show_tab2_41;
extern lv_obj_t * screen_main_label_show_tab2_42;
extern lv_obj_t * screen_main_label_show_tab2_43;
extern lv_obj_t * screen_main_cont_show_tab1;
extern lv_obj_t * screen_main_chart_show_tab1;
extern lv_obj_t * screen_main_btn_show_tab1_1;
extern lv_obj_t * screen_main_btn_show_tab1_1_label;
extern lv_obj_t * screen_main_btn_show_tab1_2;
extern lv_obj_t * screen_main_btn_show_tab1_2_label;
extern lv_obj_t * screen_main_label_show_tab1;
extern lv_obj_t * screen_main_cont_tab;
extern lv_obj_t * screen_main_btn_tab1;
extern lv_obj_t * screen_main_btn_tab1_label;
extern lv_obj_t * screen_main_btn_tab2;
extern lv_obj_t * screen_main_btn_tab2_label;
extern lv_obj_t * screen_main_btn_tab3;
extern lv_obj_t * screen_main_btn_tab3_label;
extern lv_obj_t * screen_main_btn_tab4;
extern lv_obj_t * screen_main_btn_tab4_label;
extern lv_obj_t * screen_main_cont_menu1;
extern lv_obj_t * screen_main_cont_menu3;
extern lv_obj_t * screen_main_label_menu3_num1;
extern lv_obj_t * screen_main_label_menu3_num2;
extern lv_obj_t * screen_main_label_menu3_num3;
extern lv_obj_t * screen_main_cont_menu2;
extern lv_obj_t * screen_main_label_menu2_3;
extern lv_obj_t * screen_main_label_menu2_2;
extern lv_obj_t * screen_main_label_menu2_1;
extern lv_obj_t * screen_main_label_menu1;
extern lv_obj_t * screen_main_cont_title1;
extern lv_obj_t * screen_main_label_time1;
extern lv_obj_t * screen_main_img_battery1;

lv_ui_data_t lv_ui_data={0};

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

static void hidden_tab1(void)
{
	lv_obj_add_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
}

static void show_tab1(void)
{
	lv_obj_clear_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
}

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
	}
}

void screen_main_btn_set_09_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_09_02 clicked");
	}
}

void screen_main_btn_set_08_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_01 clicked");
	}
}

void screen_main_btn_set_08_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_02 clicked");
	}
}

void screen_main_btn_set_08_03_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_03 clicked");
	}
}

void screen_main_btn_set_07_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_07_01 clicked");
	}
}

void screen_main_btn_set_07_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_07_02 clicked");
	}
}

void screen_main_btn_set_06_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_01 clicked");
	}
}

void screen_main_btn_set_06_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_02 clicked");
	}
}

void screen_main_btn_set_06_03_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_03 clicked");
	}
}

void screen_main_btn_set_05_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_05_01 clicked");
	}
}

void screen_main_btn_set_05_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_05_02 clicked");
	}
}

void screen_main_btn_set_tail_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_tail_01 clicked");
		show_count_show();
	}
}

void screen_main_btn_show_tab1_1_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_show_tab1_1 clicked");
	}
}

void screen_main_btn_show_tab1_2_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_show_tab1_2 clicked");
	}
}

void screen_main_btn_tab1_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab1 clicked");
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		show_tab1();
	}
}

void screen_main_btn_tab2_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab2 clicked");
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		show_tab1();
	}
}

void screen_main_btn_tab3_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab3 clicked");
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		hidden_tab1();
	}
}

void screen_main_btn_tab4_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab4 clicked");
		ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		show_tab1();
	}
}

/**
 * @brief 更新图表数据
 * @param data UI 数据结构体指针
 */
void lv_ui_data_update(void)
{

}

/**
 * @brief 初始化图表
 * @param argument 未使用
 */
void screen_chart_init(void)
{
	
	lv_ui_data_update();// 初始化图表数据
}

/**
 * @brief UI 初始化包装函数
 */
void lv_ui_init(void)
{
	lv_lock();
	setupUi();// 初始化 UI 界面
	screen_chart_init();// 初始化图表
	lv_unlock();
}

/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void) {}
