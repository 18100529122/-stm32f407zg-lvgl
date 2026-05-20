#include "test_middleware.h"
#include "lvgl.h"
#include <stdio.h>

/**
 * @brief 运行 LVGL 测试用例
 */
void test_lvgl_widgets(void)
{
    printf("Running LVGL Test Widgets...\n");

    /* 创建一个屏幕对象 */
    lv_obj_t * screen = lv_screen_active();

    /* 创建一个按钮 */
    lv_obj_t * btn = lv_button_create(screen);
    lv_obj_set_size(btn, 200, 100);
    lv_obj_center(btn);

    /* 在按钮上添加标签 */
    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "Hello STM32!");
    lv_obj_center(label);

    /* 创建一个标题标签 */
    lv_obj_t * title = lv_label_create(screen);
    lv_label_set_text(title, "LVGL v9.2.2 Test on STM32F407");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    
    /* 设置标题样式 (可选) */
    static lv_style_t style_title;
    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, &lv_font_montserrat_26);
    lv_obj_add_style(title, &style_title, 0);
}

/**
 * @brief 测试Middleware函数，包含lvgl_widgets
 */
void Test_Middleware(void)
{
    test_lvgl_widgets();
}

