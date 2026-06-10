#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"
#include "app_data_process.h"
#include <math.h>
#include "stdio.h"
#include "elog.h"


extern lv_obj_t * screen_main;
extern lv_obj_t * screen_main_cont_main_set;
extern lv_obj_t * screen_main_cont_main_set_09;
extern lv_obj_t * screen_main_label_set_09_01;
extern lv_obj_t * screen_main_btn_set_09_01;
extern lv_obj_t * screen_main_btn_set_09_01_label;
extern lv_obj_t * screen_main_btn_set_09_02;
extern lv_obj_t * screen_main_btn_set_09_02_label;
extern lv_obj_t * screen_main_cont_main_set_08;
extern lv_obj_t * screen_main_label_set_08_01;
extern lv_obj_t * screen_main_btn_set_08_01;
extern lv_obj_t * screen_main_btn_set_08_01_label;
extern lv_obj_t * screen_main_btn_set_08_02;
extern lv_obj_t * screen_main_btn_set_08_02_label;
extern lv_obj_t * screen_main_btn_set_08_03;
extern lv_obj_t * screen_main_btn_set_08_03_label;
extern lv_obj_t * screen_main_cont_main_set_07;
extern lv_obj_t * screen_main_label_set_07_01;
extern lv_obj_t * screen_main_btn_set_07_01;
extern lv_obj_t * screen_main_btn_set_07_01_label;
extern lv_obj_t * screen_main_btn_set_07_02;
extern lv_obj_t * screen_main_btn_set_07_02_label;
extern lv_obj_t * screen_main_cont_main_set_06;
extern lv_obj_t * screen_main_label_set_06_01;
extern lv_obj_t * screen_main_btn_set_06_01;
extern lv_obj_t * screen_main_btn_set_06_01_label;
extern lv_obj_t * screen_main_btn_set_06_02;
extern lv_obj_t * screen_main_btn_set_06_02_label;
extern lv_obj_t * screen_main_btn_set_06_03;
extern lv_obj_t * screen_main_btn_set_06_03_label;
extern lv_obj_t * screen_main_cont_main_set_05;
extern lv_obj_t * screen_main_label_set_05_01;
extern lv_obj_t * screen_main_btn_set_05_01;
extern lv_obj_t * screen_main_btn_set_05_01_label;
extern lv_obj_t * screen_main_btn_set_05_02;
extern lv_obj_t * screen_main_btn_set_05_02_label;
extern lv_obj_t * screen_main_cont_main_set_04;
extern lv_obj_t * screen_main_label_set_04_01;
extern lv_obj_t * screen_main_slider_set_04_01;
extern lv_obj_t * screen_main_label_set_04_02;
extern lv_obj_t * screen_main_label_set_04_03;
extern lv_obj_t * screen_main_cont_main_set_03;
extern lv_obj_t * screen_main_label_set_03_01;
extern lv_obj_t * screen_main_slider_set_03_01;
extern lv_obj_t * screen_main_label_set_03_02;
extern lv_obj_t * screen_main_label_set_03_03;
extern lv_obj_t * screen_main_cont_main_set_02;
extern lv_obj_t * screen_main_label_set_02_01;
extern lv_obj_t * screen_main_slider_set_02_01;
extern lv_obj_t * screen_main_label_set_02_02;
extern lv_obj_t * screen_main_label_set_02_03;
extern lv_obj_t * screen_main_cont_main_set_01;
extern lv_obj_t * screen_main_label_set_01_01;
extern lv_obj_t * screen_main_slider_set_01_01;
extern lv_obj_t * screen_main_label_set_01_02;
extern lv_obj_t * screen_main_label_set_01_03;
extern lv_obj_t * screen_main_cont_main_set_tail;
extern lv_obj_t * screen_main_label_set_tail_01;
extern lv_obj_t * screen_main_btn_set_tail_01;
extern lv_obj_t * screen_main_btn_set_tail_01_label;
extern lv_obj_t * screen_main_cont_main_show;
extern lv_obj_t * screen_main_cont_tail;
extern lv_obj_t * screen_main_label_tail_01;
extern lv_obj_t * screen_main_label_tail_02;
extern lv_obj_t * screen_main_label_tail_03;
extern lv_obj_t * screen_main_label_tail_04;
extern lv_obj_t * screen_main_label_tail_05;
extern lv_obj_t * screen_main_label_tail_06;
extern lv_obj_t * screen_main_btn_tail_01;
extern lv_obj_t * screen_main_btn_tail_01_label;
extern lv_obj_t * screen_main_cont_show_tab2;
extern lv_obj_t * screen_main_cont_a1eThAfj;
extern lv_obj_t * screen_main_bar_show_tab2_1;
extern lv_obj_t * screen_main_label_show_tab2_11;
extern lv_obj_t * screen_main_label_show_tab2_12;
extern lv_obj_t * screen_main_label_show_tab2_13;
extern lv_obj_t * screen_main_cont_zqAwibOK;
extern lv_obj_t * screen_main_bar_show_tab2_2;
extern lv_obj_t * screen_main_label_show_tab2_21;
extern lv_obj_t * screen_main_label_show_tab2_22;
extern lv_obj_t * screen_main_label_show_tab2_23;
extern lv_obj_t * screen_main_cont_sYPD6Gkz;
extern lv_obj_t * screen_main_bar_show_tab2_3;
extern lv_obj_t * screen_main_label_show_tab2_31;
extern lv_obj_t * screen_main_label_show_tab2_32;
extern lv_obj_t * screen_main_label_show_tab2_33;
extern lv_obj_t * screen_main_cont_Mif8nq4s;
extern lv_obj_t * screen_main_bar_show_tab2_4;
extern lv_obj_t * screen_main_label_show_tab2_41;
extern lv_obj_t * screen_main_label_show_tab2_42;
extern lv_obj_t * screen_main_label_show_tab2_43;
extern lv_obj_t * screen_main_cont_show_tab1;
extern lv_obj_t * screen_main_chart_show_tab1;
extern lv_obj_t * screen_main_btn_show_tab1_1;
extern lv_obj_t * screen_main_btn_show_tab1_1_label;
extern lv_obj_t * screen_main_btn_show_tab1_2;
extern lv_obj_t * screen_main_btn_show_tab1_2_label;
extern lv_obj_t * screen_main_label_show_tab1;
extern lv_obj_t * screen_main_cont_tab;
extern lv_obj_t * screen_main_btn_tab1;
extern lv_obj_t * screen_main_btn_tab1_label;
extern lv_obj_t * screen_main_btn_tab2;
extern lv_obj_t * screen_main_btn_tab2_label;
extern lv_obj_t * screen_main_btn_tab3;
extern lv_obj_t * screen_main_btn_tab3_label;
extern lv_obj_t * screen_main_btn_tab4;
extern lv_obj_t * screen_main_btn_tab4_label;
extern lv_obj_t * screen_main_cont_menu1;
extern lv_obj_t * screen_main_cont_menu3;
extern lv_obj_t * screen_main_label_menu3_num1;
extern lv_obj_t * screen_main_label_menu3_num2;
extern lv_obj_t * screen_main_label_menu3_num3;
extern lv_obj_t * screen_main_cont_menu2;
extern lv_obj_t * screen_main_label_menu2_3;
extern lv_obj_t * screen_main_label_menu2_2;
extern lv_obj_t * screen_main_label_menu2_1;
extern lv_obj_t * screen_main_label_menu1;
extern lv_obj_t * screen_main_cont_title1;
extern lv_obj_t * screen_main_label_time1;
extern lv_obj_t * screen_main_img_battery1;

