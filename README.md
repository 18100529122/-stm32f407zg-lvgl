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

### 1. 基础外设
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **LED0** | PF9 | 系统运行指示灯（低电平点亮） |
| **LED1** | PF10 | 系统状态指示灯（低电平点亮） |
| **UART1 TX** | PA9 | 调试串口发送（波特率 115200） |
| **UART1 RX** | PA10 | 调试串口接收（波特率 115200） |
| **USB_2_UART** | CH340C | 支持 DTR/RTS 自动下载电路 |

### 2. 用户交互 (按键、蜂鸣器等)
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **KEY0** | PE4 | 用户按键 0 |
| **KEY1** | PE3 | 用户按键 1 |
| **KEY2** | PE2 | 用户按键 2 |
| **WK_UP** | PA0 | 唤醒/用户按键 (高电平有效) |
| **TPAD** | PA5 | 电容触摸按键 |
| **BEEP** | PF8 | 蜂鸣器控制 (高电平响) |
| **LED0** | PF9 | 系统运行指示灯 (DS0) |
| **LED1** | PF10 | 系统状态指示灯 (DS1) |
| **PWR_LED** | POWER | 电源指示灯 (蓝色) |
| **LIGHT_SENSOR**| PF7 | 光敏电阻模拟输入 |

### 3. LCD 显示屏 (FSMC 接口)
本项目使用 FSMC 16 位并行接口驱动液晶屏：
| 功能 | 引脚 | FSMC 定义 |
| :--- | :--- | :--- |
| **LCD_CS** | PG12 | FSMC_NE4 |
| **LCD_RS** | PF12 | FSMC_A6 (Register Select) |
| **LCD_RST** | RESET | 液晶屏复位 (连接系统复位) |
| **LCD_WR** | PD5 | FSMC_NWE (Write Enable) |
| **LCD_RD** | PD4 | FSMC_NOE (Output Enable) |
| **LCD_BL** | PB15 | 背光控制 (Backlight) |
| **LCD_D0~D15** | PD/PE 端口 | 16位并行数据线 |

### 3. SPI Flash (W25Q128)
用于存储图片、字库等资源：
| 功能 | 引脚 | 备注 |
| :--- | :--- | :--- |
| **SPI1_SCK** | PB3 | SPI1 时钟 |
| **SPI1_MISO** | PB4 | SPI1 主机输入 |
| **SPI1_MOSI** | PB5 | SPI1 主机输出 |
| **SPI1_CS** | PB14 | 片选信号 |

### 4. 外部 SRAM (FSMC 接口)
本项目使用 FSMC 接口扩展 1MB 外部 SRAM，常用于 LVGL 显存、内存池或大规模数据缓冲区。

**存储空间划分说明 (Total: 1MB, Address: 0x68000000 - 0x680FFFFF)**:

| 起始地址 | 长度 | 用途 | 模块引用 |
| :--- | :--- | :--- | :--- |
| `0x68000000` | ~160KB | LVGL 显存 (Display Buffer) | `lv_port_disp.c` |
| `0x68040000` | 128KB | LVGL 动态内存池 (Memory Pool) | `lv_conf.h` |

**注**：ADC 缓冲区及 FFT 计算缓存已迁移至 **片内 SRAM**，以避免与 LCD 刷屏产生 FSMC 总线竞争。

| 功能 | 引脚 | FSMC 定义 |
| :--- | :--- | :--- |
| **SRAM_CS** | PG10 | FSMC_NE3 |
| **SRAM_WE** | PD5 | FSMC_NWE |
| **SRAM_OE** | PD4 | FSMC_NOE |
| **SRAM_UB** | PE1 | FSMC_NBL1 (Upper Byte Control) |
| **SRAM_LB** | PE0 | FSMC_NBL0 (Lower Byte Control) |
| **SRAM_D0~D15** | PD/PE 端口 | 16位并行数据线 |
| **SRAM_A0~A18** | PF/PG/PD 端口 | 19位地址线 |

### 5. 模拟外设
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **ADC1_IN5** | PA5 | 模拟信号采集测试 |
| **DAC_OUT1** | PA4 | 模拟信号输出测试 |

### 6. 以太网接口 (RMII 模式)
使用 YT8512C PHY 芯片：
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **RMII_REF_CLK** | PA1 | 参考时钟 (50MHz) |
| **RMII_MDIO** | PA2 | 管理数据接口 (与 RS232/RS485 共用) |
| **RMII_MDC** | PC1 | 管理时钟接口 |
| **RMII_CRS_DV** | PA7 | 载波侦听/数据有效 |
| **RMII_RXD0** | PC4 | 接收数据 0 |
| **RMII_RXD1** | PC5 | 接收数据 1 |
| **RMII_TX_EN** | PG11 | 发送使能 |
| **RMII_TXD0** | PG13 | 发送数据 0 |
| **RMII_TXD1** | PG14 | 发送数据 1 |
| **ETH_RESET** | PD3 | 复位引脚 (带 10K 下拉) |

