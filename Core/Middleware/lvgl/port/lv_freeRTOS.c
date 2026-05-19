#include "lv_freeRTOS.h"
#include "lvgl.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "lv_ui_event.h"
#include "app_data_fft.h"
#include "app_data_process.h"

/* LVGL 刷新任务句柄 */
osThreadId_t lvglTaskHandle;


/* LVGL 刷新任务属性 */
const osThreadAttr_t lvglTask_attributes = {
  .name = "lvglTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/**
 * @brief LVGL 数据更新定时器回调
 * @param timer 定时器对象
 */
static void lvgl_data_update_timer_cb(lv_timer_t * timer)
{
    (void)timer;
    
    // 获取数据
    uint8_t rms = app_data_process_get_rms_uint8();
    uint8_t max = app_data_process_get_peak_uint8();
    uint8_t data50hz = app_data_process_get_freq_50hz_uint8();
    uint8_t data100hz = app_data_process_get_freq_100hz_uint8();
    
    char * rms_data = app_data_process_get_rms_str();
    char * max_data = app_data_process_get_peak_str();
    char * data50hz_data = app_data_process_get_freq_50hz_str();
    char * data100hz_data = app_data_process_get_freq_100hz_str();
    
    printf("rms: %d-%s, max: %d-%s, 50Hz: %d-%s, 100Hz: %d-%s\r\n",
        rms, rms_data, max, max_data, data50hz, data50hz_data, data100hz, data100hz_data); 
    
    // 更新图表和标签数据
    lv_ui_data_update(rms, max, data50hz, data100hz, rms_data, max_data, data50hz_data, data100hz_data);
    
    /* 刷新 UI (如果需要) */
    lv_ui_refresh();
}

/**
 * @brief LVGL 刷新任务函数
 * @param argument 未使用
 */
static void lvgl_thread(void *argument)
{
    (void)argument;
    /* 等待 middleware_init 在 StartDefaultTask 中完成 (lv_init 和 lv_port_disp_init) */
    osDelay(2000);
    printf("LVGL Thread: Initializing Widgets...\r\n");
    
    /* 创建数据更新定时器 (1秒一次) */
    lv_timer_create(lvgl_data_update_timer_cb, 1000, NULL);
    
    while(1) {

        lv_timer_handler();
        
        /* 延时 15ms，降低对 SRAM 总线的占用，给 ADC DMA 留出带宽 */
        osDelay(15);
    }
}

/**
 * @brief 初始化 LVGL FreeRTOS 刷新线程
 */
void lv_freertos_init(void)
{
    /* 初始化控件和 UI */
    lv_widgets_init();
    printf("LVGL Thread: Widgets Init Done\r\n");

    /* 创建 LVGL 刷新线程 */
    lvglTaskHandle = osThreadNew(lvgl_thread, NULL, &lvglTask_attributes);
}

/**
 * @brief 初始化 LVGL 控件和 UI
 */
void lv_widgets_init(void)
{
    lv_ui_init();
}