lv_ui_data_t lv_ui_data={0};

lv_obj_t * screen_main_chart_scale_y = NULL;
lv_obj_t * screen_main_chart_scale_x = NULL;
#include "app_data_process.h"
#include <stdbool.h> // 添加此行以支持 bool 类型

static void update_chart_y_axis_and_labels(lv_obj_t * chart_obj, lv_obj_t * scale_y_obj) {
    int32_t current_y_range_val = lv_ui_data.y_axis_range;
    int32_t y_min = current_y_range_val * -50;
    int32_t y_max = current_y_range_val * 50;

    // Apply global limits
    if (y_max > Y_AXIS_GLOBAL_MAX) y_max = Y_AXIS_GLOBAL_MAX;
    if (y_min < Y_AXIS_GLOBAL_MIN) y_min = Y_AXIS_GLOBAL_MIN;

    lv_chart_set_range(chart_obj, LV_CHART_AXIS_PRIMARY_Y, y_min, y_max);
    lv_scale_set_range(scale_y_obj, y_min, y_max);

    static char y_labels_buf[3][16];
    lv_snprintf(y_labels_buf[0], sizeof(y_labels_buf[0]), "%d", y_min);
    lv_snprintf(y_labels_buf[1], sizeof(y_labels_buf[1]), "0");
    lv_snprintf(y_labels_buf[2], sizeof(y_labels_buf[2]), "%d", y_max);
    static const char * dynamic_y_labels_str[] = {y_labels_buf[0], y_labels_buf[1], y_labels_buf[2], NULL};
    lv_scale_set_text_src(scale_y_obj, dynamic_y_labels_str);

    lv_obj_invalidate(scale_y_obj); // Force redraw of the scale to apply new labels
    lv_chart_refresh(chart_obj); // Refresh chart to update data display if needed
}