### 7. 音频接口 (I2S + I2C)
使用 ES8388 音频编解码芯片：
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **I2S_MCLK** | PC6 | 主时钟 |
| **I2S_SCLK** | PB13 | 位时钟 (BCLK) |
| **I2S_LRCK** | PB12 | 左右声道选择时钟 (WS) |
| **I2S_SDIN** | PC3 | 数据输入 (ADC) |
| **I2S_SDOUT** | PC2 | 数据输出 (DAC) |
| **IIC_SCL** | PB8 | 控制接口时钟 |
| **IIC_SDA** | PB9 | 控制接口数据 |

### 8. PWM 音频
使用 MD8002A 功率放大器：
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **PWM_DAC** | PA3 | PWM 模拟音频输出 |

### 9. USB OTG 接口
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **USB_DP** | PA12 | USB 数据正 (D+) |
| **USB_DM** | PA11 | USB 数据负 (D-) |
| **USB_PWR** | PA15 | USB 电源控制 (高电平有效) |

### 10. SD 卡接口 (SDIO)
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **SDIO_CLK** | PC12 | 时钟线 |
| **SDIO_CMD** | PD2 | 命令线 |
| **SDIO_D0** | PC8 | 数据线 0 |
| **SDIO_D1** | PC9 | 数据线 1 |
| **SDIO_D2** | PC10 | 数据线 2 |
| **SDIO_D3** | PC11 | 数据线 3 |

### 11. 摄像头接口 (DCMI)
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **DCMI_PCLK** | PA6 | 像素时钟 |
| **DCMI_HSYNC** | PA4 | 行同步信号 |
| **DCMI_VSYNC** | PB7 | 场同步信号 |
| **OV_SCL** | PD6 | SCCB 时钟 (I2C) |
| **OV_SDA** | PD7 | SCCB 数据 (I2C) |
| **DCMI_D0~D7** | PC/PB/PE 端口 | 8 位数据线 |

### 12. 触摸屏控制
#### 电阻式触摸 (XPT2046)
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **T_SCK** | PB0 | SPI 时钟 |
| **T_MOSI** | PF11 | SPI 输出 |
| **T_MISO** | PB2 | SPI 输入 |
| **T_CS** | PC13 | 片选信号 |
| **T_PEN** | PB1 | 触摸中断 (IRQ) |

#### 电容式触摸 (I2C 接口)
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **CT_SCL** | PB0 | I2C 时钟 (与 T_SCK 复用) |
| **CT_SDA** | PF11 | I2C 数据 (与 T_MOSI 复用) |
| **CT_INT** | PB1 | 触摸中断 (与 T_PEN 复用) |
| **CT_RST** | PC13 | 复位引脚 (与 T_CS 复用) |

### 13. 系统其他
| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **BOOT0** | BOOT0 | 启动模式选择 |
| **RESET** | NRST | 系统复位引脚 |
| **RTC_CLK** | PC14/PC15 | 32.768kHz 外部晶振 |

### 14. 其他通信接口
- **RS232**: 使用 TPT3232 收发芯片
- **RS485**: 使用 TPT8485 收发芯片
- **CAN**: 使用 SIT1050T 收发芯片
- **I2C 总线设备**: EEPROM (24C02), 磁力计 (QMA6100P)

| 功能 | 引脚 | 说明 |
| :--- | :--- | :--- |
| **USART2_TX** | PA2 | RS232 (COM2) 发送 (与 RS485/以太网共用，P4切换) |
| **USART2_RX** | PA3 | RS232 (COM2) 接收 (与 RS485/PWM_DAC共用，P4切换) |
| **USART3_TX** | PB10 | RS232 (COM3) 发送 (与 ATK-MODULE 共用，P2切换) |
| **USART3_RX** | PB11 | RS232 (COM3) 接收 (与 ATK-MODULE 共用，P2切换) |
| **CAN1_TX** | PD1 | CAN 总线发送 (与 RS485/FSMC 共用，P5切换) |
| **CAN1_RX** | PD0 | CAN 总线接收 (与 RS485/FSMC 共用，P5切换) |
| **RS485_RE** | PG8 | RS485 收发控制 (与 NRF_IRQ 共用) |
| **IIC_SCL** | PB8 | I2C 总线时钟 (有 4.7K 上拉) |
| **IIC_SDA** | PB9 | I2C 总线数据 (有 4.7K 上拉) |
| **3D_INT** | PC0 | 磁力计中断引脚 |
| **1WIRE_DQ** | PG9 | 单总线接口 (与 DCMI_PWDN 共用，有 4.7K 上拉) |
| **NRF_CS** | PG7 | NRF24L01 片选 |
| **NRF_CE** | PG6 | NRF24L01 模块使能 |
| **NRF_IRQ** | PG8 | NRF24L01 中断输出 (与 RS485_RE 共用) |
| **REMOTE_IN** | PA8 | 红外遥控接收 (与 DCMI_XCLK 共用) |
| **ATK_MODULE** | UART4 | 扩展模块接口 (GBC_TX: PC10, GBC_RX: PC11) |
| **ATK_KEY** | PF6 | 扩展模块功能按键 |
| **ATK_LED** | PC0 | 扩展模块指示灯 |

