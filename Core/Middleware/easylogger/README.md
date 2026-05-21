EasyLogger 移植说明与使用指南

本说明旨在帮助您了解 EasyLogger 在 FreeRTOS 项目中的移植过程和基本使用方法。

---

### **1. 移植说明**

EasyLogger 的移植主要涉及以下文件的修改：

*   **`elog_port.c`**
    *   移除了 `elog_lockHandle`, `elog_asyncHandle`, `elog_dma_lockHandle` 的全局变量定义。
    *   在 `elog_port_init()` 函数中，移除了所有信号量和异步日志任务的创建。
    *   `elog_port_output()` 函数配置为使用 `HAL_UART_Transmit()` (阻塞模式) 进行日志输出。
    *   `elog_port_output_lock()` 和 `elog_port_output_unlock()` 函数中与信号量相关的操作已被注释。
    *   `elog_port_get_time()` 函数使用 `osKernelGetTickCount()` 获取系统 Tick 数。
    *   `elog_port_get_p_info()` 和 `elog_port_get_t_info()` 函数返回空字符串。
*   **`elog_cfg.h` 文件**
    *   注释掉了 `ELOG_ASYNC_OUTPUT_USING_PTHREAD` 宏，以禁用 POSIX 线程实现。
    *   同时，由于 `elog_asyncHandle` 也被禁用，异步输出功能将不会启用。
*   **`middleware.c` 文件**
    *   在文件顶部添加 `elog.h` 头文件引用。
    *   在 `middleware_init()` 函数中添加 `elog_init()` 和 `elog_start()` 的调用，用于初始化和启动 EasyLogger。

### **2. 如何使用**

在完成上述移植后，您可以在您的应用程序代码中使用 EasyLogger 提供的日志宏来输出不同级别的日志信息。

**2.1 初始化**

EasyLogger 的初始化和启动已集成到 `middleware_init()` 函数中，您无需在应用程序中再次手动调用。

**2.2 日志输出示例**

以下是一些常用的日志输出宏：

*   **`ELOG_ASSERT` / `elog_a`**: 断言日志 (等级 0)
*   **`ELOG_ERROR` / `elog_e`**: 错误日志 (等级 1)
*   **`ELOG_WARN` / `elog_w`**: 警告日志 (等级 2)
*   **`ELOG_INFO` / `elog_i`**: 信息日志 (等级 3)
*   **`ELOG_DEBUG` / `elog_d`**: 调试日志 (等级 4)
*   **`ELOG_VERBOSE` / `elog_v`**: 详细日志 (等级 5)

**示例代码:**

```c
#include "elog.h" // 包含 EasyLogger 头文件

void my_application_task(void *argument)
{
    // ... 其他任务代码 ...

    // 输出不同级别的日志
    log_a("这是一个断言日志！");
    log_e("发生了一个错误：%d", -1);
    log_w("这是一个警告信息！");
    log_i("应用程序启动成功！");
    log_d("变量 x 的值为：%d", 123);
    log_v("详细的调试信息，用于跟踪程序流程。");

    // ... 其他任务代码 ...
}
```

**2.3 配置 (`elog_cfg.h`)**

您可以通过修改 `elog_cfg.h` 文件来进一步配置 EasyLogger 的行为，例如：

*   `ELOG_OUTPUT_LVL`: 设置静态输出日志级别。低于此级别的日志将不会被编译。
*   `ELOG_LINE_BUF_SIZE`: 每行日志的缓冲区大小。
*   `ELOG_ASYNC_OUTPUT_BUF_SIZE`: 异步输出模式的缓冲区大小 (虽然当前异步模式禁用，此宏仍可能影响某些内部缓冲)。
*   `ELOG_COLOR_ENABLE`: 启用/禁用日志颜色。

**2.4 编译与运行**

确保您的项目已正确包含 EasyLogger 的源文件 (`elog.c`, `elog_async.c`, `elog_utils.c`, `elog_buf.c` 和 `elog_port.c`) 到编译路径中，并正确链接 FreeRTOS 和 CMSIS-OS V2 库。编译并运行您的项目，即可通过配置的 UART 端口查看日志输出。
