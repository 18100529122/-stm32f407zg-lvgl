/**
 ****************************************************************************************************
 * @file        lcd.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.1
 * @date        2023-05-29
 * @brief       2.8寸/3.5寸/4.3寸/7寸 TFTLCD(MCU屏) 驱动代码
 ****************************************************************************************************
 */

#ifndef __LCD_H
#define __LCD_H

#include "main.h"
#include "stdlib.h"

/******************************************************************************************/
/* LCD RST/WR/RD/BL/CS/RS 引脚 定义 */

#define LCD_WR_GPIO_PORT GPIOD
#define LCD_WR_GPIO_PIN	 GPIO_PIN_5

#define LCD_RD_GPIO_PORT GPIOD
#define LCD_RD_GPIO_PIN	 GPIO_PIN_4

#define LCD_BL_GPIO_PORT GPIOB
#define LCD_BL_GPIO_PIN	 GPIO_PIN_15

#define LCD_CS_GPIO_PORT GPIOG
#define LCD_CS_GPIO_PIN	 GPIO_PIN_12

#define LCD_RS_GPIO_PORT GPIOF
#define LCD_RS_GPIO_PIN	 GPIO_PIN_12

/* FSMC相关参数 定义 */
#define LCD_FSMC_NEX	 4			   /* 使用FSMC_NE4接LCD_CS */
#define LCD_FSMC_AX		 6			   /* 使用FSMC_A6接LCD_RS */

/******************************************************************************************/

/* LCD重要参数集 */
typedef struct
{
	uint16_t width;		/* LCD 宽度 */
	uint16_t height;	 /* LCD 高度 */
	uint16_t id;		 /* LCD ID */
	uint8_t dir;		 /* 横屏还是竖屏控制：0，竖屏；1，横屏。 */
	uint16_t wramcmd;	  /* 开始写gram指令 */
	uint16_t setxcmd;	  /* 设置x坐标指令 */
	uint16_t setycmd;	  /* 设置y坐标指令 */
} _lcd_dev;

/* LCD参数 */
extern _lcd_dev lcddev; /* 管理LCD重要参数 */

/* LCD的画笔颜色和背景色 */
extern uint32_t g_point_color;	   /* 默认红色 */
extern uint32_t g_back_color;	  /* 背景颜色.默认为白色 */

/* LCD背光控制 */
#define LCD_BL(x)                                                                                                                                                                                      \
	do                                                                                                                                                                                                 \
	{                                                                                                                                                                                                  \
		x ? HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN, GPIO_PIN_RESET);                                                 \
	} while (0)

/* LCD地址结构体 */
typedef struct
{
	volatile uint16_t LCD_REG;
	volatile uint16_t LCD_RAM;
} LCD_TypeDef;

/* LCD_BASE 计算公式 */
#define LCD_BASE			(uint32_t)((0x60000000 + (0x4000000 * (LCD_FSMC_NEX - 1))) | (((1 << LCD_FSMC_AX) * 2) - 2))
#define LCD					((LCD_TypeDef *)LCD_BASE)

/******************************************************************************************/
/* LCD扫描方向和颜色 定义 */

/* 扫描方向定义 */
#define L2R_U2D				0			  /* 从左到右,从上到下 */
#define L2R_D2U				1			  /* 从左到右,从下到上 */
#define R2L_U2D				2			  /* 从右到左,从上到下 */
#define R2L_D2U				3			  /* 从右到左,从下到上 */

#define U2D_L2R				4			  /* 从上到下,从左到右 */
#define U2D_R2L				5			  /* 从上到下,从右到左 */
#define D2U_L2R				6			  /* 从下到上,从左到右 */
#define D2U_R2L				7			  /* 从下到上,从右到左 */

#define DFT_SCAN_DIR		L2R_U2D		/* 默认的扫描方向 */

