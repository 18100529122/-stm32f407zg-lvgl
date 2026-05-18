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
osThreadId_t lvglDataTaskHandle;


/* LVGL 刷新任务属性 */
const osThreadAttr_t lvglTask_attributes = {
  .name = "lvglTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* LVGL 数据更新任务属性 */
const osThreadAttr_t lvglDataTask_attributes = {
  .name = "lvglDataTask",
  .stack_size = 1024 * 2,
  .priority = (osPriority_t) osPriorityLow, // 降低优先级，确保不干扰 ADC 处理
};

/**
 * @brief LVGL 数据更新任务函数
 * @param argument 未使用
 */
static void lvgl_data_thread(void *argument)
{
    (void)argument;
    /* 延长等待时间，确保 UI 彻底初始化完成 */
    osDelay(3000);
    printf("LVGL Data Thread Started (Polling Mode 500ms)\r\n");
    
    while(1) {
        // 每隔 500ms 获取一次数据并更新 UI
        osDelay(1000);
        // 获取数据
        uint8_t rms =0;
        uint8_t max =0;
        uint8_t data50hz =0;
        uint8_t data100hz =0;
        char rms_data[10];
        char max_data[10];
        char data50hz_data[10];
        char data100hz_data[10];
        // 计算数据
        app_data_result_t *result = app_data_process_get_result();
        rms = (uint8_t)(result->rms*0.01f);
        max = (uint8_t)(result->peak*0.01f);
        data50hz = (uint8_t)(result->freq_50hz*0.01f);
        data100hz = (uint8_t)(result->freq_100hz*0.01f);

        snprintf(rms_data, sizeof(rms_data), "%.2f", result->rms);
        snprintf(max_data, sizeof(max_data), "%.2f", result->peak);
        snprintf(data50hz_data, sizeof(data50hz_data), "%.2f", result->freq_50hz);
        snprintf(data100hz_data, sizeof(data100hz_data), "%.2f", result->freq_100hz);
        printf("rms: %d-%s, max: %d-%s, 50Hz: %d-%s, 100Hz: %d-%s\r\n",
            rms, rms_data, max, max_data, data50hz, data50hz_data,data100hz, data100hz_data); 
        // 更新图表数据
        lv_ui_data_update(rms,max,data50hz,data100hz,rms_data,max_data,data50hz_data,data100hz_data);
        
        /* 刷新图表 */
        lv_ui_refresh();
    }
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
    
    while(1) {

        lv_timer_handler();
        
        /* 延时 15ms，降低对 SRAM 总线的占用，给 ADC DMA 留出带宽 */
        osDelay(30);
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
    
    /* 创建 LVGL 数据更新线程 */
    lvglDataTaskHandle = osThreadNew(lvgl_data_thread, NULL, &lvglDataTask_attributes);
}

/**
 * @brief 初始化 LVGL 控件和 UI
 */
void lv_widgets_init(void)
{
    lv_ui_init();
}
