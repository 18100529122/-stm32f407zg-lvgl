#include "lv_freeRTOS.h"
#include "lvgl.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "lv_ui_event.h"
#include "app_data_fft.h"

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
        osDelay(500);
        
        
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
