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

#ifndef __SETUP_UI_H__
#define __SETUP_UI_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "sdk.h"
#include "animations.h"


extern lv_img_dsc_t const battery_1_30x30;


LV_FONT_DECLARE(lv_font_chinese_14_14);

lv_obj_t * setup_screen_main(void);



#ifdef __cplusplus
}
#endif
#endif
