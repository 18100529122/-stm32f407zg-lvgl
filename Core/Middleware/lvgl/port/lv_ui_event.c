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

/**
 * @brief 切换为柱状图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_bar_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        lv_label_set_text(screen_chart_label_btn, "show bar");
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
        lv_label_set_text(screen_chart_label_btn, "show line");
    }
}

/**
 * @brief 更新图表数据
 * @param rms RMS 值
 * @param max 最大值
 * @param data50hz 50Hz 值
 * @param data100hz 100Hz 值
 * @param rms_data RMS 值数据
 * @param max_data 最大值数据
 * @param data50hz_data 50Hz 值数据
 * @param data100hz_data 100Hz 值数据
 */
void lv_ui_data_update(uint8_t rms,uint8_t max,uint8_t data50hz,uint8_t data100hz,char * rms_data,char * max_data,char * data50hz_data,char * data100hz_data)
{
    lv_bar_set_value(screen_chart_bar_rms, rms, LV_ANIM_OFF);
    lv_bar_set_value(screen_chart_bar_max, max, LV_ANIM_OFF);
    lv_bar_set_value(screen_chart_bar_50hz, data50hz, LV_ANIM_OFF);
    lv_bar_set_value(screen_chart_bar_100hz, data100hz, LV_ANIM_OFF);
    
    lv_label_set_text(screen_chart_label_rms, rms_data);
    lv_label_set_text(screen_chart_label_max, max_data);
    lv_label_set_text(screen_chart_label_50hz, data50hz_data);
    lv_label_set_text(screen_chart_label_100hz, data100hz_data);
}

/**
 * @brief 初始化图表
 * @param argument 未使用
 */
void screen_chart_init(void)
{
    lv_ui_data_update(0,0,0,0,"0","0","0","0");// 初始化图表数据
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
