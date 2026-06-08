#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"
#include "app_data_process.h"
#include <math.h>
#include "stdio.h"
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
	lv_obj_add_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
}

static void show_tab1(void)
{
	lv_obj_clear_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
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
		lv_ui_data.chart_selection=0;
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
		lv_ui_data.chart_selection=1;
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
		lv_ui_data.chart_selection=2;
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
		lv_ui_data.chart_selection=3;
	}
}

//修改文本内容
void label_set_internal_ultrasound(void)// 更新内置超声文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1f", lv_ui_data.internal_ultrasound);
	lv_label_set_text(screen_main_label_menu2_2, temp_chars);
}
void label_set_peak_value(void)// 更新峰值文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "峰值:%.1fdBuv", lv_ui_data.peak_value);
	lv_label_set_text(screen_main_label_menu3_num1, temp_chars);
}
void label_set_noise(void)// 更新噪声文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "噪声:%.1fdBuv", lv_ui_data.noise);
	lv_label_set_text(screen_main_label_menu3_num2, temp_chars);
}
void label_set_pulse(void)// 更新脉冲文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "脉冲:%d", lv_ui_data.pulse);
	lv_label_set_text(screen_main_label_menu3_num3, temp_chars);
}

void label_set_y_axis_range(void)// 更新Y轴量程文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%d%%", lv_ui_data.y_axis_range);
	lv_label_set_text(screen_main_label_show_tab1, temp_chars);
}

void label_set_rms(void)// 更新RMS文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1fdBuv", lv_ui_data.rms);
	lv_label_set_text(screen_main_label_show_tab2_13, temp_chars);
}
void label_set_max(void)// 更新最大值文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1fdBuv", lv_ui_data.max);
	lv_label_set_text(screen_main_label_show_tab2_23, temp_chars);
}
void label_set_data50hz(void)// 更新50Hz文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1fdBuv", lv_ui_data.data50hz);
	lv_label_set_text(screen_main_label_show_tab2_33, temp_chars);
}
void label_set_data100hz(void)// 更新100Hz文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1fdBuv", lv_ui_data.data100hz);
	lv_label_set_text(screen_main_label_show_tab2_43, temp_chars);
}

void label_set_attention_threshold(void)// 更新注意阈值文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "注意阈值:%.1fdBuv", lv_ui_data.attention_threshold);
	lv_label_set_text(screen_main_label_set_01_01, temp_chars);
}
void label_set_alarm_threshold(void)// 更新告警阈值文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "告警阈值:%.1fdBuv", lv_ui_data.alarm_threshold);
	lv_label_set_text(screen_main_label_set_02_01, temp_chars);
}
void label_set_count_threshold(void)// 更新计数阈值文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "计数阈值: %d 个", lv_ui_data.count_threshold);
	lv_label_set_text(screen_main_label_set_03_01, temp_chars);
}
void label_set_phase_offset(void)// 更新相位偏移文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "相位偏移: %d 度", lv_ui_data.phase_offset);
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
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
	//初始化结构体
	// cont menu 界面显示参数
	lv_ui_data.time=0;               /**< 时间 */
	lv_ui_data.battery_level=0;      /**< 电量 */

	lv_ui_data.internal_ultrasound=0.0f; /**< 内置超声 */
	lv_ui_data.peak_value=0.0f;            /**< 峰值 */
	lv_ui_data.noise=0.0f;            /**< 噪声 */
	lv_ui_data.pulse=0;              /**< 脉冲 */

	// cont show 界面显示与控制参数
	lv_ui_data.chart_selection=0;    /**< 图表选择 0脉冲波形 1PRPD图 2四要素图 3飞行图谱 默认0*/
	lv_ui_data.y_axis_range=25;       /**< Y轴量程0-100 默认25 */
	lv_ui_data.adc_wave_ptr=NULL;  /**< ADC 波形数据指针 脉冲波形 */
	lv_ui_data.prpd_matrix_ptr=NULL; /**< PRPD图谱矩阵数据指针 */
	lv_ui_data.tof_matrix_ptr=NULL;  /**< 飞行图谱矩阵数据指针 */
	//四要素图
	lv_ui_data.rms=0;			 /**< RMS 值 */
	lv_ui_data.max=0;			 /**< 最大值 */
	lv_ui_data.data50hz=0;		  /**< 50Hz 值 */
	lv_ui_data.data100hz=0;	   /**< 100Hz 值 */

	// cont tail 界面显示参数
	lv_ui_data.sync_method=0;        /**< 同步方式 0内同步 */
	lv_ui_data.sync_frequency=50;     /**< 同步频率 默认50Hz*/
	lv_ui_data.channel_gain=40;       /**< 通道增益 默认40dB*/
	lv_ui_data.channel_threshold=20;  /**< 通道阈值 默认20*/
	lv_ui_data.phase_offset=0;       /**< 相位偏移 0-360默认0*/
	lv_ui_data.filter_enabled=0;     /**< 滤波是否开启 0关闭 1开启 默认0*/

	// cont set 界面显示与控制参数
	lv_ui_data.attention_threshold=20.0f; /**< 注意阈值 0-70.0 默认20*/
	lv_ui_data.alarm_threshold=20.0f;  /**< 告警阈值 0-70.0 默认20*/
	lv_ui_data.count_threshold=5;    /**< 计数阈值 0-160 默认5 */
	lv_ui_data.phase_offset_angle=0; /**< 相位偏移角度 0-360默认0*/
	lv_ui_data.gain_type=1;          /**< 增益类型 0自动 1手动 默认1*/
	lv_ui_data.signal_gain=0;        /**< 信号增益 0 40db 1 60db 2 80db 默认0 */
	lv_ui_data.unit_selection=0;     /**< 单位选择 0 dbuv 1uv 默认0*/
	lv_ui_data.flight_cycle=0;       /**< 飞行周期 0 2T 1 5T 2 10T 默认0*/	
	lv_ui_data.channel_selection=0;  /**< 通道选择 0内置超声 1外部超声 默认0*/

	lv_ui_data_update();// 初始化图表数据

	//更新文本内容
	label_set_internal_ultrasound();
	label_set_peak_value();
	label_set_noise();
	label_set_pulse();

	label_set_y_axis_range();

	label_set_rms();
	label_set_max();
	label_set_data50hz();
	label_set_data100hz();

	label_set_attention_threshold();
	label_set_alarm_threshold();
	label_set_count_threshold();
	label_set_phase_offset();
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