static void chart_style_init(lv_obj_t * chart_obj)//图表样式初始化 只需要设置一次的值
{
	lv_chart_set_update_mode(chart_obj, LV_CHART_UPDATE_MODE_CIRCULAR);//循环更新数据
	lv_chart_set_range(chart_obj,LV_CHART_AXIS_PRIMARY_X, 0, 100);//设置X轴范围
	lv_chart_set_range(chart_obj,LV_CHART_AXIS_PRIMARY_Y, -50*lv_ui_data.y_axis_range, 50*lv_ui_data.y_axis_range);//设置Y轴范围
    lv_chart_set_div_line_count(chart_obj, 11, 9);//设置X轴和Y轴的分线数量 (Y轴11条线对应10个间隔，X轴9条线对应8个间隔)

    lv_obj_t * chart_parent = lv_obj_get_parent(chart_obj);

    // 获取 Chart 的完整尺寸、内容尺寸和内边距
    lv_coord_t chart_full_width = lv_obj_get_width(chart_obj);
    lv_coord_t chart_full_height = lv_obj_get_height(chart_obj);
    lv_coord_t chart_content_width = lv_obj_get_content_width(chart_obj);
    lv_coord_t chart_content_height = lv_obj_get_content_height(chart_obj);
    lv_coord_t pad_left = lv_obj_get_style_pad_left(chart_obj, LV_PART_MAIN);
    lv_coord_t pad_top = lv_obj_get_style_pad_top(chart_obj, LV_PART_MAIN);
    lv_coord_t pad_bottom = lv_obj_get_style_pad_bottom(chart_obj, LV_PART_MAIN);

    // 计算 Y 轴 scale 的垂直偏移量，使其中心与 Chart 内容区域的中心对齐
    lv_coord_t y_offset_for_align_to = (pad_top + chart_content_height / 2) - (chart_full_height / 2);

    // 创建 Y 轴刻度
    screen_main_chart_scale_y = lv_scale_create(chart_parent);
    lv_obj_set_size(screen_main_chart_scale_y, 60, chart_content_height); // 高度匹配 Chart 内容高度
    lv_obj_align_to(screen_main_chart_scale_y, chart_obj, LV_ALIGN_OUT_LEFT_MID, -5 - pad_left, y_offset_for_align_to); // 调整 y 偏移
    lv_scale_set_mode(screen_main_chart_scale_y, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_scale_set_total_tick_count(screen_main_chart_scale_y, 3); // 3 labels (2 intervals)
    lv_scale_set_major_tick_every(screen_main_chart_scale_y, 1); // Every tick is a major tick
    lv_scale_set_label_show(screen_main_chart_scale_y, true);
    lv_obj_set_style_text_font(screen_main_chart_scale_y, &lv_font_chinese_14_14, 0);

    // Call after scale_y is created and before chart_refresh to initialize range and labels
    update_chart_y_axis_and_labels(chart_obj, screen_main_chart_scale_y);

    // 计算 X 轴 scale 的水平偏移量，使其中心与 Chart 内容区域的中心对齐
    lv_coord_t x_offset_for_align_to = (pad_left + chart_content_width / 2) - (chart_full_width / 2);

    // 创建 X 轴刻度
    screen_main_chart_scale_x = lv_scale_create(chart_parent);
    lv_obj_set_size(screen_main_chart_scale_x, chart_content_width, 60); // 宽度匹配 Chart 内容宽度
    lv_obj_align_to(screen_main_chart_scale_x, chart_obj, LV_ALIGN_OUT_BOTTOM_MID, x_offset_for_align_to, 5 + pad_bottom); // 调整 x 偏移
    lv_scale_set_mode(screen_main_chart_scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_scale_set_range(screen_main_chart_scale_x, 0, 100);
    lv_scale_set_total_tick_count(screen_main_chart_scale_x, 5); // 5 labels (4 intervals)
    lv_scale_set_major_tick_every(screen_main_chart_scale_x, 1); // Every tick is a major tick
    lv_scale_set_label_show(screen_main_chart_scale_x, true);
    static const char * x_labels_str[] = {"0", "25", "50", "75", "100", NULL};
    lv_scale_set_text_src(screen_main_chart_scale_x, x_labels_str);
    lv_obj_set_style_text_font(screen_main_chart_scale_x, &lv_font_chinese_14_14, 0);

}

// 图表样式
static void chart_set_style(void)
{
	//清除图表数据
	
	//设置样式
	if(lv_ui_data.chart_selection==0)	//脉冲波形	折线图
	{
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_LINE);//折线图

		
	}
	else if(lv_ui_data.chart_selection==1)//PRPD图	散点
	{
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_SCATTER);
	}
	else if(lv_ui_data.chart_selection==2)//四要素 无
	{
		
	}
	else if(lv_ui_data.chart_selection==3)//飞行图 散点
	{
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_SCATTER);
	}
	//刷新图表
	lv_chart_refresh(screen_main_chart_show_tab1);
}

