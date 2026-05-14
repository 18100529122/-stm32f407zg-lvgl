#include "lv_freeRTOS.h"
#include "lvgl.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "setup_ui.h"

/* LVGL 刷新任务句柄 */
osThreadId_t lvglTaskHandle;

/* LVGL 刷新任务属性 */
const osThreadAttr_t lvglTask_attributes = {
  .name = "lvglTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/**
 * @brief LVGL 刷新任务函数
 * @param argument 未使用
 */
static void lvgl_thread(void *argument)
{
    (void)argument;
    HAL_Delay(2000);
    lv_lock();
    setupUi();
    lv_unlock();

    while(1) {
        /* 调用 LVGL 计时器处理器 */
        lv_timer_handler();
        
        /* 延时 5ms，保证界面流畅度 */
        osDelay(5);
    }
}

/**
 * @brief 初始化 LVGL FreeRTOS 刷新线程
 */
void lv_freertos_init(void)
{
    lvglTaskHandle = osThreadNew(lvgl_thread, NULL, &lvglTask_attributes);
}