### 15. 系统电源
- **DC电源输入**：支持 6V-24V 宽电压输入 (RY9125 降压至 5V)
- **USB电源输入**：支持 Type-C/Mini-USB 5V 供电
- **系统主电源**：AMS1117-3.3 提供 3.3V 系统电压
- **模拟电源**：独立 LDO 提供 3.3V 模拟电源 (VCCA)，减少干扰

## 软件架构与特性

- **操作系统**: FreeRTOS
  - 采用专用的 LVGL 刷新线程 (`lvglTask`)，刷新周期 15ms。
  - **异步数据更新**: UI 数据更新任务 (`lvglDataTask`) 采用 **500ms 定时轮询** 模式，解耦了后台计算与前端显示。
  - 使用 `lv_lock/unlock` 互斥量确保多线程环境下的 UI 操作安全。
- **图形库**: LVGL v9.2.2
  - **功能全面**: 已启用所有常用控件（Slider, Switch, Roller, List, Keyboard 等）及高级布局引擎 (Flex, Grid)。
  - **交互体验**: 已对接电容触摸输入，支持点击、滑动等标准交互动作。
  - **显存管理**: 使用外部 1MB SRAM 中的 128KB 空间作为 LVGL 动态内存池 (0x68040000)。
- **硬件驱动 (BSP)**:
  - **显示**: ILI9806 (800x480) MCU 并行接口驱动，支持横屏显示。
  - **触摸**: GT9xxx 电容触摸驱动，极致精简优化，仅保留核心通信逻辑。
  - **ADC**: 实现 **1Msps** 高速原始采样，采用定时器硬件触发 + DMA 循环搬运。
    - **内存优化**: 采样缓冲区与 FIFO 结构体均部署于 **片内 SRAM**，彻底解决了与 LCD 刷屏任务抢占 FSMC 总线导致的 DMA 停滞问题。
    - **高效抽取**: 在 ISR 中实现 **200 倍硬件级抽取**（有效 $F_s = 5kHz$），采用索引跳转优化算法，极大地降低了中断 CPU 占用。
    - **优先级管理**: 严格配置 NVIC 优先级，确保 ADC DMA (6) 高于 LCD DMA (7)，保障采样时序严谨。
    - **频谱分析**: 集成 512 点 FFT 算法，实时提取 **50Hz - 500Hz** 的频率分量。
    - **启动同步**: 采样启动逻辑被封装在数据处理任务中，确保后台消费者就绪后才开启前端生产，消除系统初始化阶段的数据丢包。
    - **健壮性保护**: 引入 **"溢出即停止" (Stop-on-Full)** 机制，当 FIFO 满载且处理不及时时自动停止 DMA，并在数据处理完成后自动恢复采样，确保数据处理的时序一致性。
  - **DAC**: 支持 DMA 循环输出模式，可用于波形发生器。
  - **延时**: 指令级 `delay_us` 确保系统全阶段时序稳定，解决初始化卡死风险。
- **应用层 (App)**:
  - **数据处理**: 独立后台任务 (`adc_process`)，基于生产者-消费者模型，实时处理采样数据并更新全局状态。
- **底层驱动**: STM32Cube HAL 库
- **开发工具**: STM32CubeIDE

## 快速开始

1. **环境准备**: 安装 STM32CubeIDE (建议 v1.15.0+)。
2. **导入项目**: 将本仓库代码导入 IDE 中。
3. **编译烧录**: 连接开发板，编译项目并下载至芯片。
   - 注意：本项目已针对 `text` 段大小进行深度优化。
4. **查看结果**: 观察 LCD 屏幕显示及 LED 闪烁状态，通过串口助手查看调试信息。