static void updata_chart_data(void)//更新图表数据
{
	

	//刷新图表
	lv_chart_refresh(screen_main_chart_show_tab1);
}

//修改文本内容
static void label_set_internal_ultrasound(void)// 更新内置超声文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1f", lv_ui_data.internal_ultrasound);
	lv_label_set_text(screen_main_label_menu2_2, temp_chars);
}
static void label_set_peak_value(void)// 更新峰值文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "峰值:%.1fdBuv", lv_ui_data.peak_value);
	lv_label_set_text(screen_main_label_menu3_num1, temp_chars);
}
static void label_set_noise(void)// 更新噪声文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "噪声:%.1fdBuv", lv_ui_data.noise);
	lv_label_set_text(screen_main_label_menu3_num2, temp_chars);
}
static void label_set_pulse(void)// 更新脉冲文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "脉冲:%d", lv_ui_data.pulse);
	lv_label_set_text(screen_main_label_menu3_num3, temp_chars);
}

static void label_set_y_axis_range(void)// 更新Y轴量程文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%d%%", lv_ui_data.y_axis_range);
	lv_label_set_text(screen_main_label_show_tab1, temp_chars);
}

static void label_set_rms(void)// 更新RMS文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%d dBuv", lv_ui_data.rms);
	lv_label_set_text(screen_main_label_show_tab2_13, temp_chars);
}
static void label_set_max(void)// 更新最大值文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%d dBuv", lv_ui_data.max);
	lv_label_set_text(screen_main_label_show_tab2_23, temp_chars);
}
static void label_set_data50hz(void)// 更新50Hz文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%d dBuv", lv_ui_data.data50hz);
	lv_label_set_text(screen_main_label_show_tab2_33, temp_chars);
}
static void label_set_data100hz(void)// 更新100Hz文本内容
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%d dBuv", lv_ui_data.data100hz);
	lv_label_set_text(screen_main_label_show_tab2_43, temp_chars);
}

static void label_set_attention_threshold(void)// 更新注意阈值文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "注意阈值:%.1fdBuv", lv_ui_data.attention_threshold);
	lv_label_set_text(screen_main_label_set_01_01, temp_chars);
}
static void label_set_alarm_threshold(void)// 更新告警阈值文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "告警阈值:%.1fdBuv", lv_ui_data.alarm_threshold);
	lv_label_set_text(screen_main_label_set_02_01, temp_chars);
}
static void label_set_count_threshold(void)// 更新计数阈值文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "计数阈值: %d 个", lv_ui_data.count_threshold);
	lv_label_set_text(screen_main_label_set_03_01, temp_chars);
}
static void label_set_phase_offset(void)// 更新相位偏移文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "相位偏移: %d 度", lv_ui_data.phase_offset_angle);
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}

