# STM32F407 LVGL 测试项目

本项目是基于 **正点原子探索者 (Alientek Explorer) STM32F407 开发板** 开发的，主要用于 **LVGL (Light and Versatile Graphics Library)** 的功能测试与性能评估。

## 硬件配置

- **主控芯片**: STM32F407ZGT6
  - 内核: ARM Cortex-M4
  - 主频: 168MHz
  - 存储: 1MB Flash, 192KB SRAM
- **开发板**: 正点原子探索者 (Alientek Explorer)
- **关键芯片列表**:
  - **SRAM**: XM8A51216V33A (1MB)
  - **SPI Flash**: W25Q128 (16MB)
  - **EEPROM**: 24C02 (256B)
  - **以太网 PHY**: YT8512C (10/100M)
  - **音频 Codec**: ES8388
  - **音频放大器**: MD8002A
  - **背光驱动**: MP3302DJ (DC-DC 升压)
  - **触摸芯片**: GT9147  (电容式接口)
  - **磁力计**: QMA6100P
  - **USB 转串口**: CH340C
  - **RS232 收发器**: TPT3232
  - **RS485 收发器**: TPT8485
  - **CAN 收发器**: SIT1050T
  - **电源管理**: RY9125 (DC-DC), AMS1117-3.3 (LDO)

## 引脚接线说明

