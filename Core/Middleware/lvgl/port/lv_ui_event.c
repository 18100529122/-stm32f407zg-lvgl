#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"

extern lv_obj_t * screen_chart_label_btn;
extern lv_obj_t * screen_chart_bar_100hz;
extern lv_obj_t * screen_chart_label_100hz;
extern lv_obj_t * screen_chart_bar_50hz;
extern lv_obj_t * screen_chart_label_50hz;
extern lv_obj_t * screen_chart_bar_max;
extern lv_obj_t * screen_chart_label_max;
extern lv_obj_t * screen_chart_bar_rms;
extern lv_obj_t * screen_chart_label_rms;

static uint8_t screen_show_type = 0;// 0: 柱状图, 1: 折线图

/**
 * @brief 切换为柱状图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_bar_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        //切换屏幕
        if(screen_show_type == 0)
        {
            return;
        }
        lv_obj_t * screen_chart = setup_screen_chart();
        screen_show_type = 0;
        lv_scr_load(screen_chart);
    }
}

/**
 * @brief 切换为折线图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_line_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        //切换屏幕
        if(screen_show_type == 1)
        {
            return;
        }
        lv_obj_t * screen_chart = setup_screen_chart2();
        screen_show_type = 1;
        lv_scr_load(screen_chart);
    }
}

/**
 * @brief 更新图表数据
 * @param data UI 数据结构体指针
 */
void lv_ui_data_update(lv_ui_data_t * data)
{
    if(data == NULL) return;

    if(screen_show_type == 0)
    {
        lv_bar_set_value(screen_chart_bar_rms, data->rms, LV_ANIM_OFF);
        lv_bar_set_value(screen_chart_bar_max, data->max, LV_ANIM_OFF);
        lv_bar_set_value(screen_chart_bar_50hz, data->data50hz, LV_ANIM_OFF);
        lv_bar_set_value(screen_chart_bar_100hz, data->data100hz, LV_ANIM_OFF);
        
        lv_label_set_text(screen_chart_label_rms, data->rms_data);
        lv_label_set_text(screen_chart_label_max, data->max_data);
        lv_label_set_text(screen_chart_label_50hz, data->data50hz_data);
        lv_label_set_text(screen_chart_label_100hz, data->data100hz_data);
    }
    else
    {
        // 折线图数据更新
    }
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
        .data100hz_data = "0"
    };
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
void lv_ui_refresh(void)
{

}
