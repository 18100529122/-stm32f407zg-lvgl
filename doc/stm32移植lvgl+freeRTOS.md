# STM32F407ZG 移植 LVGL + FreeRTOS 指南

本文档详细记录了在 STM32F407ZG (正点原子探索者开发板) 上移植 LVGL v9.2.2 并集成 FreeRTOS (CMSIS-RTOS2) 的过程和关键配置。

## 1. 软件环境
- **RTOS**: FreeRTOS (CMSIS-V2 接口)
- **GUI 库**: LVGL v9.2.2
- **IDE**: STM32CubeIDE / Keil MDK
- **硬件驱动**: HAL 库 + FSMC (LCD 驱动)

---

## 2. 内存布局与分配 (关键)
由于 LVGL 占用 RAM 较大，本项目充分利用了 STM32F407ZG 挂载的 **1MB 外部 SRAM** (起始地址 `0x68000000`)。

### 2.1 内存池配置 (`lv_conf.h`)
LVGL 的动态内存分配池被放置在外部 SRAM 的起始位置：
```c
#define LV_USE_STDLIB_MALLOC    LV_STDLIB_BUILTIN
#define LV_MEM_SIZE            (64 * 1024U)   /* 64KB 内存池 */
#define LV_MEM_ADR             0x68000000     /* 外部 SRAM 起始地址 */
```

### 2.2 显存缓冲区配置 (`lv_port_disp.c`)
为了实现流畅的动画和界面切换，使用了**双缓冲区**机制，并将其放置在外部 SRAM 中内存池之后的空间：
- **缓冲区大小**: 800 * 120 (1/4 屏幕)
- **Buffer 1 地址**: `0x68010000` (64KB 内存池之后)
- **Buffer 2 地址**: `0x6803EE00`

---

## 3. LVGL 核心配置 (`lv_conf.h`)
- **颜色深度**: `16` (RGB565)
- **刷新周期**: `33ms` (约 30 FPS)
- **OS 集成**: `LV_USE_OS LV_OS_NONE` (采用手动创建 FreeRTOS 任务并调用 handler 的方式)
- **渲染器**: 启用软件渲染 `LV_USE_DRAW_SW 1`

---

## 4. 接口移植 (Porting)

### 4.1 显示接口 (`lv_port_disp.c`)
- **初始化**: 调用 `lcd_display_dir(1)` 设置横屏。
- **打点/刷新**: `disp_flush` 回调函数通过 CPU 拷贝像素数据到 `LCD->LCD_RAM` (FSMC 寻址)。
- **双缓冲注册**:
  ```c
  lv_display_set_buffers(disp, buf_1, buf_2, DISP_BUF_SIZE * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
  ```

### 4.2 输入接口 (`lv_port_indev.c`)
- **驱动集成**: 封装了正点原子的 `tp_dev.scan(0)` 触摸扫描函数。
- **数据读取**: 在 `touchpad_read` 中将坐标及状态 (`PRESSED`/`RELEASED`) 传递给 LVGL。

### 4.3 心跳维持 (`stm32f4xx_it.c`)
使用 `TIM14` 提供 1ms 的系统心跳，在中断回调中调用：
```c
void TIM8_TRG_COM_TIM14_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim14);
    lv_tick_inc(1); // 为 LVGL 提供 1ms 时标
}
```

---

## 5. FreeRTOS 任务集成

### 5.1 任务创建 (`lv_freeRTOS.c`)
创建一个独立的 LVGL 刷新线程 `lvglTask`：
- **堆栈大小**: `8KB` (由于 UI 逻辑可能较复杂，建议不低于 4KB)
- **优先级**: `osPriorityNormal`

### 5.2 任务逻辑
```c
static void lvgl_thread(void *argument) {
    /* 等待硬件初始化完成 */
    osDelay(2000);
    
    /* 创建 UI 逻辑中的定时器 */
    lv_timer_create(lvgl_data_update_timer_cb, 1000, NULL);
    
    while(1) {
        lv_timer_handler(); // 处理 LVGL 定时器、动画和渲染
        osDelay(15);        // 延时 15ms，出让 CPU 资源给其他任务 (如 ADC 采样)
    }
}
```

---

## 6. 注意事项
1. **线程安全**: 当前实现中，所有 LVGL API 调用均在 `lvglTask` 中进行。若需在其他任务中操作 UI，请务必添加互斥锁。
2. **FSMC 带宽**: 显存缓冲区位于外部 SRAM，刷新 UI 时会占用 FSMC 总线。若同时有其他高速外设使用 FSMC，需注意竞争。
3. **堆栈监控**: 开启 FreeRTOS 的 `vApplicationStackOverflowHook` 以监控任务堆栈，防止因 UI 嵌套过深导致溢出。