static void label_set_cont_tail_sync_method(void)// 更新同步方法文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "同步方法: %s", lv_ui_data.sync_method ? "内同步" : "外同步");
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}
static void label_set_cont_tail_sync_frequency(void)// 更新同步频率文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "同步频率: %d Hz", lv_ui_data.sync_frequency);
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}
static void label_set_cont_tail_channel_gain(void)// 更新通道增益文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "通道增益: %d dB", lv_ui_data.channel_gain);
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}
static void label_set_cont_tail_channel_threshold(void)// 更新通道阈值文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "通道阈值: %d", lv_ui_data.channel_threshold);
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}
static void label_set_cont_tail_phase_offset(void)// 更新相位偏移文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "相位偏移: %d", lv_ui_data.phase_offset);
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}
static void label_set_cont_tail_filter_enabled(void)// 更新滤波器使能文本内容
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "滤波器使能: %s", lv_ui_data.filter_enabled ? "开启" : "关闭");
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}


//显示隐藏
static void hidden_count_show(void)
{
	// 隐藏
	lv_obj_add_flag(screen_main_cont_main_show, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_tail, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_02, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_03, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_04, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_05, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_tail_06, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_show_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_a1eThAfj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_11, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_12, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_13, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_zqAwibOK, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_21, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_22, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_23, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_sYPD6Gkz, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_31, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_32, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_33, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_Mif8nq4s, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_bar_show_tab2_4, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_41, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_42, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab2_43, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_tab, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_tab4, LV_OBJ_FLAG_HIDDEN);
}

static void show_count_show(void)
{
	lv_obj_clear_flag(screen_main_cont_main_show, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_tail, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_02, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_03, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_04, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_05, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_tail_06, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tail_01, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_show_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_a1eThAfj, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_11, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_12, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_13, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_zqAwibOK, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_21, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_22, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_23, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_sYPD6Gkz, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_31, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_32, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_33, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_Mif8nq4s, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_bar_show_tab2_4, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_41, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_42, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab2_43, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_tab, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_tab4, LV_OBJ_FLAG_HIDDEN);
}

static void hidden_tab1(void)
{
	lv_obj_add_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
}

static void show_tab1(void)
{
	lv_obj_clear_flag(screen_main_label_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_btn_show_tab1_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_chart_show_tab1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(screen_main_cont_show_tab1, LV_OBJ_FLAG_HIDDEN);
}

static void control_cont_tab1(int tab)
{
	switch (tab)
	{
		case 0:
			ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
			ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			show_tab1();
			lv_ui_data.chart_selection=0;
			break;
		case 1:
			ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
			ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			show_tab1();
			lv_ui_data.chart_selection=1;
			break;
		case 2:
			ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
			ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			hidden_tab1();
			lv_ui_data.chart_selection=2;
			break;
		case 3:
			ui_state_modify(screen_main_btn_tab1, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab2, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab3, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
			ui_state_modify(screen_main_btn_tab4, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
			show_tab1();
			lv_ui_data.chart_selection=3;
			break;
		default:
			break;
	}
}

// 按钮事件回调
void screen_main_btn_tail_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tail_01 clicked");
		hidden_count_show();
	}
}

void screen_main_btn_set_09_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_09_01 clicked");
		ui_state_modify(screen_main_btn_set_09_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_09_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		lv_ui_data.channel_selection=0;
	}
}

void screen_main_btn_set_09_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_09_02 clicked");
		ui_state_modify(screen_main_btn_set_09_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_09_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		lv_ui_data.channel_selection=1;
	}
}

void screen_main_btn_set_08_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_01 clicked");
		ui_state_modify(screen_main_btn_set_08_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_08_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.flight_cycle=0;
		g_app_data_result.flight_period=2;
		__enable_irq();
	}
}

void screen_main_btn_set_08_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_02 clicked");
		ui_state_modify(screen_main_btn_set_08_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_08_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.flight_cycle=1;
		g_app_data_result.flight_period=5;
		__enable_irq();
	}
}

void screen_main_btn_set_08_03_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_08_03 clicked");
		ui_state_modify(screen_main_btn_set_08_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_08_03, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.flight_cycle=2;
		g_app_data_result.flight_period=10;
		__enable_irq();
	}
}

void screen_main_btn_set_07_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_07_01 clicked");
		ui_state_modify(screen_main_btn_set_07_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_07_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.unit_selection=0;
		g_app_data_result.unit_select_dBuV=true;
		__enable_irq();
	}
}

void screen_main_btn_set_07_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_07_02 clicked");
		ui_state_modify(screen_main_btn_set_07_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_07_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.unit_selection=1;
		g_app_data_result.unit_select_dBuV=false;
		__enable_irq();
	}
}