/* 常用画笔颜色 */
#define WHITE				0xFFFF	   /* 白色 */
#define BLACK				0x0000	   /* 黑色 */
#define RED					0xF800	   /* 红色 */
#define GREEN				0x07E0	   /* 绿色 */
#define BLUE				0x001F	   /* 蓝色 */
#define MAGENTA				0xF81F	   /* 品红色/紫红色 = BLUE + RED */
#define YELLOW				0xFFE0	   /* 黄色 = GREEN + RED */
#define CYAN				0x07FF	   /* 青色 = GREEN + BLUE */

/* 非常用颜色 */
#define BROWN				0xBC40	   /* 棕色 */
#define BRRED				0xFC07	   /* 棕红色 */
#define GRAY				0x8430	   /* 灰色 */
#define DARKBLUE			0x01CF	   /* 深蓝色 */
#define LIGHTBLUE			0x7D7C	   /* 浅蓝色 */
#define GRAYBLUE			0x5458	   /* 灰蓝色 */
#define LIGHTGREEN			0x841F	   /* 浅绿色 */
#define LGRAY				0xC618	   /* 浅灰色(PANNEL),窗体背景色 */
#define LGRAYBLUE			0xA651	   /* 浅灰蓝色(中间层颜色) */
#define LBBLUE				0x2B12	   /* 浅棕蓝色(选择条目的反色) */
/******************************************************************************************/
/* SSD1963相关配置参数(一般不用改) */

/* LCD分辨率设置 */
#define SSD_HOR_RESOLUTION	800		/* LCD水平分辨率 */
#define SSD_VER_RESOLUTION	480		/* LCD垂直分辨率 */

/* LCD驱动参数设置 */
#define SSD_HOR_PULSE_WIDTH 1		  /* 水平脉宽 */
#define SSD_HOR_BACK_PORCH	46	   /* 水平前廊 */
#define SSD_HOR_FRONT_PORCH 210		/* 水平后廊 */

#define SSD_VER_PULSE_WIDTH 1		  /* 垂直脉宽 */
#define SSD_VER_BACK_PORCH	23	   /* 垂直前廊 */
#define SSD_VER_FRONT_PORCH 22	   /* 垂直前廊 */

/* 如下几个参数，自动计算 */
#define SSD_HT				(SSD_HOR_RESOLUTION + SSD_HOR_BACK_PORCH + SSD_HOR_FRONT_PORCH)
#define SSD_HPS				(SSD_HOR_BACK_PORCH)
#define SSD_VT				(SSD_VER_RESOLUTION + SSD_VER_BACK_PORCH + SSD_VER_FRONT_PORCH)
#define SSD_VPS				(SSD_VER_BACK_PORCH)

/******************************************************************************************/
/* 函数声明 */

void lcd_wr_data(volatile uint16_t data);			  /* LCD写数据 */
void lcd_wr_regno(volatile uint16_t regno);			/* LCD写寄存器编号/地址 */
void lcd_write_reg(uint16_t regno, uint16_t data);   /* LCD写寄存器的值 */

void lcd_init(void);						/* 初始化LCD */
void lcd_display_on(void);				   /* 开显示 */
void lcd_display_off(void);					/* 关显示 */
void lcd_scan_dir(uint8_t dir);				/* 设置屏扫描方向 */
void lcd_display_dir(uint8_t dir);		   /* 设置屏幕显示方向 */

void lcd_write_ram_prepare(void);							  /* 准备写GRAM */
void lcd_set_cursor(uint16_t x, uint16_t y);				 /* 设置光标 */
uint32_t lcd_read_point(uint16_t x, uint16_t y);			 /* 读点 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color);/* 画点 */

void lcd_clear(uint16_t color);															 /* LCD清屏 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);		   /* 纯色填充矩形 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);		/* 画直线 */
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);	  /* 颜色块填充矩形 */

void lcd_dma_init(void);									/* LCD DMA初始化 */
void lcd_dma_show(uint16_t *color, uint32_t size);		   /* LCD DMA传输 */
void lcd_dma_wait_done(void);							   /* 等待DMA完成 */

#endif /* __LCD_H */
