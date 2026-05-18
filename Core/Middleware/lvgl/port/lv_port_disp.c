/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include "lcd.h"
#include "dma.h"

/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
    #define MY_DISP_HOR_RES    800
#endif

#ifndef MY_DISP_VER_RES
    #define MY_DISP_VER_RES    480
#endif

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */

/* 外部 SRAM 地址定义 (Bank1 NE3) */
#define EXTERNAL_SRAM_BASE  0x68000000

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

static void disp_dma_callback(DMA_HandleTypeDef *hdma);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t * disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    /* 使用外部 SRAM 缓冲区以解决内部 RAM 不足的问题 */
    /* 40 行双缓冲区: 800 * 40 * 2 = 64000 字节 (单次 DMA 传输上限为 65535 像素) */
    uint32_t buf_size = MY_DISP_HOR_RES * 40 * BYTE_PER_PIXEL;
    uint8_t * buf_2_1 = (uint8_t *)(EXTERNAL_SRAM_BASE);
    uint8_t * buf_2_2 = (uint8_t *)(EXTERNAL_SRAM_BASE + buf_size);
    
    lv_display_set_buffers(disp, buf_2_1, buf_2_2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* 注册 DMA 完成回调 */
    hdma_memtomem_dma2_stream1.XferCpltCallback = disp_dma_callback;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /* 初始化 LCD 硬件 已经在BSP中初始化过了,这里只需要设置方向即可 */
    /* 设置为横屏 (根据 800*480 需求) */
    lcd_display_dir(1);
    lcd_scan_dir(3);
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{
    if(disp_flush_enabled) {
        /* 得到填充的宽度和高度 */
        uint16_t width = area->x2 - area->x1 + 1;
        uint16_t height = area->y2 - area->y1 + 1;

        /* 设置LCD窗口并准备写入 */
        lcd_set_window(area->x1, area->y1, width, height);
        lcd_write_ram_prepare();

        /* 确保 DMA 处于就绪状态，防止因上次异常未清除导致 HAL_BUSY */
        if(hdma_memtomem_dma2_stream1.State != HAL_DMA_STATE_READY) {
            HAL_DMA_Abort(&hdma_memtomem_dma2_stream1);
        }

        /* 使用 CubeMX 生成的 DMA 异步写入，释放 CPU */
        HAL_StatusTypeDef status = HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream1, (uint32_t)px_map, (uint32_t)&LCD->LCD_RAM, width * height);
        
        /* 如果 DMA 启动失败（例如传输量超限或 DMA 忙） */
        if(status != HAL_OK) {
            /* 回退到 CPU 同步传输，确保系统不挂起 */
            uint32_t size = width * height;
            uint16_t *p = (uint16_t *)px_map;
            while(size--) {
                LCD->LCD_RAM = *p++;
            }
            /* 手动调用完成信号 */
            lv_display_flush_ready(disp_drv);
        }
    }
    else {
        /* 如果禁用了更新，也需要通知 LVGL 释放缓冲区 */
        lv_display_flush_ready(disp_drv);
    }

    /* IMPORTANT!!!
     * 注意：异步模式下，lv_display_flush_ready(disp_drv) 已经在 disp_dma_callback 中调用。 */
}

/**
 * @brief  DMA 传输完成回调函数
 * @param  hdma: DMA 句柄
 * @retval None
 */
static void disp_dma_callback(DMA_HandleTypeDef *hdma)
{
    lv_display_t * disp = lv_display_get_default();
    if(disp) {
        lv_display_flush_ready(disp);
    }
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
