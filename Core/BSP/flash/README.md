# LibDriver W25QXX 移植说明文档 (STM32F407ZG)

本项目基于 [LibDriver W25QXX](https://github.com/libdriver/w25qxx) 驱动库，在 STM32F407ZG (正点原子探索者开发板) 上实现了 W25Q128 (及国产兼容芯片) 的移植。

## 1. 硬件连接

| W25QXX 引脚 | STM32F407 引脚 | 功能 | 备注 |
| :--- | :--- | :--- | :--- |
| **CS** | PB14 | 片选 (Output) | 软件控制，初始状态为 High |
| **SCK** | PB3 | SPI1 时钟 (AF5) | 速率建议 10.5MHz - 42MHz |
| **MISO** | PB4 | SPI1 主机输入 (AF5) | 开启内部上拉以防干扰 |
| **MOSI** | PB5 | SPI1 主机输出 (AF5) | - |

---

## 2. 移植核心说明

### 2.1 底层接口实现 ([driver_w25qxx_interface.c](driver_w25qxx_interface.c))
- **SPI 读写**：通过 `HAL_SPI_Transmit` 和 `HAL_SPI_Receive` 实现了标准 SPI 协议对接。
- **CS 控制**：在每次传输前后自动拉低/拉高 PB14。
- **延时函数**：对接了 `bsp.c` 中的微秒级循环延时 (`delay_us`)，确保 Flash 内部操作时序准确。
- **调试输出**：重定向到串口 1 的 `vprintf`，驱动日志可直接在串口助手查看。

### 2.2 厂商兼容性补丁 ([driver_w25qxx.c](driver_w25qxx.c))
由于许多开发板使用国产兼容芯片（如 ZettaDevice, BoyaMicro 等），其厂商 ID (Manufacturer ID) 与原装 Winbond (`0xEF`) 不同，会导致识别失败。
- **修改内容**：将驱动中原有的严格 16 位 ID 校验，放宽为仅校验低 8 位的**容量 ID** (例如 W25Q128 对应 `0x17`)。
- **效果**：只要容量匹配且指令集兼容，驱动即可正常工作。

---

## 3. STM32CubeMX 配置参考

为了防止重新生成代码时覆盖关键配置，请在 CubeMX 中进行以下设置：

1.  **Connectivity -> SPI1**:
    - **Mode**: Full-Duplex Master
    - **Prescaler**: 8 (或更小以提升速度)
    - **GPIO Settings**:
        - **PB4 (MISO)**: Pull-up, Speed=Very High
        - **PB3/PB5**: Speed=Very High
2.  **System Core -> GPIO**:
    - **PB14**: GPIO Output, Level=High, Speed=Very High
3.  **System Core -> SYS**:
    - **Debug**: Serial Wire (释放 PB3/PB4 的 JTAG 占用)

---

## 4. 使用说明

### 4.1 自动初始化
驱动已整合进板级支持包。在系统启动时，`BSP_Init()` 会自动调用初始化函数：
```c
/* c:\work\github\-stm32f407zg-lvgl\Core\BSP\bsp\bsp.c */
w25qxx_basic_init(W25Q128, W25QXX_INTERFACE_SPI, W25QXX_BOOL_FALSE);
```

### 4.2 基本读写示例
```c
#include "driver_w25qxx_basic.h"

uint8_t data[16] = "Hello Flash";
uint8_t buffer[16];

// 写入数据 (注意：写入前应确保目标扇区已擦除)
w25qxx_basic_write(0x000000, data, 16);

// 读取数据
w25qxx_basic_read(0x000000, buffer, 16);
```

### 4.3 进阶功能 (擦除等)
如需执行扇区擦除等操作，请包含 `driver_w25qxx_advance.h`：
```c
#include "driver_w25qxx_advance.h"

// 擦除 4K 扇区
w25qxx_advance_sector_erase_4k(0x000000);
```

---

## 5. 常见问题
- **识别报错 `id is invalid`**：请查看串口输出的 Read ID 值。如果容量 ID 正确但厂商 ID 不同，确认 [driver_w25qxx.c](driver_w25qxx.c) 的补丁是否生效。
- **读出全是 0xFF**：检查硬件接线，特别是 PB14 (CS) 是否松动，或 SPI 引脚是否被 JTAG 模式占用。

---

## 6. API 函数说明

### 6.1 基础 API ([driver_w25qxx_basic.h](driver_w25qxx_basic.h))

| 函数名 | 功能描述 |
| :--- | :--- |
| `w25qxx_basic_init` | 初始化驱动，设置芯片类型、接口模式及 Dual/Quad SPI 状态 |
| `w25qxx_basic_deinit` | 反初始化驱动 |
| `w25qxx_basic_read` | 在指定地址读取指定长度的数据 |
| `w25qxx_basic_write` | 在指定地址写入指定长度的数据 (内部不包含自动擦除) |
| `w25qxx_basic_chip_erase` | 擦除整片 Flash 芯片内容 |
| `w25qxx_basic_get_id` | 获取制造商 ID 和设备 ID |
| `w25qxx_basic_power_down` | 进入掉电模式以降低功耗 |
| `w25qxx_basic_wake_up` | 从掉电模式中唤醒芯片 |

### 6.2 进阶 API ([driver_w25qxx_advance.h](driver_w25qxx_advance.h))

| 函数名 | 功能描述 |
| :--- | :--- |
| `w25qxx_advance_sector_erase_4k` | 擦除指定的 4KB 扇区 |
| `w25qxx_advance_block_erase_32k` | 擦除指定的 32KB 数据块 |
| `w25qxx_advance_block_erase_64k` | 擦除指定的 64KB 数据块 |
| `w25qxx_advance_page_program` | 页编程 (单次写入长度不超过 256 字节) |
| `w25qxx_advance_fast_read` | 快速读取模式 |
| `w25qxx_advance_get_status1/2/3` | 读取状态寄存器 1, 2 或 3 的值 |
| `w25qxx_advance_set_status1/2/3` | 写入状态寄存器 1, 2 或 3 的值 |
| `w25qxx_advance_get_get_jedec_id` | 获取 3 字节的 JEDEC ID |
| `w25qxx_advance_reset` | 软件复位芯片 |
| `w25qxx_advance_only_spi_get_unique_id` | 获取芯片唯一的 64 位 ID (仅 SPI 模式) |
| `w25qxx_advance_global_block_lock` | 全局块锁定保护 |
| `w25qxx_advance_global_block_unlock` | 全局块解锁 |