void screen_main_btn_set_06_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_01 clicked");
		ui_state_modify(screen_main_btn_set_06_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_06_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.signal_gain=0;
		g_app_data_result.gain=40;
		__enable_irq();
	}
}

void screen_main_btn_set_06_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_02 clicked");
		ui_state_modify(screen_main_btn_set_06_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_06_03, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.signal_gain=1;
		g_app_data_result.gain=60;
		__enable_irq();
	}
}

void screen_main_btn_set_06_03_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_06_03 clicked");
		ui_state_modify(screen_main_btn_set_06_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		ui_state_modify(screen_main_btn_set_06_03, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.signal_gain=2;
		g_app_data_result.gain=80;
		__enable_irq();
	}
}

void screen_main_btn_set_05_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_05_01 clicked");
		ui_state_modify(screen_main_btn_set_05_01, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_05_02, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.gain_type=0;
		g_app_data_result.gain_type_auto=true;
		__enable_irq();
	}
}

void screen_main_btn_set_05_02_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_05_02 clicked");
		ui_state_modify(screen_main_btn_set_05_02, LV_STATE_CHECKED, UI_STATE_ACTION_ADD);
		ui_state_modify(screen_main_btn_set_05_01, LV_STATE_CHECKED, UI_FLAG_ACTION_REMOVE);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.gain_type=1;
		g_app_data_result.gain_type_auto=false;
		__enable_irq();
	}
}

void screen_main_btn_set_tail_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_set_tail_01 clicked");
		show_count_show();
		control_cont_tab1(lv_ui_data.chart_selection);
	}
}

void screen_main_btn_show_tab1_1_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_show_tab1_1 clicked");
		if(lv_ui_data.y_axis_range < 100)
		{
			lv_ui_data.y_axis_range+=5;
        	update_chart_y_axis_and_labels(screen_main_chart_show_tab1, screen_main_chart_scale_y);
			label_set_y_axis_range();
		}
	}
}

void screen_main_btn_show_tab1_2_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_show_tab1_2 clicked");
		if(lv_ui_data.y_axis_range > 5)
		{
			lv_ui_data.y_axis_range-=5;
        	update_chart_y_axis_and_labels(screen_main_chart_show_tab1, screen_main_chart_scale_y);
			label_set_y_axis_range();
		}
	}
}

void screen_main_btn_tab1_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab1 clicked");
		control_cont_tab1(0);
	}
}

void screen_main_btn_tab2_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab2 clicked");
		control_cont_tab1(1);
	}
}

void screen_main_btn_tab3_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab3 clicked");
		control_cont_tab1(2);
	}
}

void screen_main_btn_tab4_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		log_i("screen_main_btn_tab4 clicked");
		control_cont_tab1(3);
	}
}


//滑块事件回调函数
void screen_main_slider_set_01_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_01_01);
		log_i("screen_main_slider_set_01_01 value: %d", value);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.attention_threshold=value*0.1f;
		g_app_data_result.note_thr_mv=value*0.1f;
		__enable_irq();
		label_set_attention_threshold();
	}
}
void screen_main_slider_set_02_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_02_01);
		log_i("screen_main_slider_set_02_01 value: %d", value);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.alarm_threshold=value*0.1f;
		g_app_data_result.alarm_thr_mv=value*0.1f;
		__enable_irq();
		label_set_alarm_threshold();
	}
}
void screen_main_slider_set_03_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_03_01);
		log_i("screen_main_slider_set_03_01 value: %d", value);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.count_threshold=value;
		g_app_data_result.count_thr=value;
		__enable_irq();
		label_set_count_threshold();
	}
}
void screen_main_slider_set_04_01_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t value = lv_slider_get_value(screen_main_slider_set_04_01);
		log_i("screen_main_slider_set_04_01 value: %d", value);
		//关闭开启中断
		__disable_irq();
		lv_ui_data.phase_offset_angle=value;
		g_app_data_result.phase_offset=value;
		__enable_irq();
		label_set_phase_offset();
	}
}


/**
 * @brief 更新图表数据
 * @param data UI 数据结构体指针
 */
void lv_ui_data_update(void)
{

}

/**
 * @brief 初始化图表
 * @param argument 未使用
 */
