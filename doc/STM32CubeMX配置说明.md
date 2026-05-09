# STM32CubeMX 配置说明 (正点原子探索者 + LVGL)

本文档详细描述了在 STM32CubeMX 中为 LVGL 项目配置 STM32F407ZGT6 的具体步骤。

## 1. 系统核心配置 (System Core)

### RCC (时钟源)
- **High Speed Clock (HSE)**: `Crystal/Ceramic Resonator`

### SYS (系统调试)
- **Debug**: `Serial Wire` (SWD 调试)
- **Timebase Source**: `TIM14` (由于使用 FreeRTOS，建议将 HAL 库基准时钟切换到定时器)

### Clock Configuration (时钟树)
- **HCLK (MHz)**: 输入 `168` 并回车，自动配置最大主频。

---

## 2. 存储器配置 (Connectivity -> FSMC)

### SRAM 3 (外部 SRAM - 1MB)
用于为 LVGL 提供大容量运行内存和显存缓冲区。
- **Mode**:
    - **Selection**: `SRAM 3` (对应引脚 PG10)
    - **Memory type**: `SRAM`
    - **Address**: `19 bits`
    - **Data**: `16 bits`
- **Parameter Settings**:
    - **Write Operation**: `Enabled` (务必开启)
    - **Extended Mode**: `Disabled`
- **Timing (参考时序)**:
    - `Address setup time`: `1`
    - `Data setup time`: `8`

### SRAM 4 (LCD 接口)
将液晶屏作为 SRAM 4 进行寻址访问。
- **Mode**:
    - **Selection**: `SRAM 4` (对应引脚 PG12)
    - **Memory type**: `LCD Interface`
    - **LCD Register Select**: `A6` (对应引脚 PF12)
    - **Data**: `16 bits`
- **Parameter Settings**:
    - **Write Operation**: `Enabled`
    - **Extended Mode**: `Enabled` (建议开启以独立优化读写时序)
- **Timing (初始保守时序)**:
    - `Address setup time`: `15`
    - `Data setup time`: `60`

---

## 3. GPIO 引脚配置

### LCD 辅助
- **PB15**: `GPIO_Output`, Label: `LCD_BL` (背光控制，默认 High)

### GT9147 电容触摸屏 (软件 I2C)
- **PB0**: `GPIO_Output`, Label: `CT_SCL`
- **PF11**: `GPIO_Output`, Label: `CT_SDA`
- **PC13**: `GPIO_Output`, Label: `CT_RST`
- **PB1**: `GPIO_Input`, Label: `CT_INT` (可配置为 EXTI 中断模式)

### 指示灯
- **PF9**: `GPIO_Output`, Label: `LED0`
- **PF10**: `GPIO_Output`, Label: `LED1`

---

## 4. 调试串口 (Connectivity -> USART1)
- **Mode**: `Asynchronous`
- **Baud Rate**: `115200`
- **Word Length**: `8 Bits`

---

## 5. 操作系统 (Middleware -> FREERTOS)
- **Interface**: `CMSIS_V2`
- **Tasks and Queues**:
    - `defaultTask`: **Stack Size** 修改为 `1024` (4096 Bytes) 或更高。
- **Config parameters**:
    - `TOTAL_HEAP_SIZE`: 建议 `32768` (32KB)，剩余显存通过外部 SRAM 管理。

---

## 6. 生成代码设置 (Project Manager)
- **Toolchain / IDE**: `STM32CubeIDE`
- **Code Generator**:
    - 勾选 `Generate peripheral initialization as a pair of '.c/.h' files per peripheral`。
