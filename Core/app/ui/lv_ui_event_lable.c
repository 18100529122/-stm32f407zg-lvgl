/**
 * @file    lv_ui_event_lable.c
 * @brief   Label 相关事件处理
 */

/*========================= 头文件包含 (Includes) ==========================*/
#include "lv_ui_event.h"

/*========================= 宏定义 (Macros) ================================*/

/*========================= 类型定义 (Typedefs) ============================*/

/*========================= 全局变量 (Global Variables) ====================*/

/*========================= 静态变量 (Static Variables) ====================*/

/*========================= 静态函数声明 (Static Function Declarations) ====*/

/*========================= 函数实现 (Function Definitions) ================*/

/**
 * @brief 更新内置超声文本内容
 *
 * 该函数将 `lv_ui_data.internal_ultrasound` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_menu2_2` 标签的文本内容。
 */
void label_set_internal_ultrasound(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1f", lv_ui_data.internal_ultrasound);
	lv_label_set_text(screen_main_label_menu2_2, temp_chars);
}

/**
 * @brief 更新峰值文本内容
 *
 * 该函数将 `lv_ui_data.peak_value` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_menu3_num1` 标签的文本内容。
 */
void label_set_peak_value(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "峰值:%.1fdBuv", lv_ui_data.peak_value);
	lv_label_set_text(screen_main_label_menu3_num1, temp_chars);
}

/**
 * @brief 更新噪声文本内容
 *
 * 该函数将 `lv_ui_data.noise` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_menu3_num2` 标签的文本内容。
 */
void label_set_noise(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "噪声:%.1fdBuv", lv_ui_data.noise);
	lv_label_set_text(screen_main_label_menu3_num2, temp_chars);
}

/**
 * @brief 更新脉冲文本内容
 *
 * 该函数将 `lv_ui_data.pulse` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_menu3_num3` 标签的文本内容。
 */
void label_set_pulse(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "脉冲:%d", lv_ui_data.pulse);
	lv_label_set_text(screen_main_label_menu3_num3, temp_chars);
}

/**
 * @brief 更新Y轴量程文本内容
 *
 * 该函数将 `lv_ui_data.y_axis_range` 的值格式化为字符串，并添加百分号，
 * 然后将其设置为 `screen_main_label_show_tab1` 标签的文本内容。
 */
void label_set_y_axis_range(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%d%%", lv_ui_data.y_axis_range);
	lv_label_set_text(screen_main_label_show_tab1, temp_chars);
}

/**
 * @brief 更新RMS文本内容
 *
 * 该函数将 `lv_ui_data.common_data.rms` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_show_tab2_13` 标签的文本内容。
 */
void label_set_rms(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1f dBuv", lv_ui_data.common_data.rms);
	lv_label_set_text(screen_main_label_show_tab2_13, temp_chars);
}

/**
 * @brief 更新最大值文本内容
 *
 * 该函数将 `lv_ui_data.common_data.peak` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_show_tab2_23` 标签的文本内容。
 */
void label_set_max(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1f dBuv", lv_ui_data.common_data.peak);
	lv_label_set_text(screen_main_label_show_tab2_23, temp_chars);
}

/**
 * @brief 更新50Hz文本内容
 *
 * 该函数将 `lv_ui_data.common_data.freq_50hz` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_show_tab2_33` 标签的文本内容。
 */
void label_set_data50hz(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1f dBuv", lv_ui_data.common_data.freq_50hz);
	lv_label_set_text(screen_main_label_show_tab2_33, temp_chars);
}

/**
 * @brief 更新100Hz文本内容
 *
 * 该函数将 `lv_ui_data.common_data.freq_100hz` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_show_tab2_43` 标签的文本内容。
 */
void label_set_data100hz(void)
{
	char temp_chars[24];
	snprintf(temp_chars, sizeof(temp_chars), "%.1f dBuv", lv_ui_data.common_data.freq_100hz);
	lv_label_set_text(screen_main_label_show_tab2_43, temp_chars);
}

