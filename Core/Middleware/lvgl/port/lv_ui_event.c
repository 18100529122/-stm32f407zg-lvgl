#include "lv_ui_event.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 屏幕 1 按钮点击事件回调
 * @param e 事件对象
 */
void screen_btn_1_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);

    if(code == LV_EVENT_CLICKED) {
        /* 获取按钮上的标签对象 (它是按钮的第一个子对象) */
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        if(label != NULL) {
            /* 获取当前文本并转换为数字 */
            const char * txt = lv_label_get_text(label);
            int count = atoi(txt);
            
            /* 数字加 1 */
            count++;
            
            /* 更新按钮上的文本 */
            lv_label_set_text_fmt(label, "%d", count);
            
            LV_LOG_USER("Button clicked! New count: %d", count);
        }
    }
}
