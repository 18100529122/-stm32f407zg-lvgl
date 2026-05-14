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


lv_obj_t * screen = NULL;
lv_obj_t * screen_chart = NULL;
lv_obj_t * screen_label_title = NULL;
lv_obj_t * screen_btn_1 = NULL;
lv_obj_t * screen_btn_1_label = NULL;
static event_table_t screen_event_table = {0};
static void register_sys_events(event_table_t *table);
static void init_states(void);
static void register_ui_events(void);
static lv_obj_t * create_ui(void);


static void register_sys_events(event_table_t *table) {
}
static void init_states(void) {
    extern lv_obj_t * global_statusbar;
    set_current_event_table(&screen_event_table);
}
static void register_ui_events(void) {
}
static lv_obj_t * create_ui(void) {
    LV_LOG_USER("Initializing screen ...");
    screen = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
    // Add style for screen - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart
    screen_chart = lv_chart_create(screen);
    lv_obj_set_x(screen_chart, 80);
    lv_obj_set_y(screen_chart, 48);
    lv_obj_set_width(screen_chart, 640);
    lv_obj_set_height(screen_chart, 384);
    lv_obj_set_scrollbar_mode(screen_chart, LV_SCROLLBAR_MODE_OFF);
    lv_chart_set_type(screen_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(screen_chart, 3, 5);
    lv_chart_set_point_count(screen_chart, 5);
    lv_chart_set_range(screen_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 500);
    lv_chart_series_t * screen_chart_series0 = lv_chart_add_series(screen_chart, lv_color_hex(0x000000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 1);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 20);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 30);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 40);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 5);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 300);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 50);
    lv_chart_set_next_value(screen_chart, screen_chart_series0, 80);
    ui_flag_modify(screen_chart, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    // Create screen_label_title
    screen_label_title = lv_label_create(screen);
    lv_obj_set_x(screen_label_title, 100);
    lv_obj_set_y(screen_label_title, 20);
    lv_obj_set_width(screen_label_title, 600);
    lv_obj_set_height(screen_label_title, 30);
    lv_obj_set_scrollbar_mode(screen_label_title, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_label_title, "LVGL TEST");
    lv_label_set_long_mode(screen_label_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_label_title, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_label_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_btn_1
    screen_btn_1 = lv_btn_create(screen);
    lv_obj_set_x(screen_btn_1, 10);
    lv_obj_set_y(screen_btn_1, 10);
    lv_obj_set_width(screen_btn_1, 50);
    lv_obj_set_height(screen_btn_1, 50);
    screen_btn_1_label = lv_label_create(screen_btn_1);
    lv_obj_set_scrollbar_mode(screen_btn_1, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_btn_1_label, "1");
    lv_obj_set_style_pad_all(screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    // Add style for screen_btn_1 - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_text_color(screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen_btn_1, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    return screen;
}
lv_obj_t * setup_screen(void) {
    if (screen != NULL) {
        init_states();
        return screen;
    }
    create_ui();
    register_ui_events();
    register_sys_events(&screen_event_table);
    init_states();
    return screen;
}
