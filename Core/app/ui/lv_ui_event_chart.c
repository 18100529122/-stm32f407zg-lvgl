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
static lv_chart_series_t *s_main_chart_ser0 = NULL;

/*========================= 静态函数声明 (Static Function Declarations) ====*/
static void update_chart_y_axis_and_labels_range(lv_obj_t *chart_obj, lv_obj_t *scale_y_obj, int32_t y_min, int32_t y_max);
static lv_chart_series_t *ensure_main_chart_series(lv_obj_t *chart_obj);
static void clear_main_chart_series(lv_obj_t *chart_obj);
static void fill_scatter_from_matrix_u16(const uint16_t *m, uint32_t amp_bins, uint32_t x_bins, int32_t *x, int32_t *y, uint32_t point_cnt);

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

	update_chart_y_axis_and_labels_range(chart_obj, scale_y_obj, y_min, y_max);
}

static void update_chart_y_axis_and_labels_range(lv_obj_t *chart_obj, lv_obj_t *scale_y_obj, int32_t y_min, int32_t y_max)
{
	lv_chart_set_range(chart_obj, LV_CHART_AXIS_PRIMARY_Y, y_min, y_max);
	lv_scale_set_range(scale_y_obj, y_min, y_max);

	static char y_labels_buf[3][16];
	lv_snprintf(y_labels_buf[0], sizeof(y_labels_buf[0]), "%d", y_min);
	lv_snprintf(y_labels_buf[1], sizeof(y_labels_buf[1]), "%d", (y_min + y_max) / 2);
	lv_snprintf(y_labels_buf[2], sizeof(y_labels_buf[2]), "%d", y_max);
	static const char *dynamic_y_labels_str[] = {y_labels_buf[0], y_labels_buf[1], y_labels_buf[2], NULL};
	lv_scale_set_text_src(scale_y_obj, dynamic_y_labels_str);

	lv_obj_invalidate(scale_y_obj);
}

/**
 * @brief 更新图表的X轴范围和标签
 */
void update_chart_x_axis_and_labels(int data_type)
{
	static char x_labels_buf[5][16];
	if (data_type == 0)
	{
		lv_scale_set_range(screen_main_chart_scale_x, 0, 100);
		lv_snprintf(x_labels_buf[0], sizeof(x_labels_buf[0]), "0");
		lv_snprintf(x_labels_buf[1], sizeof(x_labels_buf[1]), "25");
		lv_snprintf(x_labels_buf[2], sizeof(x_labels_buf[2]), "50");
		lv_snprintf(x_labels_buf[3], sizeof(x_labels_buf[3]), "75");
		lv_snprintf(x_labels_buf[4], sizeof(x_labels_buf[4]), "100");
	}
	else if (data_type == 1)
	{
		lv_scale_set_range(screen_main_chart_scale_x, 0, 360);
		lv_snprintf(x_labels_buf[0], sizeof(x_labels_buf[0]), "0");
		lv_snprintf(x_labels_buf[1], sizeof(x_labels_buf[1]), "90");
		lv_snprintf(x_labels_buf[2], sizeof(x_labels_buf[2]), "180");
		lv_snprintf(x_labels_buf[3], sizeof(x_labels_buf[3]), "240");
		lv_snprintf(x_labels_buf[4], sizeof(x_labels_buf[4]), "360");
	}
	else if (data_type == 3)
	{
		if (lv_ui_data.flight_cycle == 0)
		{
			lv_scale_set_range(screen_main_chart_scale_x, 0, 2);
			lv_snprintf(x_labels_buf[0], sizeof(x_labels_buf[0]), "0");
			lv_snprintf(x_labels_buf[1], sizeof(x_labels_buf[1]), "0.5");
			lv_snprintf(x_labels_buf[2], sizeof(x_labels_buf[2]), "1");
			lv_snprintf(x_labels_buf[3], sizeof(x_labels_buf[3]), "1.5");
			lv_snprintf(x_labels_buf[4], sizeof(x_labels_buf[4]), "2");
		}
		else if (lv_ui_data.flight_cycle == 1)
		{
			lv_scale_set_range(screen_main_chart_scale_x, 0, 5);
			lv_snprintf(x_labels_buf[0], sizeof(x_labels_buf[0]), "0");
			lv_snprintf(x_labels_buf[1], sizeof(x_labels_buf[1]), "1.25");
			lv_snprintf(x_labels_buf[2], sizeof(x_labels_buf[2]), "2.5");
			lv_snprintf(x_labels_buf[3], sizeof(x_labels_buf[3]), "3.75");
			lv_snprintf(x_labels_buf[4], sizeof(x_labels_buf[4]), "5");
		}
		else if (lv_ui_data.flight_cycle == 2)
		{
			lv_scale_set_range(screen_main_chart_scale_x, 0, 10);
			lv_snprintf(x_labels_buf[0], sizeof(x_labels_buf[0]), "0");
			lv_snprintf(x_labels_buf[1], sizeof(x_labels_buf[1]), "2.5");
			lv_snprintf(x_labels_buf[2], sizeof(x_labels_buf[2]), "5");
			lv_snprintf(x_labels_buf[3], sizeof(x_labels_buf[3]), "7.5");
			lv_snprintf(x_labels_buf[4], sizeof(x_labels_buf[4]), "10");
		}
	}

	static const char *dynamic_x_labels_str[] = {x_labels_buf[0], x_labels_buf[1], x_labels_buf[2], x_labels_buf[3], x_labels_buf[4], NULL};
	lv_scale_set_text_src(screen_main_chart_scale_x, dynamic_x_labels_str);

	lv_obj_invalidate(screen_main_chart_scale_x);  // Force redraw of the scale to apply new labels
}

