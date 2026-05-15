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


lv_obj_t * screen_chart = NULL;
lv_obj_t * screen_chart_cont_title = NULL;
lv_obj_t * screen_chart_btn_bar = NULL;
lv_obj_t * screen_chart_btn_bar_label = NULL;
lv_obj_t * screen_chart_btn_line = NULL;
lv_obj_t * screen_chart_btn_line_label = NULL;
lv_obj_t * screen_chart_chart_line = NULL;
lv_obj_t * screen_chart_chart_bar = NULL;
static event_table_t screen_chart_event_table = {0};
static void register_sys_events(event_table_t *table);
static void init_states(void);
static void register_ui_events(void);
static lv_obj_t * create_ui(void);


static void register_sys_events(event_table_t *table) {
}
static void init_states(void) {
    extern lv_obj_t * global_statusbar;
    set_current_event_table(&screen_chart_event_table);
}
static void register_ui_events(void) {
    lv_obj_add_event_cb(screen_chart_btn_bar, screen_chart_btn_bar_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(screen_chart_btn_line, screen_chart_btn_line_event_cb, LV_EVENT_CLICKED, NULL);
}
static lv_obj_t * create_ui(void) {
    LV_LOG_USER("Initializing screen_chart ...");
    screen_chart = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(screen_chart, LV_SCROLLBAR_MODE_OFF);
    // Add style for screen_chart - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(screen_chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_cont_title
    screen_chart_cont_title = lv_obj_create(screen_chart);
    lv_obj_set_x(screen_chart_cont_title, 0);
    lv_obj_set_y(screen_chart_cont_title, 0);
    lv_obj_set_width(screen_chart_cont_title, 180);
    lv_obj_set_height(screen_chart_cont_title, 480);
    lv_obj_set_scrollbar_mode(screen_chart_cont_title, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(screen_chart_cont_title, LV_LAYOUT_NONE);
    // Add style for screen_chart_cont_title - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_border_width(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_btn_bar
    screen_chart_btn_bar = lv_btn_create(screen_chart_cont_title);
    lv_obj_set_x(screen_chart_btn_bar, 35);
    lv_obj_set_y(screen_chart_btn_bar, 135);
    lv_obj_set_width(screen_chart_btn_bar, 100);
    lv_obj_set_height(screen_chart_btn_bar, 50);
    screen_chart_btn_bar_label = lv_label_create(screen_chart_btn_bar);
    lv_obj_set_scrollbar_mode(screen_chart_btn_bar, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_btn_bar_label, "bar");
    lv_obj_set_style_pad_all(screen_chart_btn_bar, 0, LV_STATE_DEFAULT);
    lv_obj_align(screen_chart_btn_bar_label, LV_ALIGN_CENTER, 0, 0);
    // Add style for screen_chart_btn_bar - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_text_color(screen_chart_btn_bar, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen_chart_btn_bar, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_btn_bar, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_btn_line
    screen_chart_btn_line = lv_btn_create(screen_chart_cont_title);
    lv_obj_set_x(screen_chart_btn_line, 35);
    lv_obj_set_y(screen_chart_btn_line, 45);
    lv_obj_set_width(screen_chart_btn_line, 100);
    lv_obj_set_height(screen_chart_btn_line, 50);
    screen_chart_btn_line_label = lv_label_create(screen_chart_btn_line);
    lv_obj_set_scrollbar_mode(screen_chart_btn_line, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_btn_line_label, "line");
    lv_obj_set_style_pad_all(screen_chart_btn_line, 0, LV_STATE_DEFAULT);
    lv_obj_align(screen_chart_btn_line_label, LV_ALIGN_CENTER, 0, 0);
    // Add style for screen_chart_btn_line - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_text_color(screen_chart_btn_line, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen_chart_btn_line, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_btn_line, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_chart_line
    screen_chart_chart_line = lv_chart_create(screen_chart);
    lv_obj_set_x(screen_chart_chart_line, 190);
    lv_obj_set_y(screen_chart_chart_line, 48);
    lv_obj_set_width(screen_chart_chart_line, 600);
    lv_obj_set_height(screen_chart_chart_line, 384);
    lv_obj_set_scrollbar_mode(screen_chart_chart_line, LV_SCROLLBAR_MODE_OFF);
    lv_chart_set_type(screen_chart_chart_line, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(screen_chart_chart_line, 10, 10);
    lv_chart_set_point_count(screen_chart_chart_line, 50);
    lv_chart_set_range(screen_chart_chart_line, LV_CHART_AXIS_PRIMARY_Y, 0, 3000);
    ui_flag_modify(screen_chart_chart_line, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_chart_bar
    screen_chart_chart_bar = lv_chart_create(screen_chart);
    lv_obj_set_x(screen_chart_chart_bar, 190);
    lv_obj_set_y(screen_chart_chart_bar, 48);
    lv_obj_set_width(screen_chart_chart_bar, 600);
    lv_obj_set_height(screen_chart_chart_bar, 384);
    lv_obj_set_scrollbar_mode(screen_chart_chart_bar, LV_SCROLLBAR_MODE_OFF);
    lv_chart_set_type(screen_chart_chart_bar, LV_CHART_TYPE_BAR);
    lv_chart_set_div_line_count(screen_chart_chart_bar, 10, 10);
    lv_chart_set_point_count(screen_chart_chart_bar, 10);
    lv_chart_set_range(screen_chart_chart_bar, LV_CHART_AXIS_PRIMARY_Y, 0, 3000);
    ui_flag_modify(screen_chart_chart_bar, LV_OBJ_FLAG_HIDDEN, UI_FLAG_ACTION_ADD);
    ui_flag_modify(screen_chart_chart_bar, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    return screen_chart;
}
lv_obj_t * setup_screen_chart(void) {
    if (screen_chart != NULL) {
        init_states();
        return screen_chart;
    }
    create_ui();
    register_ui_events();
    register_sys_events(&screen_chart_event_table);
    init_states();
    return screen_chart;
}
