#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"

extern lv_obj_t * screen_chart_label_btn;

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

void screen_chart_init(void)
{
    
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
