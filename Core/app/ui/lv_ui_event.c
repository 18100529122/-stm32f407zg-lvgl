#include "lv_ui_event.h"

lv_ui_data_t lv_ui_data = {0};

/*
 * @brief 初始化 UI 数据结构体
 */
static void lv_ui_data_init(void)
{
	// 初始化结构体
	//  cont menu 界面显示参数
	lv_ui_data.time = 0;		  /**< 时间 */
	lv_ui_data.battery_level = 0; /**< 电量 */

	lv_ui_data.internal_ultrasound = 0.0f; /**< 内置超声 */
	lv_ui_data.peak_value = 0.0f;		   /**< 峰值 */
	lv_ui_data.noise = 0.0f;			   /**< 噪声 */
	lv_ui_data.pulse = 0;				   /**< 脉冲 */

	// cont show 界面显示与控制参数
	lv_ui_data.chart_selection = 0;	   /**< 图表选择 0脉冲波形 1PRPD图 2四要素图 3飞行图谱 默认0*/
	lv_ui_data.y_axis_range = 50;	   /**< Y轴量程0-100 默认50 */
	lv_ui_data.prpd_matrix_ptr = NULL; /**< PRPD图谱矩阵数据指针 */
	lv_ui_data.tof_matrix_ptr = NULL;  /**< 飞行图谱矩阵数据指针 */
	for (int i = 0; i < 100; i++)
	{
		lv_ui_data.adc_wave_100[i] = 0;
	}
	// 四要素图
	lv_ui_data.rms = 0;		  /**< RMS 值 */
	lv_ui_data.max = 0;		  /**< 最大值 */
	lv_ui_data.data50hz = 0;  /**< 50Hz 值 */
	lv_ui_data.data100hz = 0; /**< 100Hz 值 */

	// cont tail 界面显示参数
	lv_ui_data.sync_method = 0;		   /**< 同步方式 0内同步 */
	lv_ui_data.sync_frequency = 50;	   /**< 同步频率 默认50Hz*/
	lv_ui_data.channel_gain = 40;	   /**< 通道增益 默认40dB*/
	lv_ui_data.channel_threshold = 20; /**< 通道阈值 默认20*/
	lv_ui_data.phase_offset = 0;	   /**< 相位偏移 0-360默认0*/
	lv_ui_data.filter_enabled = 0;	   /**< 滤波是否开启 0关闭 1开启 默认0*/

	// cont set 界面显示与控制参数
	lv_ui_data.attention_threshold = 20.0f; /**< 注意阈值 0-70.0 默认20*/
	lv_ui_data.alarm_threshold = 20.0f;		/**< 告警阈值 0-70.0 默认20*/
	lv_ui_data.count_threshold = 5;			/**< 计数阈值 0-160 默认5 */
	lv_ui_data.phase_offset_angle = 0;		/**< 相位偏移角度 0-360默认0*/
	lv_ui_data.gain_type = 1;				/**< 增益类型 0自动 1手动 默认1*/
	lv_ui_data.signal_gain = 0;				/**< 信号增益 0 40db 1 60db 2 80db 默认0 */
	lv_ui_data.unit_selection = 0;			/**< 单位选择 0 dbuv 1uv 默认0*/
	lv_ui_data.flight_cycle = 0;			/**< 飞行周期 0 2T 1 5T 2 10T 默认0*/
	lv_ui_data.channel_selection = 0;		/**< 通道选择 0内置超声 1外部超声 默认0*/
}

/**
 * @brief 初始化图表
 * @param argument 未使用
 */
static void screen_init(void)
{
	lv_ui_data_init();	// 初始化 UI 数据结构体

	// 更新文本内容
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

	// 设置滑块值
	lv_slider_set_value(screen_main_slider_set_01_01, lv_ui_data.attention_threshold * 10.0f, LV_ANIM_OFF);
	lv_slider_set_value(screen_main_slider_set_02_01, lv_ui_data.alarm_threshold * 10.0f, LV_ANIM_OFF);
	lv_slider_set_value(screen_main_slider_set_03_01, lv_ui_data.count_threshold, LV_ANIM_OFF);
	lv_slider_set_value(screen_main_slider_set_04_01, lv_ui_data.phase_offset_angle, LV_ANIM_OFF);

	// Bar
	bar_set_rms();
	bar_set_max();
	bar_set_data50hz();
	bar_set_data100hz();

	// 图表样式
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
	setupUi();		// 初始化 UI 界面(生成的ui)
	screen_init();	// 初始化 UI 界面数据
	lv_unlock();
}

/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void)
{
	app_data_result_t *r = app_data_process_get_result();
	if (r)
	{
		// 更新数据 PRPD 图谱 飞行图谱 脉冲波形
		lv_ui_data.prpd_matrix_ptr = r->prpd_matrix_ptr;
		lv_ui_data.tof_matrix_ptr = r->tof_matrix_ptr;

		for (uint32_t i = 0; i < 100; i++)
		{
			uint32_t src_i = (i * (ADC_WAVE_SIZE - 1)) / (100 - 1);
			lv_ui_data.adc_wave_100[i] = r->adc_wave[src_i];
		}

		// 更新四要素图数据
		lv_ui_data.rms = r->rms;
		lv_ui_data.max = r->peak;
		lv_ui_data.data50hz = r->freq_50hz;
		lv_ui_data.data100hz = r->freq_100hz;
	}

	updata_chart_data();
}
