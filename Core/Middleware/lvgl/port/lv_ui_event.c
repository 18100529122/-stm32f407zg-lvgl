#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"
#include "app_data_process.h"
#include <math.h>

extern lv_obj_t * screen_chart_label_btn;
extern lv_obj_t * screen_chart_bar_100hz;
extern lv_obj_t * screen_chart_label_100hz;
extern lv_obj_t * screen_chart_bar_50hz;
extern lv_obj_t * screen_chart_label_50hz;
extern lv_obj_t * screen_chart_bar_max;
extern lv_obj_t * screen_chart_label_max;
extern lv_obj_t * screen_chart_bar_rms;
extern lv_obj_t * screen_chart_label_rms;
extern lv_obj_t * screen_chart2_chart;

static uint8_t screen_show_type = 0;// 0: 柱状图, 1: 折线图

/**
 * @brief 根据频次获取颜色 (色标映射)
 * @param count 频次
 * @return lv_color_t 颜色
 */
static lv_color_t get_color_from_count(uint16_t count)
{
    if (count == 0) return lv_color_hex(0x000000);
    if (count < 5) return lv_color_hex(0x800000);   /* 深红 */
    if (count < 20) return lv_color_hex(0xFF0000);  /* 鲜红 */
    if (count < 50) return lv_color_hex(0xFF8000);  /* 橙色 */
    return lv_color_hex(0xFFFF00);                 /* 黄色 */
}

/**
 * @brief PRPD 图谱自定义绘图回调
 */
void prpd_chart_draw_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_DRAW_MAIN_END) {
        lv_layer_t * layer = lv_event_get_layer(e);
        
        lv_area_t chart_area;
        lv_obj_get_content_coords(obj, &chart_area);

        app_data_result_t * result = app_data_process_get_result();
        
        lv_draw_rect_dsc_t draw_dsc;
        lv_draw_rect_dsc_init(&draw_dsc);
        
        int32_t w = lv_area_get_width(&chart_area);
        int32_t h = lv_area_get_height(&chart_area);

        /* 遍历矩阵进行绘图 */
        for(int a = 0; a < TOF_AMP_BINS; a++) {
            for(int t = 0; t < TOF_TIME_BINS; t++) {
                uint16_t count = result->tof_matrix[a][t];
                if(count > 0) {
                    /* 计算屏幕坐标 */
                    /* X: 0-99 映射到 0-w */
                    /* Y: 0-39 映射到 h-0 (注意 Y 轴向下) */
                    lv_coord_t x = chart_area.x1 + (t * w) / TOF_TIME_BINS;
                    lv_coord_t y = chart_area.y2 - (a * h) / TOF_AMP_BINS;

                    draw_dsc.bg_color = get_color_from_count(count);
                    
                    lv_area_t point_area;
                    point_area.x1 = x;
                    point_area.x2 = x + 2; /* 点大小为 3x3 */
                    point_area.y1 = y - 2;
                    point_area.y2 = y;
                    
                    lv_draw_rect(layer, &draw_dsc, &point_area);
                }
            }
        }
    }
}

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
    else if(screen_show_type == 1)
    {
        if(screen_chart2_chart)
        {
            /* 填充 ADC 波形数据 (作为相位参考基准) */
            lv_chart_series_t * ser_sine = lv_chart_get_series_next(screen_chart2_chart, NULL);
            if(ser_sine) {
                for(int i = 0; i < 512; i++) {
                    /* 转换为 mV (与 ToF 矩阵相同的映射逻辑: 3000mV -> 15mV) */
                    float mv = ((float)data->adc_wave[i] * 3300.0f / 4096.0f) * 0.005f;
                    /* 放大 100 倍存入图表，以匹配 0-2000 的范围，消除阶梯感 */
                    lv_chart_set_next_value(screen_chart2_chart, ser_sine, (int16_t)(mv * 100.0f));
                }
            }

            /* 仅需使图表无效，触发 LV_EVENT_DRAW_MAIN_END 事件进行自定义绘图 */
            lv_obj_invalidate(screen_chart2_chart);
        }
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
        .data100hz_data = "0",
        .tof_matrix = NULL
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