详细的硬件引脚配置请参考 [引脚配置说明](file:///c:/work/github/-stm32f407zg-lvgl/doc/%E5%BC%95%E8%84%9A.md)。

## 内存布局与 SRAM 使用情况

本项目充分利用了 STM32F407 的片内 SRAM 和 1MB 外部 SRAM，以平衡高性能计算与大容量显示缓存的需求。

### 1. 片内 SRAM (Total: ~135.2 KB)
片内 SRAM 主要用于 FreeRTOS 堆栈、高速信号处理缓冲区及 LVGL 绘制中间层。

| 模块 | 用途 | 大小 | 存储位置 |
| :--- | :--- | :--- | :--- |
| **FreeRTOS** | 系统堆内存 (Task 栈、信号量等) | 32 KB | SRAM1 |
| **LVGL Draw** | 绘制线程栈 (Draw Thread Stack) | 8 KB | SRAM1 |
| **LVGL Layer** | 简单图层中间缓存 (Simple Layer Buf) | 24 KB | SRAM1 |
| **ADC 采样** | 原始数据缓冲区 (8192 uint16) | 16 KB | SRAM1 |
| **ADC FIFO** | 处理后的 FIFO 数据块 (4 * 2048 uint16) | 16.4 KB | SRAM1 |
| **FFT 运算** | FFT 输入/输出缓存 (2048 float32 * 2) | 16 KB | SRAM1 |
| **信号处理** | 任务局部静态变量 (2048 float32) | 8 KB | SRAM1 |
| **信号结果** | FFT 结果与应用层数据结果 | 9.3 KB | SRAM1 |
| **EasyFlash** | 运行时数据与缓存 | 1 KB | SRAM1 |
| **EasyLogger** | 内部配置与缓冲 | 0.5 KB | SRAM1 |
| **其他** | HAL 驱动、串口缓存及系统全局变量 | ~4 KB | SRAM1 |

### 2. 外部 SRAM (Total: ~439 KB)
通过 FSMC 接口访问 1MB 外部 SRAM，主要用于大规模显示缓冲区和动态内存池。

| 模块 | 起始地址 | 长度 | 用途 |
| :--- | :--- | :--- | :--- |
| **LVGL Heap** | `0x68000000` | 64 KB | LVGL 动态内存池 (`lv_malloc`) |
| **LVGL Disp** | `0x68010000` | 375 KB | 800*120*2 双缓冲区 (Partial Render) |
| **EXT SRAM** | `0x68070000` | 576 KB | 编译器管理区域 (`.ext_sram`) |

## 代码文件结构

```text
Core/
├── app/                # 应用逻辑层
│   ├── data_process/   # 数据处理、FFT 计算、PRPD 算法
│   └── ui/             # LVGL UI 界面设计与事件处理
├── BSP/                # 板级支持包 (底层驱动)
│   ├── adc/            # 高速 ADC 采样驱动 (1Msps)
│   ├── dac/            # DAC 波形输出驱动
│   ├── flash/          # W25Q128 SPI Flash 驱动 (LibDriver)
│   ├── lcd/            # ILI9806 LCD 驱动 (FSMC)
│   ├── lcd_touch/      # GT9xxx 触摸驱动 (软件 I2C)
│   └── time/           # 高精度延时与时间戳工具
├── Middleware/         # 中间件层
│   ├── easyflash/      # 轻量级 Flash 存储库 (用于环境变量、数据存储)
│   ├── easylogger/     # 嵌入式系统日志库 (用于系统调试和信息输出)
│   └── lvgl/           # LVGL 图形库核心及适配层 (porting)
├── Inc/                # 系统核心头文件
└── Src/                # 系统核心实现 (main, freertos 等)
```

## 软件架构与特性

- **操作系统**: FreeRTOS
  - 采用专用的 LVGL 刷新线程 (`lvglTask`)，刷新周期 15ms。
  - **异步数据更新**: UI 数据更新任务 (`lvglDataTask`) 采用 **500ms 定时轮询** 模式，解耦了后台计算与前端显示。
  - 使用 `lv_lock/unlock` 互斥量确保多线程环境下的 UI 操作安全。
- **图形库**: LVGL v9.2.2
  - **功能全面**: 已启用所有常用控件（Slider, Switch, Roller, List, Keyboard 等）及高级布局引擎 (Flex, Grid)。
  - **交互体验**: 已对接电容触摸输入，支持点击、滑动等标准交互动作。
  - **显存管理**: 使用外部 1MB SRAM 中的 64KB 空间作为 LVGL 动态内存池 (起始于 0x68000000)。
- **硬件驱动 (BSP)**:
  - **显示**: ILI9806 (800x480) MCU 并行接口驱动，支持横屏显示。
  - **触摸**: GT9xxx 电容触摸驱动，极致精简优化，仅保留核心通信逻辑。
  - **Flash**: 基于 **LibDriver W25QXX** 实现了 W25Q128 的全功能驱动。
    - **高度兼容**: 针对国产 Flash 芯片修改了厂商 ID 校验逻辑，支持 ZettaDevice、BoyaMicro 等多种兼容芯片。
    - **自动初始化**: 驱动已深度集成至 `BSP_Init`，支持上电自动识别与配置。
    - **分层接口**: 提供 `basic` (常用读写) 与 `advance` (扇区管理、状态寄存器) 两套 API 接口。
  - **ADC**: 实现 **1Msps** 高速原始采样，采用定时器硬件触发 + DMA 循环搬运。
    - **双缓冲 (Ping-Pong) 机制**: 采用 **5120** 点 (10KB) 大容量缓冲区，配合半完成 (`HalfCplt`) 与全完成 (`Cplt`) 中断，实现数据采集与抽取的并行处理。
    - **内存布局**: 采样缓冲区与 FIFO 结构体均部署于 **片内 SRAM**，通过 DMA 高效传输，并利用 **10:1 抽取** 降低 CPU 处理负担。
    - **高效抽取**: 在 ISR 中实现 **10:1 硬件级抽取**（有效 $F_s = 100kHz$），支持后续 2048 点 FFT 计算。
    - **频谱分析**: 集成 2048 点 FFT 算法，实时提取 **50Hz - 500Hz** 的频率分量。
  - **DAC**: 支持 DMA 循环输出模式，可用于波形发生器。
  - **延时**: 指令级 `delay_us` 确保系统全阶段时序稳定，解决初始化卡死风险。
- **应用层 (App)**:
  - **数据处理**: 独立后台任务 (`adc_process`)，基于生产者-消费者模型，实时处理采样数据并更新全局状态。
  - **PRPD 渲染引擎**: 
    - **自定义绘图**: 基于 `LV_EVENT_DRAW_MAIN_END` 事件，绕过传统的对象式绘图，直接在内容区进行像素级渲染，支持数千个散点的高频刷新而不卡顿。
    - **热力色谱映射**: 实现了基于放电频次的动态颜色映射（深红-鲜红-橙-黄），直观展示放电能量聚集区。
    - **实时波形叠加**: 支持将 512 点原始 ADC 波形作为背景参考线与 PRPD 散点同步显示，方便相位对齐分析。
- **底层驱动**: STM32Cube HAL 库
- **开发工具**: STM32CubeIDE

## 代码规范与格式化

本项目使用 `clang-format` 工具进行 C/C++ 代码格式化，以确保代码风格的统一性。

- **格式化风格**: 基于 LLVM 风格，并进行以下自定义配置：
  - 使用 Tab 缩进，Tab 宽度为 4。
  - 函数、`if`/`for`/`while` 语句的大括号另起一行 (Allman 风格)。
  - `extern "C"` 块内部不进行额外缩进。
  - 行宽限制为 200 个字符。
  - 函数参数尽可能打包到一行。
  - 行尾注释前有两个空格。

- **配置文件**: 项目根目录下的 [.clang-format](file:///c:/work/github/-stm32f407zg-lvgl/.clang-format) 文件定义了详细的格式化规则。

- **快速格式化**:
  为了方便地对项目代码进行格式化，我们提供了一个 PowerShell 脚本。

  1.  **安装 `clang-format`**:
      请参考 `clang-format` 官方文档安装最新版本，或从 [LLVM 发布页面](https://releases.llvm.org/download.html) 下载适用于 Windows 的 LLVM 安装程序，并提取 `clang-format.exe` 到 `C:\work\github\-stm32f407zg-lvgl\tools` 目录下。

  2.  **运行格式化脚本**:
      打开 PowerShell 终端，导航到项目根目录 (`C:\work\github\-stm32f407zg-lvgl`)，然后运行：
      ```powershell
      .\tools\format_code.ps1
      ```
      该脚本将自动遍历 `Core/BSP` 和 `Core/app` 目录下的所有 `.c` 和 `.h` 文件并进行格式化。
      **注意**: 在运行脚本前，请确保您已备份代码或使用版本控制，因为格式化操作会直接修改文件内容。

## 快速开始

1. **环境准备**: 安装 STM32CubeIDE (建议 v1.15.0+)。
2. **导入项目**: 将本仓库代码导入 IDE 中。
3. **编译烧录**: 连接开发板，编译项目并下载至芯片。
   - 注意：本项目已针对 `text` 段大小进行深度优化。
4. **查看结果**: 观察 LCD 屏幕显示及 LED 闪烁状态，通过串口助手查看调试信息。
