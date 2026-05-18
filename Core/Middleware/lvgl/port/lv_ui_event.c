#include "lv_ui_event.h"
#include "setup_ui.h"
#include "app_data_fft.h"

extern lv_obj_t * screen_chart_chart_line;
extern lv_obj_t * screen_chart_chart_bar;

/* 存储 10 个数据源 */
static lv_chart_series_t * chart_line_series[10] = {NULL};
static lv_chart_series_t * chart_bar_series = NULL;

static int32_t * chart_line_data[10] = {NULL};
static uint8_t chart_line_data_index = 0;
static int32_t * chart_bar_data = NULL;

/**
 * @brief 切换为柱状图事件回调
 * @param e 事件对象
 */
void screen_chart_btn_bar_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        // 柱状图可见, 折线图不可见
        ui_flag_modify(screen_chart_chart_line, LV_OBJ_FLAG_HIDDEN, UI_FLAG_ACTION_ADD);
        ui_flag_modify(screen_chart_chart_bar, LV_OBJ_FLAG_HIDDEN, UI_FLAG_ACTION_REMOVE);
        printf("screen_chart_btn_bar_event_cb\r\n");
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
        // 折线图可见, 柱状图不可见
        ui_flag_modify(screen_chart_chart_line, LV_OBJ_FLAG_HIDDEN, UI_FLAG_ACTION_REMOVE);
        ui_flag_modify(screen_chart_chart_bar, LV_OBJ_FLAG_HIDDEN, UI_FLAG_ACTION_ADD);
        printf("screen_chart_btn_line_event_cb\r\n");
    }
}

static void ui_chart_init(void)
{
    // 设置图表样式
    lv_chart_set_update_mode(screen_chart_chart_line, LV_CHART_UPDATE_MODE_CIRCULAR);// 循环更新模式
    lv_chart_set_update_mode(screen_chart_chart_bar, LV_CHART_UPDATE_MODE_CIRCULAR);// 循环更新模式

    
    lv_obj_set_style_line_width(screen_chart_chart_line, 0, LV_PART_ITEMS);// 隐藏折线图的连线，只保留散点 (打点)
    lv_obj_set_style_size(screen_chart_chart_line, 3, 3, LV_PART_INDICATOR); // 缩小点到 3x3
    lv_obj_set_style_radius(screen_chart_chart_line, 0, LV_PART_INDICATOR); // 禁用圆角，大幅提升绘制速度

    //数据颜色
    lv_color_t colors[10] = {
        lv_palette_main(LV_PALETTE_RED),
        lv_palette_main(LV_PALETTE_BLUE),
        lv_palette_main(LV_PALETTE_GREEN),
        lv_palette_main(LV_PALETTE_ORANGE),
        lv_palette_main(LV_PALETTE_PURPLE),
        lv_palette_main(LV_PALETTE_CYAN),
        lv_palette_main(LV_PALETTE_AMBER),
        lv_palette_main(LV_PALETTE_TEAL),
        lv_palette_main(LV_PALETTE_PINK),
        lv_palette_main(LV_PALETTE_INDIGO)
    };

    // 创建折线图数据源
    for(int i=0;i<10;i++)
    {
        chart_line_series[i] = lv_chart_add_series(screen_chart_chart_line, colors[i],LV_CHART_AXIS_PRIMARY_Y);
        chart_line_data[i]=lv_chart_get_y_array(screen_chart_chart_line,chart_line_series[i]);
    }
    // 创建柱状图数据源
    chart_bar_series = lv_chart_add_series(screen_chart_chart_bar, colors[0],LV_CHART_AXIS_PRIMARY_Y);
    chart_bar_data=lv_chart_get_y_array(screen_chart_chart_bar,chart_bar_series);
}

/**
 * @brief UI 初始化包装函数
 */
void lv_ui_init(void)
{
    lv_lock();
    setupUi();// 初始化 UI 界面
    ui_chart_init();// 初始化图表
    lv_unlock();
}

/**
 * @brief 更新柱状图数据
 */
void lv_ui_update_bar_chart_data(float * data, int len)
{
    if(chart_bar_series != NULL && screen_chart_chart_bar!=NULL)
    {
        int count = (len > 10) ? 10 : len; // 限制为柱状图定义的 10 个点
        for(int i = 0; i < count; i++)
        {
            // 使用 ID 直接设置 Y 值，对应 FFT 结果
            chart_bar_data[i]=data[i];
        }
    }
}

/**
 * @brief 更新折线图数据
 */
void lv_ui_update_line_chart_data(float * data)
{
    if(screen_chart_chart_line!=NULL)
    {
        chart_line_data[0][chart_line_data_index]=data[0];
        chart_line_data[1][chart_line_data_index]=data[1];
        chart_line_data[2][chart_line_data_index]=data[2];
        // chart_line_data[3][chart_line_data_index]=data[3];
        // chart_line_data[4][chart_line_data_index]=data[4];
        // chart_line_data[5][chart_line_data_index]=data[5];
        // chart_line_data[6][chart_line_data_index]=data[6];
        // chart_line_data[7][chart_line_data_index]=data[7];
        // chart_line_data[8][chart_line_data_index]=data[8];
        // chart_line_data[9][chart_line_data_index]=data[9];

        // 告诉图表循环起始点的位置，这能帮助 LVGL 更高效地管理内部刷新
        for(int i = 0; i < 10; i++) {
            lv_chart_set_x_start_point(screen_chart_chart_line, chart_line_series[i], chart_line_data_index);
        }

        chart_line_data_index = (chart_line_data_index + 1) % 50;
    }
}

/**
 * @brief 刷新 UI 界面显示 (总刷新入口)
 */
void lv_ui_refresh(void)
{
    if(screen_chart_chart_line!=NULL )
    {
        lv_chart_refresh(screen_chart_chart_line);
    }
    if(screen_chart_chart_bar!=NULL )
    {
        lv_chart_refresh(screen_chart_chart_bar);
    }

}
