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
    lcd_dma_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t * disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    /* 使用外部 SRAM 缓冲区以解决内部 RAM 不足的问题 */
    /* 80 行双缓冲区: 800 * 80 * 2 = 128000 字节 */
    uint32_t buf_size = MY_DISP_HOR_RES * 80 * BYTE_PER_PIXEL;
    uint8_t * buf_2_1 = (uint8_t *)(EXTERNAL_SRAM_BASE);
    uint8_t * buf_2_2 = (uint8_t *)(EXTERNAL_SRAM_BASE + buf_size);
    
    lv_display_set_buffers(disp, buf_2_1, buf_2_2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);
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

        /* 改用 CPU 直接写入，排除 DMA 故障 */
        uint32_t size = width * height;
        uint16_t *p = (uint16_t *)px_map;
        while(size--) {
            LCD->LCD_RAM = *p++;
        }
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