static lv_chart_series_t *ensure_main_chart_series(lv_obj_t *chart_obj)
{
	lv_chart_series_t *ser = lv_chart_get_series_next(chart_obj, NULL);
	if (ser == NULL)
	{
		ser = lv_chart_add_series(chart_obj, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
	}
	s_main_chart_ser0 = ser;
	return ser;
}

static void clear_main_chart_series(lv_obj_t *chart_obj)
{
	uint32_t point_cnt = lv_chart_get_point_count(chart_obj);
	lv_chart_series_t *ser = lv_chart_get_series_next(chart_obj, NULL);
	while (ser != NULL)
	{
		int32_t *y = lv_chart_get_y_array(chart_obj, ser);
		for (uint32_t i = 0; i < point_cnt; i++)
		{
			y[i] = LV_CHART_POINT_NONE;
		}
		int32_t *x = lv_chart_get_x_array(chart_obj, ser);
		if (x)
		{
			for (uint32_t i = 0; i < point_cnt; i++)
			{
				x[i] = 0;
			}
		}
		ser = lv_chart_get_series_next(chart_obj, ser);
	}
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
	lv_obj_set_style_text_font(screen_main_chart_scale_x, &lv_font_chinese_14_14, 0);

	// Call after scale_x is created and before chart_refresh to initialize range and labels
	update_chart_x_axis_and_labels(lv_ui_data.chart_selection);

	ensure_main_chart_series(chart_obj);
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
	ensure_main_chart_series(screen_main_chart_show_tab1);
	clear_main_chart_series(screen_main_chart_show_tab1);

	// 设置样式
	if (lv_ui_data.chart_selection == 0)  // 脉冲波形	折线图
	{
		lv_chart_set_point_count(screen_main_chart_show_tab1, 100);
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_LINE);
		lv_obj_set_style_line_opa(screen_main_chart_show_tab1, LV_OPA_COVER, LV_PART_ITEMS);
		if (screen_main_chart_scale_y) update_chart_y_axis_and_labels(screen_main_chart_show_tab1, screen_main_chart_scale_y);
		if (screen_main_chart_scale_x) update_chart_x_axis_and_labels(lv_ui_data.chart_selection);
	}
	else if (lv_ui_data.chart_selection == 1)  // PRPD图	散点
	{
		lv_chart_set_point_count(screen_main_chart_show_tab1, 300);
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_SCATTER);
		lv_obj_set_style_line_opa(screen_main_chart_show_tab1, LV_OPA_TRANSP, LV_PART_ITEMS);
		if (screen_main_chart_scale_y) update_chart_y_axis_and_labels_range(screen_main_chart_show_tab1, screen_main_chart_scale_y, 0, 40);
		if (screen_main_chart_scale_x) update_chart_x_axis_and_labels(lv_ui_data.chart_selection);
	}
	else if (lv_ui_data.chart_selection == 2)  // 四要素 无
	{
	}
	else if (lv_ui_data.chart_selection == 3)  // 飞行图 散点
	{
		lv_chart_set_point_count(screen_main_chart_show_tab1, 300);
		lv_chart_set_type(screen_main_chart_show_tab1, LV_CHART_TYPE_SCATTER);
		lv_obj_set_style_line_opa(screen_main_chart_show_tab1, LV_OPA_TRANSP, LV_PART_ITEMS);
		if (screen_main_chart_scale_y) update_chart_y_axis_and_labels_range(screen_main_chart_show_tab1, screen_main_chart_scale_y, 0, 40);
		if (screen_main_chart_scale_x) update_chart_x_axis_and_labels(lv_ui_data.chart_selection);
	}

	lv_chart_refresh(screen_main_chart_show_tab1);
}

