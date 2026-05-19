/**
 *
 * This file is created and owned by anyui.
 *
 * Version: 1.0.0
 *
 * COPYRIGHT 2026 anyui Team
 * All rights reserved.
 *
 * https://anyui.tech/
 *
 * Author: anyui Team
 */

#include "setup_ui.h"
#include "lv_ui_event.h"



lv_obj_t * screen_chart2 = NULL;
lv_obj_t * screen_chart2_chart = NULL;
lv_obj_t * screen_chart2_cont_title = NULL;
lv_obj_t * screen_chart2_btn_bar = NULL;
lv_obj_t * screen_chart2_btn_bar_label = NULL;
lv_obj_t * screen_chart2_btn_line = NULL;
lv_obj_t * screen_chart2_btn_line_label = NULL;
lv_obj_t * screen_chart2_label_btn = NULL;
static event_table_t screen_chart2_event_table = {0};
static void register_sys_events(event_table_t *table);
static void init_states(void);
static void register_ui_events(void);
static lv_obj_t * create_ui(void);


static void register_sys_events(event_table_t *table) {
}
static void init_states(void) {
    extern lv_obj_t * global_statusbar;
    set_current_event_table(&screen_chart2_event_table);
}
static void register_ui_events(void) {
    lv_obj_add_event_cb(screen_chart2_btn_bar, screen_chart_btn_bar_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(screen_chart2_btn_line, screen_chart_btn_line_event_cb, LV_EVENT_CLICKED, NULL);
}
static lv_obj_t * create_ui(void) {
    LV_LOG_USER("Initializing screen_chart2 ...");
    screen_chart2 = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(screen_chart2, LV_SCROLLBAR_MODE_OFF);
    ui_flag_modify(screen_chart2, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart2_chart
    screen_chart2_chart = lv_chart_create(screen_chart2);
    lv_obj_set_x(screen_chart2_chart, 250);
    lv_obj_set_y(screen_chart2_chart, 20);
    lv_obj_set_width(screen_chart2_chart, 500);
    lv_obj_set_height(screen_chart2_chart, 380);
    lv_obj_set_scrollbar_mode(screen_chart2_chart, LV_SCROLLBAR_MODE_OFF);
    lv_chart_set_type(screen_chart2_chart, LV_CHART_TYPE_SCATTER);
    lv_chart_set_div_line_count(screen_chart2_chart, 8, 8);
    lv_chart_set_point_count(screen_chart2_chart, 500);
    lv_chart_set_range(screen_chart2_chart, LV_CHART_AXIS_PRIMARY_X, 0, 200);
    lv_chart_set_range(screen_chart2_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 200);
    
    /* 添加红色散点序列并设置点大小 */
    lv_chart_series_t * ser = lv_chart_add_series(screen_chart2_chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_set_style_size(screen_chart2_chart, 3, 3, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(screen_chart2_chart, 0, LV_PART_ITEMS); /* 关键：设置线宽为0，只显示点 */
    
    ui_flag_modify(screen_chart2_chart, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_chart, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_chart, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_chart, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_chart, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);

    /* 为图表添加 Y 轴坐标 (幅值 mV) */
    lv_obj_t * scale_y = lv_scale_create(screen_chart2);
    lv_obj_set_size(scale_y, 60, 400);
    lv_obj_align_to(scale_y, screen_chart2_chart, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_scale_set_mode(scale_y, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_scale_set_range(scale_y, 0, 200); /* 对应 0-20.0mV */
    lv_scale_set_total_tick_count(scale_y, 21);
    lv_scale_set_major_tick_every(scale_y, 5);
    lv_scale_set_label_show(scale_y, true);
    
    static const char * y_labels[] = {"0", "5", "10", "15", "20", NULL};
    lv_scale_set_text_src(scale_y, y_labels);
    lv_obj_set_style_text_font(scale_y, &lv_font_montserrat_14, 0);

    /* 为图表添加 X 轴坐标 (时间 ms) */
    lv_obj_t * scale_x = lv_scale_create(screen_chart2);
    lv_obj_set_size(scale_x, 500, 60);
    lv_obj_align_to(scale_x, screen_chart2_chart, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_scale_set_mode(scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_scale_set_range(scale_x, 0, 200);
    lv_scale_set_total_tick_count(scale_x, 21);
    lv_scale_set_major_tick_every(scale_x, 5);
    lv_scale_set_label_show(scale_x, true);
    lv_obj_set_style_text_font(scale_x, &lv_font_montserrat_14, 0);

    /* 添加坐标轴标题 */
    lv_obj_t * label_y_title = lv_label_create(screen_chart2);
    lv_label_set_text(label_y_title, "Amplitude [mV]");
    lv_obj_set_style_text_font(label_y_title, &lv_font_montserrat_14, 0);
    lv_obj_align_to(label_y_title, scale_y, LV_ALIGN_OUT_LEFT_MID, -40, 0);
    lv_obj_set_style_transform_rotation(label_y_title, 2700, 0); /* 旋转 270 度垂直显示 */

    lv_obj_t * label_x_title = lv_label_create(screen_chart2);
    lv_label_set_text(label_x_title, "Time Interval [ms]");
    lv_obj_set_style_text_font(label_x_title, &lv_font_montserrat_14, 0);
    lv_obj_align_to(label_x_title, scale_x, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);

    // Create screen_chart2_cont_title
    screen_chart2_cont_title = lv_obj_create(screen_chart2);
    lv_obj_set_x(screen_chart2_cont_title, 0);
    lv_obj_set_y(screen_chart2_cont_title, 0);
    lv_obj_set_width(screen_chart2_cont_title, 180);
    lv_obj_set_height(screen_chart2_cont_title, 480);
    lv_obj_set_scrollbar_mode(screen_chart2_cont_title, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(screen_chart2_cont_title, LV_LAYOUT_NONE);
    // Add style for screen_chart2_cont_title - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_border_width(screen_chart2_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(screen_chart2_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart2_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart2_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart2_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart2_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart2_cont_title, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_cont_title, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_cont_title, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_cont_title, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_cont_title, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart2_btn_bar
    screen_chart2_btn_bar = lv_btn_create(screen_chart2_cont_title);
    lv_obj_set_x(screen_chart2_btn_bar, 35);
    lv_obj_set_y(screen_chart2_btn_bar, 145);
    lv_obj_set_width(screen_chart2_btn_bar, 100);
    lv_obj_set_height(screen_chart2_btn_bar, 50);
    screen_chart2_btn_bar_label = lv_label_create(screen_chart2_btn_bar);
    lv_obj_set_scrollbar_mode(screen_chart2_btn_bar, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart2_btn_bar_label, "bar");
    lv_obj_set_style_pad_all(screen_chart2_btn_bar, 0, LV_STATE_DEFAULT);
    lv_obj_align(screen_chart2_btn_bar_label, LV_ALIGN_CENTER, 0, 0);
    // Add style for screen_chart2_btn_bar - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_text_color(screen_chart2_btn_bar, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen_chart2_btn_bar, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart2_btn_bar, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart2_btn_bar, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_btn_bar, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_btn_bar, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_btn_bar, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart2_btn_line
    screen_chart2_btn_line = lv_btn_create(screen_chart2_cont_title);
    lv_obj_set_x(screen_chart2_btn_line, 35);
    lv_obj_set_y(screen_chart2_btn_line, 45);
    lv_obj_set_width(screen_chart2_btn_line, 100);
    lv_obj_set_height(screen_chart2_btn_line, 50);
    screen_chart2_btn_line_label = lv_label_create(screen_chart2_btn_line);
    lv_obj_set_scrollbar_mode(screen_chart2_btn_line, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart2_btn_line_label, "line");
    lv_obj_set_style_pad_all(screen_chart2_btn_line, 0, LV_STATE_DEFAULT);
    lv_obj_align(screen_chart2_btn_line_label, LV_ALIGN_CENTER, 0, 0);
    // Add style for screen_chart2_btn_line - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_text_color(screen_chart2_btn_line, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen_chart2_btn_line, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart2_btn_line, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart2_btn_line, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_btn_line, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_btn_line, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_btn_line, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart2_label_btn
    screen_chart2_label_btn = lv_label_create(screen_chart2_cont_title);
    lv_obj_set_x(screen_chart2_label_btn, 35);
    lv_obj_set_y(screen_chart2_label_btn, 245);
    lv_obj_set_width(screen_chart2_label_btn, 100);
    lv_obj_set_height(screen_chart2_label_btn, 50);
    lv_obj_set_scrollbar_mode(screen_chart2_label_btn, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart2_label_btn, "show line");
    lv_label_set_long_mode(screen_chart2_label_btn, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart2_label_btn, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart2_label_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart2_label_btn, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_label_btn, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_label_btn, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart2_label_btn, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    return screen_chart2;
}
lv_obj_t * setup_screen_chart2(void) {
    if (screen_chart2 != NULL) {
        init_states();
        return screen_chart2;
    }
    create_ui();
    register_ui_events();
    register_sys_events(&screen_chart2_event_table);
    init_states();
    return screen_chart2;
}