static void screen_chart_init(void)
{
	//初始化结构体
	// cont menu 界面显示参数
	lv_ui_data.time=0;               /**< 时间 */
	lv_ui_data.battery_level=0;      /**< 电量 */

	lv_ui_data.internal_ultrasound=0.0f; /**< 内置超声 */
	lv_ui_data.peak_value=0.0f;            /**< 峰值 */
	lv_ui_data.noise=0.0f;            /**< 噪声 */
	lv_ui_data.pulse=0;              /**< 脉冲 */

	// cont show 界面显示与控制参数
	lv_ui_data.chart_selection=0;    /**< 图表选择 0脉冲波形 1PRPD图 2四要素图 3飞行图谱 默认0*/
	lv_ui_data.y_axis_range=25;       /**< Y轴量程0-100 默认25 */
	lv_ui_data.adc_wave_ptr=NULL;  /**< ADC 波形数据指针 脉冲波形 */
	lv_ui_data.prpd_matrix_ptr=NULL; /**< PRPD图谱矩阵数据指针 */
	lv_ui_data.tof_matrix_ptr=NULL;  /**< 飞行图谱矩阵数据指针 */
	//四要素图
	lv_ui_data.rms=0;			 /**< RMS 值 */
	lv_ui_data.max=0;			 /**< 最大值 */
	lv_ui_data.data50hz=0;		  /**< 50Hz 值 */
	lv_ui_data.data100hz=0;	   /**< 100Hz 值 */

	// cont tail 界面显示参数
	lv_ui_data.sync_method=0;        /**< 同步方式 0内同步 */
	lv_ui_data.sync_frequency=50;     /**< 同步频率 默认50Hz*/
	lv_ui_data.channel_gain=40;       /**< 通道增益 默认40dB*/
	lv_ui_data.channel_threshold=20;  /**< 通道阈值 默认20*/
	lv_ui_data.phase_offset=0;       /**< 相位偏移 0-360默认0*/
	lv_ui_data.filter_enabled=0;     /**< 滤波是否开启 0关闭 1开启 默认0*/

	// cont set 界面显示与控制参数
	lv_ui_data.attention_threshold=20.0f; /**< 注意阈值 0-70.0 默认20*/
	lv_ui_data.alarm_threshold=20.0f;  /**< 告警阈值 0-70.0 默认20*/
	lv_ui_data.count_threshold=5;    /**< 计数阈值 0-160 默认5 */
	lv_ui_data.phase_offset_angle=0; /**< 相位偏移角度 0-360默认0*/
	lv_ui_data.gain_type=1;          /**< 增益类型 0自动 1手动 默认1*/
	lv_ui_data.signal_gain=0;        /**< 信号增益 0 40db 1 60db 2 80db 默认0 */
	lv_ui_data.unit_selection=0;     /**< 单位选择 0 dbuv 1uv 默认0*/
	lv_ui_data.flight_cycle=0;       /**< 飞行周期 0 2T 1 5T 2 10T 默认0*/	
	lv_ui_data.channel_selection=0;  /**< 通道选择 0内置超声 1外部超声 默认0*/

	lv_ui_data_update();// 初始化图表数据

	//更新文本内容
	label_set_internal_ultrasound();
	label_set_peak_value();
	label_set_noise();
	label_set_pulse();

	label_set_y_axis_range();

	label_set_rms();
	label_set_max();
	label_set_data50hz();
	label_set_data100hz();

	label_set_attention_threshold();
	label_set_alarm_threshold();
	label_set_count_threshold();
	label_set_phase_offset();

	label_set_cont_tail_sync_method();
	label_set_cont_tail_sync_frequency();
	label_set_cont_tail_channel_gain();
	label_set_cont_tail_channel_threshold();
	label_set_cont_tail_phase_offset();
	label_set_cont_tail_filter_enabled();

	//设置滑块值
	lv_slider_set_value(screen_main_slider_set_01_01, lv_ui_data.attention_threshold*10.0f,LV_ANIM_OFF);
	lv_slider_set_value(screen_main_slider_set_02_01, lv_ui_data.alarm_threshold*10.0f,LV_ANIM_OFF);
	lv_slider_set_value(screen_main_slider_set_03_01, lv_ui_data.count_threshold,LV_ANIM_OFF);
	lv_slider_set_value(screen_main_slider_set_04_01, lv_ui_data.phase_offset_angle,LV_ANIM_OFF);

	//图表样式
	chart_style_init(screen_main_chart_show_tab1);
	chart_set_style();
}

extern void setupUi(void);
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
void lv_ui_refresh(void) {}