/*
 * @brief 从16位矩阵填充散点图数据
 *
 * 该函数将16位矩阵中的非零元素转换为散点图数据，
 * 并将结果填充到指定的数组中。
 * 它还处理了矩阵的边界情况，确保数据在图表范围内显示。
 *
 * @param m 指向16位矩阵的指针。
 * @param amp_bins 矩阵的行数（Y轴）。
 * @param x_bins 矩阵的列数（X轴）。
 * @param x 指向X轴数据数组的指针。
 * @param y 指向Y轴数据数组的指针。
 * @param point_cnt 散点图数据点的数量。
 */
static void fill_scatter_from_matrix_u16(const uint16_t *m, uint32_t amp_bins, uint32_t x_bins, int32_t *x, int32_t *y, uint32_t point_cnt)
{
	if (m == NULL || x == NULL || y == NULL || amp_bins == 0 || x_bins == 0 || point_cnt == 0) return;

	uint32_t out_i = 0;
	for (uint32_t amp = 0; amp < amp_bins; amp++)
	{
		const uint32_t row_ofs = amp * x_bins;
		for (uint32_t xi = 0; xi < x_bins; xi++)
		{
			uint16_t c = m[row_ofs + xi];
			if (c == 0) continue;
			if (out_i >= point_cnt) break;
			x[out_i] = (int32_t)xi;
			y[out_i] = (int32_t)amp;
			out_i++;
		}
		if (out_i >= point_cnt) break;
	}

	for (uint32_t i = out_i; i < point_cnt; i++)
	{
		y[i] = LV_CHART_POINT_NONE;
	}
}

/**
 * @brief 更新图表数据
 *
 * 该函数目前仅刷新主图表 `screen_main_chart_show_tab1`。
 * 在实际应用中，此函数会负责从数据源获取最新数据并将其加载到图表中。
 */
void updata_chart_data(void)
{
	lv_obj_t *chart = screen_main_chart_show_tab1;
	lv_chart_series_t *ser = ensure_main_chart_series(chart);
	if (ser == NULL) return;

	uint32_t point_cnt = lv_chart_get_point_count(chart);
	if (point_cnt == 0) return;

	if (lv_ui_data.chart_selection == 0)
	{
		int32_t *y = lv_chart_get_y_array(chart, ser);
		uint32_t cnt = point_cnt;
		if (cnt > 100) cnt = 100;
		for (uint32_t i = 0; i < cnt; i++)
		{
			y[i] = (int32_t)lv_ui_data.adc_wave_100[i];
		}
		for (uint32_t i = cnt; i < point_cnt; i++)
		{
			y[i] = LV_CHART_POINT_NONE;
		}
		lv_chart_refresh(chart);
		return;
	}

	if (lv_ui_data.chart_selection == 1 || lv_ui_data.chart_selection == 3)
	{
		int32_t *x = lv_chart_get_x_array(chart, ser);
		int32_t *y = lv_chart_get_y_array(chart, ser);
		if (x == NULL || y == NULL) return;

		if (lv_ui_data.chart_selection == 1)
		{
			uint16_t (*m)[PRPD_PHASE_BINS] = lv_ui_data.prpd_matrix_ptr;
			if (m == NULL)
			{
				lv_chart_refresh(chart);
				return;
			}
			fill_scatter_from_matrix_u16((const uint16_t *)m, PRPD_AMP_BINS, PRPD_PHASE_BINS, x, y, point_cnt);
		}
		else
		{
			uint16_t (*m)[TOF_TIME_BINS] = lv_ui_data.tof_matrix_ptr;
			if (m == NULL)
			{
				lv_chart_refresh(chart);
				return;
			}
			fill_scatter_from_matrix_u16((const uint16_t *)m, TOF_AMP_BINS, TOF_TIME_BINS, x, y, point_cnt);
		}

		lv_chart_refresh(chart);
		return;
	}

	lv_chart_refresh(chart);
}
