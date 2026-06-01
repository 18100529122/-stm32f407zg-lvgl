#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"
#include "app_data_process.h"
#include <math.h>
#include "elog.h"

extern lv_obj_t * screen_main_btn_tail_01;



void screen_main_btn_tail_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tail_01 clicked");
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
	}
}

void screen_main_btn_tab2_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab2 clicked");
	}
}

void screen_main_btn_tab3_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab3 clicked");
	}
}

void screen_main_btn_tab4_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab4 clicked");
	}
}

/**
 * @brief 更新图表数据
 * @param data UI 数据结构体指针
 */
void lv_ui_data_update(lv_ui_data_t *data)
{
	if (data == NULL) return;

}

/**
 * @brief 初始化图表
 * @param argument 未使用
 */
void screen_chart_init(void)
{
	lv_ui_data_t init_data = {
		.rms = 0, 
		.max = 0, 
		.data50hz = 0, 
		.data100hz = 0, 
		.rms_data = "0", 
		.max_data = "0", 
		.data50hz_data = "0", 
		.data100hz_data = "0", 
		.prpd_matrix_ptr = NULL, 
		.tof_matrix_ptr = NULL, 
		.adc_wave_ptr = NULL};
	lv_ui_data_update(&init_data);// 初始化图表数据
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
