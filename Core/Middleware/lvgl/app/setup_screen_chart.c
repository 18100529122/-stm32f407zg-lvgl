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
lv_obj_t * screen_chart_cont_show = NULL;
lv_obj_t * screen_chart_cont_100hz = NULL;
lv_obj_t * screen_chart_bar_100hz = NULL;
lv_obj_t * screen_chart_label_100hz = NULL;
lv_obj_t * screen_chart_label_100hz_title = NULL;
lv_obj_t * screen_chart_cont_50hz = NULL;
lv_obj_t * screen_chart_bar_50hz = NULL;
lv_obj_t * screen_chart_label_50hz = NULL;
lv_obj_t * screen_chart_label_50hz_title = NULL;
lv_obj_t * screen_chart_cont_max = NULL;
lv_obj_t * screen_chart_bar_max = NULL;
lv_obj_t * screen_chart_label_max = NULL;
lv_obj_t * screen_chart_label_max_title = NULL;
lv_obj_t * screen_chart_cont_rms = NULL;
lv_obj_t * screen_chart_bar_rms = NULL;
lv_obj_t * screen_chart_label_rms = NULL;
lv_obj_t * screen_chart_label_rms_title = NULL;
lv_obj_t * screen_chart_cont_title = NULL;
lv_obj_t * screen_chart_btn_bar = NULL;
lv_obj_t * screen_chart_btn_bar_label = NULL;
lv_obj_t * screen_chart_btn_line = NULL;
lv_obj_t * screen_chart_btn_line_label = NULL;
lv_obj_t * screen_chart_label_btn = NULL;
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
    // Create screen_chart_cont_show
    screen_chart_cont_show = lv_obj_create(screen_chart);
    lv_obj_set_x(screen_chart_cont_show, 180);
    lv_obj_set_y(screen_chart_cont_show, 0);
    lv_obj_set_width(screen_chart_cont_show, 620);
    lv_obj_set_height(screen_chart_cont_show, 480);
    lv_obj_set_scrollbar_mode(screen_chart_cont_show, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(screen_chart_cont_show, LV_LAYOUT_NONE);
    // Add style for screen_chart_cont_show - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_border_width(screen_chart_cont_show, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart_cont_show, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart_cont_show, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart_cont_show, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart_cont_show, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_cont_100hz
    screen_chart_cont_100hz = lv_obj_create(screen_chart_cont_show);
    lv_obj_set_x(screen_chart_cont_100hz, 0);
    lv_obj_set_y(screen_chart_cont_100hz, 360);
    lv_obj_set_width(screen_chart_cont_100hz, 620);
    lv_obj_set_height(screen_chart_cont_100hz, 120);
    lv_obj_set_scrollbar_mode(screen_chart_cont_100hz, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(screen_chart_cont_100hz, LV_LAYOUT_NONE);
    // Add style for screen_chart_cont_100hz - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_border_width(screen_chart_cont_100hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(screen_chart_cont_100hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart_cont_100hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart_cont_100hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart_cont_100hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart_cont_100hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_bar_100hz
    screen_chart_bar_100hz = lv_bar_create(screen_chart_cont_100hz);
    lv_obj_set_x(screen_chart_bar_100hz, 30);
    lv_obj_set_y(screen_chart_bar_100hz, 30);
    lv_obj_set_width(screen_chart_bar_100hz, 500);
    lv_obj_set_height(screen_chart_bar_100hz, 20);
    lv_obj_set_scrollbar_mode(screen_chart_bar_100hz, LV_SCROLLBAR_MODE_OFF);
    lv_bar_set_value(screen_chart_bar_100hz, 20, LV_ANIM_OFF);
    // Add style for screen_chart_bar_100hz - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_100hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Add style for screen_chart_bar_100hz - LV_PART_INDICATOR | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_100hz, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_bar_100hz, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_100hz, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_100hz, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_100hz, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_100hz, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_100hz
    screen_chart_label_100hz = lv_label_create(screen_chart_cont_100hz);
    lv_obj_set_x(screen_chart_label_100hz, 535);
    lv_obj_set_y(screen_chart_label_100hz, 30);
    lv_obj_set_width(screen_chart_label_100hz, 60);
    lv_obj_set_height(screen_chart_label_100hz, 20);
    lv_obj_set_scrollbar_mode(screen_chart_label_100hz, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_100hz, "number");
    lv_label_set_long_mode(screen_chart_label_100hz, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_100hz, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_100hz, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_label_100hz, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_100hz, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_100hz, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_100hz, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_100hz_title
    screen_chart_label_100hz_title = lv_label_create(screen_chart_cont_100hz);
    lv_obj_set_x(screen_chart_label_100hz_title, 200);
    lv_obj_set_y(screen_chart_label_100hz_title, 80);
    lv_obj_set_width(screen_chart_label_100hz_title, 150);
    lv_obj_set_height(screen_chart_label_100hz_title, 30);
    lv_obj_set_scrollbar_mode(screen_chart_label_100hz_title, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_100hz_title, "frequency[100] [mV]");
    lv_label_set_long_mode(screen_chart_label_100hz_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_100hz_title, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_100hz_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_cont_50hz
    screen_chart_cont_50hz = lv_obj_create(screen_chart_cont_show);
    lv_obj_set_x(screen_chart_cont_50hz, 0);
    lv_obj_set_y(screen_chart_cont_50hz, 240);
    lv_obj_set_width(screen_chart_cont_50hz, 620);
    lv_obj_set_height(screen_chart_cont_50hz, 120);
    lv_obj_set_scrollbar_mode(screen_chart_cont_50hz, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(screen_chart_cont_50hz, LV_LAYOUT_NONE);
    // Add style for screen_chart_cont_50hz - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_border_width(screen_chart_cont_50hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(screen_chart_cont_50hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart_cont_50hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart_cont_50hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart_cont_50hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart_cont_50hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_bar_50hz
    screen_chart_bar_50hz = lv_bar_create(screen_chart_cont_50hz);
    lv_obj_set_x(screen_chart_bar_50hz, 30);
    lv_obj_set_y(screen_chart_bar_50hz, 30);
    lv_obj_set_width(screen_chart_bar_50hz, 500);
    lv_obj_set_height(screen_chart_bar_50hz, 20);
    lv_obj_set_scrollbar_mode(screen_chart_bar_50hz, LV_SCROLLBAR_MODE_OFF);
    lv_bar_set_value(screen_chart_bar_50hz, 20, LV_ANIM_OFF);
    // Add style for screen_chart_bar_50hz - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_50hz, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Add style for screen_chart_bar_50hz - LV_PART_INDICATOR | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_50hz, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_bar_50hz, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_50hz, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_50hz, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_50hz, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_50hz, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_50hz
    screen_chart_label_50hz = lv_label_create(screen_chart_cont_50hz);
    lv_obj_set_x(screen_chart_label_50hz, 535);
    lv_obj_set_y(screen_chart_label_50hz, 30);
    lv_obj_set_width(screen_chart_label_50hz, 60);
    lv_obj_set_height(screen_chart_label_50hz, 20);
    lv_obj_set_scrollbar_mode(screen_chart_label_50hz, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_50hz, "number");
    lv_label_set_long_mode(screen_chart_label_50hz, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_50hz, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_50hz, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_label_50hz, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_50hz, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_50hz, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_50hz, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_50hz_title
    screen_chart_label_50hz_title = lv_label_create(screen_chart_cont_50hz);
    lv_obj_set_x(screen_chart_label_50hz_title, 200);
    lv_obj_set_y(screen_chart_label_50hz_title, 80);
    lv_obj_set_width(screen_chart_label_50hz_title, 150);
    lv_obj_set_height(screen_chart_label_50hz_title, 30);
    lv_obj_set_scrollbar_mode(screen_chart_label_50hz_title, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_50hz_title, "frequency[50] [mV]");
    lv_label_set_long_mode(screen_chart_label_50hz_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_50hz_title, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_50hz_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_cont_max
    screen_chart_cont_max = lv_obj_create(screen_chart_cont_show);
    lv_obj_set_x(screen_chart_cont_max, 0);
    lv_obj_set_y(screen_chart_cont_max, 120);
    lv_obj_set_width(screen_chart_cont_max, 620);
    lv_obj_set_height(screen_chart_cont_max, 120);
    lv_obj_set_scrollbar_mode(screen_chart_cont_max, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(screen_chart_cont_max, LV_LAYOUT_NONE);
    // Add style for screen_chart_cont_max - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_border_width(screen_chart_cont_max, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(screen_chart_cont_max, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart_cont_max, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart_cont_max, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart_cont_max, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart_cont_max, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_bar_max
    screen_chart_bar_max = lv_bar_create(screen_chart_cont_max);
    lv_obj_set_x(screen_chart_bar_max, 30);
    lv_obj_set_y(screen_chart_bar_max, 30);
    lv_obj_set_width(screen_chart_bar_max, 500);
    lv_obj_set_height(screen_chart_bar_max, 20);
    lv_obj_set_scrollbar_mode(screen_chart_bar_max, LV_SCROLLBAR_MODE_OFF);
    lv_bar_set_value(screen_chart_bar_max, 20, LV_ANIM_OFF);
    // Add style for screen_chart_bar_max - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_max, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Add style for screen_chart_bar_max - LV_PART_INDICATOR | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_max, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_bar_max, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_max, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_max, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_max, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_max, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_max
    screen_chart_label_max = lv_label_create(screen_chart_cont_max);
    lv_obj_set_x(screen_chart_label_max, 535);
    lv_obj_set_y(screen_chart_label_max, 30);
    lv_obj_set_width(screen_chart_label_max, 60);
    lv_obj_set_height(screen_chart_label_max, 20);
    lv_obj_set_scrollbar_mode(screen_chart_label_max, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_max, "number");
    lv_label_set_long_mode(screen_chart_label_max, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_max, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_max, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_label_max, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_max, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_max, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_max, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_max_title
    screen_chart_label_max_title = lv_label_create(screen_chart_cont_max);
    lv_obj_set_x(screen_chart_label_max_title, 200);
    lv_obj_set_y(screen_chart_label_max_title, 80);
    lv_obj_set_width(screen_chart_label_max_title, 150);
    lv_obj_set_height(screen_chart_label_max_title, 30);
    lv_obj_set_scrollbar_mode(screen_chart_label_max_title, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_max_title, "max [mV]");
    lv_label_set_long_mode(screen_chart_label_max_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_max_title, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_max_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_cont_rms
    screen_chart_cont_rms = lv_obj_create(screen_chart_cont_show);
    lv_obj_set_x(screen_chart_cont_rms, 0);
    lv_obj_set_y(screen_chart_cont_rms, 0);
    lv_obj_set_width(screen_chart_cont_rms, 620);
    lv_obj_set_height(screen_chart_cont_rms, 120);
    lv_obj_set_scrollbar_mode(screen_chart_cont_rms, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(screen_chart_cont_rms, LV_LAYOUT_NONE);
    // Add style for screen_chart_cont_rms - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_border_width(screen_chart_cont_rms, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(screen_chart_cont_rms, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart_cont_rms, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart_cont_rms, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart_cont_rms, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart_cont_rms, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_bar_rms
    screen_chart_bar_rms = lv_bar_create(screen_chart_cont_rms);
    lv_obj_set_x(screen_chart_bar_rms, 30);
    lv_obj_set_y(screen_chart_bar_rms, 30);
    lv_obj_set_width(screen_chart_bar_rms, 500);
    lv_obj_set_height(screen_chart_bar_rms, 20);
    lv_obj_set_scrollbar_mode(screen_chart_bar_rms, LV_SCROLLBAR_MODE_OFF);
    lv_bar_set_value(screen_chart_bar_rms, 20, LV_ANIM_OFF);
    // Add style for screen_chart_bar_rms - LV_PART_MAIN | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_rms, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Add style for screen_chart_bar_rms - LV_PART_INDICATOR | LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_chart_bar_rms, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_bar_rms, LV_OBJ_FLAG_CLICKABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_rms, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_rms, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_rms, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_bar_rms, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_rms
    screen_chart_label_rms = lv_label_create(screen_chart_cont_rms);
    lv_obj_set_x(screen_chart_label_rms, 535);
    lv_obj_set_y(screen_chart_label_rms, 30);
    lv_obj_set_width(screen_chart_label_rms, 60);
    lv_obj_set_height(screen_chart_label_rms, 20);
    lv_obj_set_scrollbar_mode(screen_chart_label_rms, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_rms, "number");
    lv_label_set_long_mode(screen_chart_label_rms, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_rms, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_rms, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_flag_modify(screen_chart_label_rms, LV_OBJ_FLAG_SNAPPABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_rms, LV_OBJ_FLAG_CLICK_FOCUSABLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_rms, LV_OBJ_FLAG_GESTURE_BUBBLE, UI_FLAG_ACTION_REMOVE);
    ui_flag_modify(screen_chart_label_rms, LV_OBJ_FLAG_PRESS_LOCK, UI_FLAG_ACTION_REMOVE);
    // Create screen_chart_label_rms_title
    screen_chart_label_rms_title = lv_label_create(screen_chart_cont_rms);
    lv_obj_set_x(screen_chart_label_rms_title, 200);
    lv_obj_set_y(screen_chart_label_rms_title, 80);
    lv_obj_set_width(screen_chart_label_rms_title, 150);
    lv_obj_set_height(screen_chart_label_rms_title, 30);
    lv_obj_set_scrollbar_mode(screen_chart_label_rms_title, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_rms_title, "virtual valu [mV]");
    lv_label_set_long_mode(screen_chart_label_rms_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_rms_title, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_rms_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
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
    lv_obj_set_style_radius(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_chart_cont_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Create screen_chart_btn_bar
    screen_chart_btn_bar = lv_btn_create(screen_chart_cont_title);
    lv_obj_set_x(screen_chart_btn_bar, 35);
    lv_obj_set_y(screen_chart_btn_bar, 145);
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
    // Create screen_chart_label_btn
    screen_chart_label_btn = lv_label_create(screen_chart_cont_title);
    lv_obj_set_x(screen_chart_label_btn, 35);
    lv_obj_set_y(screen_chart_label_btn, 245);
    lv_obj_set_width(screen_chart_label_btn, 100);
    lv_obj_set_height(screen_chart_label_btn, 50);
    lv_obj_set_scrollbar_mode(screen_chart_label_btn, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_chart_label_btn, "show bar");
    lv_label_set_long_mode(screen_chart_label_btn, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(screen_chart_label_btn, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_chart_label_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
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
