/**
 * @file    lv_ui_event_chart.c
 * @brief   Chart 相关事件处理
 */

/*========================= 头文件包含 (Includes) ==========================*/
#include "lv_ui_event.h"

/*========================= 宏定义 (Macros) ================================*/

/*========================= 类型定义 (Typedefs) ============================*/

/*========================= 全局变量 (Global Variables) ====================*/
lv_obj_t *screen_main_chart_scale_y = NULL;
lv_obj_t *screen_main_chart_scale_x = NULL;

/*========================= 静态变量 (Static Variables) ====================*/

/*========================= 静态函数声明 (Static Function Declarations) ====*/

/*========================= 函数实现 (Function Definitions) ================*/

/**
 * @brief 更新图表的Y轴范围和标签
 *
 * 根据lv_ui_data.y_axis_range的值计算Y轴的最小值和最大值，
 * 并应用全局限制（Y_AXIS_GLOBAL_MIN和Y_AXIS_GLOBAL_MAX）。
 * 然后，设置图表和Y轴刻度对象的范围，并动态生成Y轴标签。
 * 最后，强制重绘Y轴刻度并刷新图表。
 *
 * @param chart_obj 指向LVGL图表对象的指针。
 * @param scale_y_obj 指向LVGL Y轴刻度对象的指针。
 */
void update_chart_y_axis_and_labels(lv_obj_t *chart_obj, lv_obj_t *scale_y_obj)
{
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
	static const char *dynamic_y_labels_str[] = {y_labels_buf[0], y_labels_buf[1], y_labels_buf[2], NULL};
	lv_scale_set_text_src(scale_y_obj, dynamic_y_labels_str);

	lv_obj_invalidate(scale_y_obj);	 // Force redraw of the scale to apply new labels
	lv_chart_refresh(chart_obj);	 // Refresh chart to update data display if needed
}

/**
 * @brief 初始化图表样式
 *
 * 该函数设置图表的各种样式属性，例如更新模式、X轴和Y轴范围、分割线数量。
 * 它还计算并创建Y轴和X轴的刻度，设置它们的尺寸、位置、模式、刻度数量和标签。
 * Y轴标签是动态生成的，X轴标签是静态定义的。
 * 最后，调用 `update_chart_y_axis_and_labels` 来初始化Y轴的范围和标签。
 *
 * @param chart_obj 指向LVGL图表对象的指针。
 */
void chart_style_init(lv_obj_t *chart_obj)
{
	lv_chart_set_update_mode(chart_obj, LV_CHART_UPDATE_MODE_CIRCULAR);													  // 循环更新数据
	lv_chart_set_range(chart_obj, LV_CHART_AXIS_PRIMARY_X, 0, 100);														  // 设置X轴范围
	lv_chart_set_range(chart_obj, LV_CHART_AXIS_PRIMARY_Y, -50 * lv_ui_data.y_axis_range, 50 * lv_ui_data.y_axis_range);  // 设置Y轴范围
	lv_chart_set_div_line_count(chart_obj, 11, 9);																		  // 设置X轴和Y轴的分线数量 (Y轴11条线对应10个间隔，X轴9条线对应8个间隔)

	lv_obj_t *chart_parent = lv_obj_get_parent(chart_obj);

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
	lv_obj_set_size(screen_main_chart_scale_y, 60, chart_content_height);												 // 高度匹配 Chart 内容高度
	lv_obj_align_to(screen_main_chart_scale_y, chart_obj, LV_ALIGN_OUT_LEFT_MID, -5 - pad_left, y_offset_for_align_to);	 // 调整 y 偏移
	lv_scale_set_mode(screen_main_chart_scale_y, LV_SCALE_MODE_VERTICAL_LEFT);
	lv_scale_set_total_tick_count(screen_main_chart_scale_y, 3);  // 3 labels (2 intervals)
	lv_scale_set_major_tick_every(screen_main_chart_scale_y, 1);  // Every tick is a major tick
	lv_scale_set_label_show(screen_main_chart_scale_y, true);
	lv_obj_set_style_text_font(screen_main_chart_scale_y, &lv_font_chinese_14_14, 0);

	// Call after scale_y is created and before chart_refresh to initialize range and labels
	update_chart_y_axis_and_labels(chart_obj, screen_main_chart_scale_y);

	// 计算 X 轴 scale 的水平偏移量，使其中心与 Chart 内容区域的中心对齐
	lv_coord_t x_offset_for_align_to = (pad_left + chart_content_width / 2) - (chart_full_width / 2);

	// 创建 X 轴刻度
	screen_main_chart_scale_x = lv_scale_create(chart_parent);
	lv_obj_set_size(screen_main_chart_scale_x, chart_content_width, 60);													// 宽度匹配 Chart 内容宽度
	lv_obj_align_to(screen_main_chart_scale_x, chart_obj, LV_ALIGN_OUT_BOTTOM_MID, x_offset_for_align_to, 5 + pad_bottom);	// 调整 x 偏移
	lv_scale_set_mode(screen_main_chart_scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
	lv_scale_set_range(screen_main_chart_scale_x, 0, 100);
	lv_scale_set_total_tick_count(screen_main_chart_scale_x, 5);  // 5 labels (4 intervals)
	lv_scale_set_major_tick_every(screen_main_chart_scale_x, 1);  // Every tick is a major tick
	lv_scale_set_label_show(screen_main_chart_scale_x, true);
	static const char *x_labels_str[] = {"0", "25", "50", "75", "100", NULL};
	lv_scale_set_text_src(screen_main_chart_scale_x, x_labels_str);
	lv_obj_set_style_text_font(screen_main_chart_scale_x, &lv_font_chinese_14_14, 0);
}

/**
 * @brief 设置图表类型
 *
 * 根据 `lv_ui_data.chart_selection` 的值设置主图表 `screen_main_chart_show_tab1` 的类型。
 * 支持折线图 (LV_CHART_TYPE_LINE) 和散点图 (LV_CHART_TYPE_SCATTER)。
 * 在设置图表类型后，会刷新图表以应用更改。
 */
void chart_set_style(void)
{
	// 清除图表数据

	// 设置样式
	if (lv_ui_data.chart_selection == 0)  // 脉冲波形	折线图
	{
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_LINE);	 // 折线图
	}
	else if (lv_ui_data.chart_selection == 1)  // PRPD图	散点
	{
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_SCATTER);
	}
	else if (lv_ui_data.chart_selection == 2)  // 四要素 无
	{
	}
	else if (lv_ui_data.chart_selection == 3)  // 飞行图 散点
	{
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_SCATTER);
	}
	// 刷新图表
	lv_chart_refresh(screen_main_chart_show_tab1);
}

/**
 * @brief 更新图表数据
 *
 * 该函数目前仅刷新主图表 `screen_main_chart_show_tab1`。
 * 在实际应用中，此函数会负责从数据源获取最新数据并将其加载到图表中。
 */
void updata_chart_data(void)
{

	// 刷新图表
	lv_chart_refresh(screen_main_chart_show_tab1);
}