/**
 * @brief 更新注意阈值文本内容
 *
 * 该函数将 `lv_ui_data.common_data.attention_threshold` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_set_01_01` 标签的文本内容。
 */
void label_set_attention_threshold(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "注意阈值:%.1fdBuv", lv_ui_data.common_data.attention_threshold);
	lv_label_set_text(screen_main_label_set_01_01, temp_chars);
}

/**
 * @brief 更新告警阈值文本内容
 *
 * 该函数将 `lv_ui_data.common_data.alarm_threshold` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_set_02_01` 标签的文本内容。
 */
void label_set_alarm_threshold(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "告警阈值:%.1fdBuv", lv_ui_data.common_data.alarm_threshold);
	lv_label_set_text(screen_main_label_set_02_01, temp_chars);
}

/**
 * @brief 更新计数阈值文本内容
 *
 * 该函数将 `lv_ui_data.common_data.count_threshold` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_set_03_01` 标签的文本内容。
 */
void label_set_count_threshold(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "计数阈值: %d 个", lv_ui_data.common_data.count_threshold);
	lv_label_set_text(screen_main_label_set_03_01, temp_chars);
}

/**
 * @brief 更新相位偏移文本内容
 *
 * 该函数将 `lv_ui_data.common_data.phase_offset` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_set_04_01` 标签的文本内容。
 */
void label_set_phase_offset(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "相位偏移: %d 度", lv_ui_data.common_data.phase_offset);
	lv_label_set_text(screen_main_label_set_04_01, temp_chars);
}

/**
 * @brief 更新连续尾部同步方法文本内容
 *
 * 该函数根据 `lv_ui_data.sync_method` 的值，
 * 将相应的同步方法文本设置为 `screen_main_label_tail_01` 标签的文本内容。
 */
void label_set_cont_tail_sync_method(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "同步方式: %s", lv_ui_data.sync_method ? "内同步" : "外同步");
	lv_label_set_text(screen_main_label_tail_01, temp_chars);
}

/**
 * @brief 更新连续尾部同步频率文本内容
 *
 * 该函数将 `lv_ui_data.sync_frequency` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_tail_02` 标签的文本内容。
 */
void label_set_cont_tail_sync_frequency(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "同步频率: %d Hz", lv_ui_data.sync_frequency);
	lv_label_set_text(screen_main_label_tail_02, temp_chars);
}

/**
 * @brief 更新连续尾部通道增益文本内容
 *
 * 该函数将 `lv_ui_data.channel_gain` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_set_04_03` 标签的文本内容。
 */
void label_set_cont_tail_channel_gain(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "通道增益: %d dB", lv_ui_data.channel_gain);
	lv_label_set_text(screen_main_label_set_04_03, temp_chars);
}

/**
 * @brief 更新连续尾部通道阈值文本内容
 *
 * 该函数将 `lv_ui_data.channel_threshold` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_tail_04` 标签的文本内容。
 */
void label_set_cont_tail_channel_threshold(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "通道阈值: %d", lv_ui_data.channel_threshold);
	lv_label_set_text(screen_main_label_tail_04, temp_chars);
}

/**
 * @brief 更新连续尾部相位偏移文本内容
 *
 * 该函数将 `lv_ui_data.phase_offset_angle` 的值格式化为字符串，
 * 并将其设置为 `screen_main_label_tail_05` 标签的文本内容。
 */
void label_set_cont_tail_phase_offset(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "相位偏移: %d", lv_ui_data.phase_offset);
	lv_label_set_text(screen_main_label_tail_05, temp_chars);
}

/**
 * @brief 更新连续尾部滤波器使能文本内容
 *
 * 该函数根据 `lv_ui_data.filter_enabled` 的值，
 * 将相应的滤波器使能文本设置为 `screen_main_label_tail_06` 标签的文本内容。
 */
void label_set_cont_tail_filter_enabled(void)
{
	char temp_chars[30];
	snprintf(temp_chars, sizeof(temp_chars), "滤波: %s", lv_ui_data.filter_enabled ? "开启" : "关闭");
	lv_label_set_text(screen_main_label_tail_06, temp_chars);
}
