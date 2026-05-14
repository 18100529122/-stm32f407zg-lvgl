/**
 ****************************************************************************************************
 * @file        lcd.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.1
 * @date        2023-05-29
 * @brief       2.8寸/3.5寸/4.3寸/7寸 TFTLCD(MCU屏) 驱动代码
 ****************************************************************************************************
 */

#include "lcd.h"
#include "lcdfont.h"
#include <stdio.h>
#include <stdlib.h>

/* 包含初始化代码 */
extern void lcd_ex_st7789_reginit(void);
extern void lcd_ex_ili9341_reginit(void);
extern void lcd_ex_nt35310_reginit(void);
extern void lcd_ex_st7796_reginit(void);
extern void lcd_ex_nt35510_reginit(void);
extern void lcd_ex_ili9806_reginit(void);
extern void lcd_ex_ssd1963_reginit(void);



/* LCD重要参数集 */
_lcd_dev lcddev;

/* 画笔颜色,背景颜色 */
uint32_t g_point_color = RED;    /* 画笔颜色 */
uint32_t g_back_color  = WHITE;  /* 背景颜色 */

/**
 * @brief       写数据到LCD
 * @param       data: 要写入的数据
 * @retval      无
 */
void lcd_wr_data(volatile uint16_t data)
{
    LCD->LCD_RAM = data;
}

/**
 * @brief       写寄存器编号/地址到LCD
 * @param       regno: 寄存器编号/地址
 * @retval      无
 */
void lcd_wr_regno(volatile uint16_t regno)
{
    LCD->LCD_REG = regno;
}

/**
 * @brief       写寄存器
 * @param       regno: 寄存器编号/地址
 * @param       data: 要写入的数据
 * @retval      无
 */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
    LCD->LCD_REG = regno;
    LCD->LCD_RAM = data;
}

/**
 * @brief       LCD延时函数,仅用于部分在mdk -O1时间优化时需要设置的地方
 * @param       t:延时的数值
 * @retval      无
 */
static void lcd_opt_delay(uint32_t i)
{
    while (i--); /* 使用AC6时空循环可能被优化,可使用while(1) __asm volatile(""); */
}

/**
 * @brief       读LCD数据
 * @param       无
 * @retval      读取到的数据
 */
static uint16_t lcd_rd_data(void)
{
    return LCD->LCD_RAM;
}

/**
 * @brief       准备写GRAM
 * @param       无
 * @retval      无
 */
void lcd_write_ram_prepare(void)
{
    LCD->LCD_REG = lcddev.wramcmd;
}

/**
 * @brief       设置光标位置(对RGB屏无效)
 * @param       x,y: 坐标
 * @retval      无
 */
void lcd_set_cursor(uint16_t x, uint16_t y)
{
    if (lcddev.id == 0x1963)
    {
        if (lcddev.dir == 0)    /* 竖屏模式, x坐标需要变换 */
        {
            x = lcddev.width - 1 - x;
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(0);
            lcd_wr_data(0);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
        }
        else                    /* 横屏模式 */
        {
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
            lcd_wr_data((lcddev.width - 1) >> 8);
            lcd_wr_data((lcddev.width - 1) & 0xFF);
        }

        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);

    }
    else if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(y & 0xFF);
    }
    else    /* 9341/5310/7789/7796/9806 等 设置坐标 */
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
    }
}

/**
 * @brief       读取个某点的颜色值
 * @param       x,y:坐标
 * @retval      此点的颜色(32位颜色,方便兼容LTDC)
 */
uint32_t lcd_read_point(uint16_t x, uint16_t y)
{
    uint16_t r = 0, g = 0, b = 0;

    if (x >= lcddev.width || y >= lcddev.height)
    {
        return 0;   /* 超过了范围,直接返回 */
    }

    lcd_set_cursor(x, y);       /* 设置坐标 */

    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2E00);   /* 5510 发送读GRAM指令 */
    }
    else
    {
        lcd_wr_regno(0x2E);     /* 9341/5310/1963/7789/7796/9806 等发送读GRAM指令 */
    }


    r = lcd_rd_data();          /* 假读(dummy read) */

    if (lcddev.id == 0x1963)
    {
        return r;   /* 1963直接读就可以 */
    }

    r = lcd_rd_data();          /* 实际坐标颜色 */
    
    if (lcddev.id == 0x7796)    /* 7796 一次读取一个像素值 */
    {
        return r;
    }
    
    /* 9341/5310/5510/7789/9806要分2次读出 */
    b = lcd_rd_data();
    g = r & 0xFF;               /* 对于9341/5310/5510/7789/9806,第一次读取的是RG的值,R在前,G在后,各占8位 */
    g <<= 8;
    
    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));  /* ILI9341/NT35310/NT35510/ST7789/ILI9806需要公式转换一下 */
}

/**
 * @brief       画点
 * @param       x,y: 坐标
 * @param       color: 点的颜色(32位颜色,方便兼容LTDC)
 * @retval      无
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
    lcd_set_cursor(x, y);       /* 设置光标位置 */
    lcd_write_ram_prepare();    /* 开始写入GRAM */
    LCD->LCD_RAM = color;
}

/**
 * @brief       SSD1963背光亮度设置函数
 * @param       pwm: 背光等级,0~100.越大越亮.
 * @retval      无
 */
void lcd_ssd_backlight_set(uint8_t pwm)
{
    lcd_wr_regno(0xBE);         /* 配置PWM输出 */
    lcd_wr_data(0x05);          /* 1设置PWM频率 */
    lcd_wr_data(pwm * 2.55);    /* 2设置PWM占空比 */
    lcd_wr_data(0x01);          /* 3设置C */
    lcd_wr_data(0xFF);          /* 4设置D */
    lcd_wr_data(0x00);          /* 5设置E */
    lcd_wr_data(0x00);          /* 6设置F */
}


/**
 * @brief       在指定区域内填充单个颜色
 * @param       (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 * @param       color:  要填充的颜色(32位颜色,方便兼容LTDC)
 * @retval      无
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
{
    uint16_t i, j;
    uint16_t xlen = 0;
    xlen = ex - sx + 1;

    for (i = sy; i <= ey; i++)
    {
        lcd_set_cursor(sx, i);      /* 设置光标位置 */
        lcd_write_ram_prepare();    /* 开始写入GRAM */

        for (j = 0; j < xlen; j++)
        {
            LCD->LCD_RAM = color;   /* 显示颜色 */
        }
    }
}

/**
 * @brief       清屏函数
 * @param       color: 要清屏的颜色
 * @retval      无
 */
void lcd_clear(uint16_t color)
{
    uint32_t index = 0;
    uint32_t totalpoint = lcddev.width;

    totalpoint *= lcddev.height;    /* 得到总点数 */
    lcd_set_cursor(0x00, 0x0000);   /* 设置光标位置 */
    lcd_write_ram_prepare();        /* 开始写入GRAM */

    for (index = 0; index < totalpoint; index++)
    {
        LCD->LCD_RAM = color;
    }
}

/**
 * @brief       设置LCD的自动扫描方向(对RGB屏无效)
 *   @note
 *              9341/5310/5510/1963/7789/7796/9806等IC已经实际测试
 *              注意:其他函数可能会受到此函数设置的影响(尤其是9341),
 *              所以,一般设置为L2R_U2D即可,如果设置为其他扫描方式,可能导致显示不正常.
 *
 * @param       dir:0~7,代表8个方向(具体定义见lcd.h)
 * @retval      无
 */
void lcd_scan_dir(uint8_t dir)
{
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;

    /* 横屏时，对1963不改变扫描方向！竖屏时1963改变方向(这里仅用于1963的特殊处理,对其他驱动IC无效) */
    if ((lcddev.dir == 1 && lcddev.id != 0x1963) || (lcddev.dir == 0 && lcddev.id == 0x1963))
    {
        switch (dir)   /* 方向转换 */
        {
            case 0:
                dir = 6;
                break;

            case 1:
                dir = 7;
                break;

            case 2:
                dir = 4;
                break;

            case 3:
                dir = 5;
                break;

            case 4:
                dir = 1;
                break;

            case 5:
                dir = 0;
                break;

            case 6:
                dir = 3;
                break;

            case 7:
                dir = 2;
                break;
        }
    }


    /* 根据扫描方式 设置 0x36/0x3600 寄存器 bit 5,6,7 位的值 */
    switch (dir)
    {
        case L2R_U2D:   /* 从左到右,从上到下 */
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;

        case L2R_D2U:   /* 从左到右,从下到上 */
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;

        case R2L_U2D:   /* 从右到左,从上到下 */
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;

        case R2L_D2U:   /* 从右到左,从下到上 */
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;

        case U2D_L2R:   /* 从上到下,从左到右 */
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;

        case U2D_R2L:   /* 从上到下,从右到左 */
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;

        case D2U_L2R:   /* 从下到上,从左到右 */
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;

        case D2U_R2L:   /* 从下到上,从右到左 */
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
    }

    dirreg = 0x36;  /* 对绝大部分驱动IC, 由0x36寄存器控制 */

    if (lcddev.id == 0x5510)
    {
        dirreg = 0x3600;    /* 对于5510, 和其他驱动ic的寄存器有差异 */
    }

     /* 9341 & 7789 & 7796 要设置BGR位 */
    if (lcddev.id == 0x9341 || lcddev.id == 0x7789 || lcddev.id == 0x7796)
    {
        regval |= 0x08;
    }

    lcd_write_reg(dirreg, regval);

    if (lcddev.id != 0x1963)                    /* 1963不做坐标处理 */
    {
        if (regval & 0x20)
        {
            if (lcddev.width < lcddev.height)   /* 交换X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
        else
        {
            if (lcddev.width > lcddev.height)   /* 交换X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
    }

    /* 设置显示区域(开窗)大小 */
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 2);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_regno(lcddev.setxcmd + 3);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 2);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_regno(lcddev.setycmd + 3);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    }
    else
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    }
}

/**
 * @brief       设置LCD显示方向
 * @param       dir:0,竖屏; 1,横屏
 * @retval      无
 */
void lcd_display_dir(uint8_t dir)
{
    lcddev.dir = dir;   /* 竖屏/横屏 */

    if (dir == 0)       /* 竖屏 */
    {
        lcddev.width = 240;
        lcddev.height = 320;

        if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 480;
            lcddev.height = 800;
        }
        else if (lcddev.id == 0x1963)
        {
            lcddev.wramcmd = 0x2C;  /* 设置写入GRAM的指令 */
            lcddev.setxcmd = 0x2B;  /* 设置写X坐标指令 */
            lcddev.setycmd = 0x2A;  /* 设置写Y坐标指令 */
            lcddev.width = 480;     /* 设置宽度480 */
            lcddev.height = 800;    /* 设置高度800 */
        }
        else   /* 其他IC, 包括: 9341/5310/7789/7796/9806等IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796)     /* 如果是5310/7796 则表示是 320*480分辨率 */
        {
            lcddev.width = 320;
            lcddev.height = 480;
        }
        
        if (lcddev.id == 0X9806)    /* 如果是9806 则表示是 480*800 分辨率 */
        {
            lcddev.width = 480;
            lcddev.height = 800;
        }  
    }
    else        /* 横屏 */
    {
        lcddev.width = 320;         /* 默认宽度 */
        lcddev.height = 240;        /* 默认高度 */

        if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 800;
            lcddev.height = 480;
        }
        else if (lcddev.id == 0x1963 || lcddev.id == 0x9806)
        {
            lcddev.wramcmd = 0x2C;  /* 设置写入GRAM的指令 */
            lcddev.setxcmd = 0x2A;  /* 设置写X坐标指令 */
            lcddev.setycmd = 0x2B;  /* 设置写Y坐标指令 */
            lcddev.width = 800;     /* 设置宽度800 */
            lcddev.height = 480;    /* 设置高度480 */
        }
        else   /* 其他IC, 包括:9341/5310/7789/7796等IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796)     /* 如果是5310/7796 则表示是 320*480分辨率 */
        {
            lcddev.width = 480;
            lcddev.height = 320;
        }
    }

    lcd_scan_dir(DFT_SCAN_DIR);     /* 默认扫描方向 */
}

/**
 * @brief       读取LCD控制器寄存器值 (16位)
 * @param       regno: 寄存器编号
 * @retval      读取到的值
 */
static uint16_t lcd_read_reg(uint16_t regno)
{
    lcd_wr_regno(regno);
    return lcd_rd_data();
}

/**
 * @brief       LCD开启显示
 * @param       无
 * @retval      无
 */
void lcd_display_on(void)
{
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2900);   /* 开启显示 */
    }
    else                        /* 9341/5310/1963/7789/7796/9806 等发送开启显示指令 */
    {
        lcd_wr_regno(0x29);     /* 开启显示 */
    }
}

/**
 * @brief       LCD关闭显示
 * @param       无
 * @retval      无
 */
void lcd_display_off(void)
{
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2800);   /* 关闭显示 */
    }
    else                        /* 9341/5310/1963/7789/7796/9806 等发送关闭显示指令 */
    {
        lcd_wr_regno(0x28);     /* 关闭显示 */
    }
}


/**
 * @brief       初始化LCD
 * @param       无
 * @retval      无
 */
void lcd_init(void)
{
    LCD_BL(1);          /* 优先点亮背光，方便观察是否卡死 */
    printf("LCD Init Start...\r\n");
    HAL_Delay(50);
    
    lcd_wr_regno(0xD3);
    lcddev.id = lcd_rd_data();  /* dummy read */
    lcddev.id = lcd_rd_data();  /* 读到0x00 */
    lcddev.id = lcd_rd_data();  /* 读取93 */
    lcddev.id <<= 8;
    lcddev.id |= lcd_rd_data(); /* 读取41 */
    printf("LCD Read ID Done: %x\r\n", lcddev.id);

    do
    {
        if(lcddev.id == 0x9341) break;/* 不是 9341 , 尝试看看是不是 ST7789 */
        if (lcddev.id == 0x9806) break;
        if (lcddev.id == 0x7796) break;
        lcd_wr_regno(0x04);
        lcd_rd_data();              /* dummy read */
        lcd_rd_data();              /* 读到0x85 */
        lcddev.id = lcd_rd_data();  /* 读取0x85 */
        lcddev.id <<= 8;
        lcddev.id |= lcd_rd_data(); /* 读取0x52 */
        if (lcddev.id == 0x8552) lcddev.id = 0x7789;
        if (lcddev.id == 0x7789) break;

        lcd_wr_regno(0xD4);
        lcd_rd_data();              /* dummy read */
        lcd_rd_data();              /* 读回0x01 */
        lcddev.id = lcd_rd_data();  /* 读回0x53 */
        lcddev.id <<= 8;
        lcddev.id |= lcd_rd_data(); /* 这里读回0x10 */
        if (lcddev.id == 0x5310) break;
        
        /* 尝试看看是不是 NT35510 */
        lcd_write_reg(0xF000, 0x0055);
        lcd_write_reg(0xF001, 0x00AA);
        lcd_write_reg(0xF002, 0x0052);
        lcd_write_reg(0xF003, 0x0008);
        lcd_write_reg(0xF004, 0x0001);
        lcd_wr_regno(0xC500);
        lcddev.id = lcd_rd_data() << 8;
        lcd_wr_regno(0xC501);
        lcddev.id |= lcd_rd_data();
        HAL_Delay(5);               /* 等待5ms, 因为0XC501指令对1963来说就是软件复位指令 */
        if (lcddev.id == 0x5510) break;

        lcd_wr_regno(0xA1);
        lcd_rd_data();
        lcddev.id = lcd_rd_data();  /* 读回0x57 */
        lcddev.id <<= 8;
        lcddev.id |= lcd_rd_data(); /* 读回0x61 */
        if (lcddev.id == 0x5761) lcddev.id = 0x1963;
    } while (0);


    /* 特别注意, 如果在main函数里面屏蔽串口1初始化, 则会卡死在printf
     * 里面(卡死在f_putc函数), 所以, 必须初始化串口1, 或者屏蔽掉下面
     * 这行 printf 语句 !!!!!!!
     */
    printf("LCD ID:%x\r\n", lcddev.id); /* 打印LCD ID */

    if (lcddev.id == 0x7789)
    {
        lcd_ex_st7789_reginit();    /* 执行ST7789初始化 */
    }
    else if (lcddev.id == 0x9341)
    {
        lcd_ex_ili9341_reginit();   /* 执行ILI9341初始化 */
    }
    else if (lcddev.id == 0x5310)
    {
        lcd_ex_nt35310_reginit();   /* 执行NT35310初始化 */
    }
    else if (lcddev.id == 0x7796)
    {
        lcd_ex_st7796_reginit();    /* 执行ST7796初始化 */
    }
    else if (lcddev.id == 0x5510)
    {
        lcd_ex_nt35510_reginit();   /* 执行NT35510初始化 */
    }
    else if (lcddev.id == 0x9806)
    {
        lcd_ex_ili9806_reginit();   /* 执行ILI9806初始化 */
    }
    else if (lcddev.id == 0x1963)
    {
        lcd_ex_ssd1963_reginit();   /* 执行SSD1963初始化 */
        lcd_ssd_backlight_set(100); /* 背光设置为最亮 */
    }

    lcd_display_dir(0); /* 默认为竖屏 */
    LCD_BL(1);          /* 点亮背光 */
    lcd_clear(WHITE);
}

/**
 * @brief       画线
 * @param       x1,y1: 起点坐标
 * @param       x2,y2: 终点坐标
 * @param       color: 线的颜色
 * @retval      无
 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;
    delta_x = x2 - x1;      /* 计算坐标增量 */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0)
    {
        incx = 1;       /* 设置单步方向 */
    }
    else if (delta_x == 0)
    {
        incx = 0;       /* 垂直线 */
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy = 0;       /* 水平线 */
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if ( delta_x > delta_y)
    {
        distance = delta_x;  /* 选取基本增量坐标轴 */
    }
    else
    {
        distance = delta_y;
    }

    for (t = 0; t <= distance + 1; t++)     /* 画线输出 */
    {
        lcd_draw_point(row, col, color);    /* 画点 */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance)
        {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            col += incy;
        }
    }
}

/**
 * @brief       在指定位置显示一个字符
 * @param       x,y  : 坐标
 * @param       chr  : 要显示的字符:" "--->"~"
 * @param       size : 字体大小 12/16/24/32
 * @param       mode : 叠加方式(1); 非叠加方式(0);
 * @param       color : 字符的颜色;
 * @retval      无
 */
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = 0;
    uint8_t *pfont = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); /* 得到字体一个字符对应点阵集所占的字节数 */
    chr = chr - ' ';    /* 得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库） */
    uint8_t offset = (uint8_t)chr;

    switch (size)
    {
        case 12:
            pfont = (uint8_t *)asc2_1206[offset];  /* 调用1206字体 */
            break;

        case 16:
            pfont = (uint8_t *)asc2_1608[offset];  /* 调用1608字体 */
            break;

        case 24:
            pfont = (uint8_t *)asc2_2412[offset];  /* 调用2412字体 */
            break;

        case 32:
            pfont = (uint8_t *)asc2_3216[offset];  /* 调用3216字体 */
            break;

        default:
            return ;
    }

    for (t = 0; t < csize; t++)
    {
        temp = pfont[t];                            /* 获取字符的点阵数据 */

        for (t1 = 0; t1 < 8; t1++)                  /* 一个字节8个点 */
        {
            if (temp & 0x80)                        /* 有效点,需要显示 */
            {
                lcd_draw_point(x, y, color);        /* 画点出来,要显示这个点 */
            }
            else if (mode == 0)                     /* 无效点,不显示 */
            {
                lcd_draw_point(x, y, g_back_color); /* 画背景色,相当于这个点不显示(注意背景色由全局变量控制) */
            }

            temp <<= 1;                             /* 移位, 以便获取下一个位的状态 */
            y++;

            if (y >= lcddev.height)return;          /* 超区域了 */

            if ((y - y0) == size)                   /* 显示完一列了? */
            {
                y = y0; /* y坐标复位 */
                x++;    /* x坐标递增 */

                if (x >= lcddev.width)
                {
                    return;       /* x坐标超区域了 */
                }

                break;
            }
        }
    }
}

/**
 * @brief       显示字符串
 * @param       x,y         : 起始坐标
 * @param       width,height: 区域大小
 * @param       size        : 选择字体 12/16/24/32
 * @param       p           : 字符串首地址
 * @param       color       : 字符串的颜色;
 * @retval      无
 */
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
    uint8_t x0 = x;
    
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' '))   /* 判断是不是非法字符! */
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }

        if (y >= height)
        {
            break;      /* 退出 */
        }

        lcd_show_char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}

/**
 * @brief       设置窗口(对RGB屏无效), 并自动设置画点坐标到窗口左上角(sx,sy).
 * @param       sx,sy:窗口起始坐标(左上角)
 * @param       width,height:窗口宽度和高度,必须大于0!!
 *   @note      窗体大小:width*height.
 *
 * @retval      无
 */
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    uint16_t twidth, theight;
    twidth = sx + width - 1;
    theight = sy + height - 1;

   
   if (lcddev.id == 0x1963 && lcddev.dir != 1)     /* 1963竖屏特殊处理 */
    {
        sx = lcddev.width - width - sx;
        height = sy + height - 1;
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_data((sx + width - 1) >> 8);
        lcd_wr_data((sx + width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_data(height >> 8);
        lcd_wr_data(height & 0xFF);
    }
    else if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_regno(lcddev.setxcmd + 2);
        lcd_wr_data(twidth >> 8);
        lcd_wr_regno(lcddev.setxcmd + 3);
        lcd_wr_data(twidth & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_regno(lcddev.setycmd + 2);
        lcd_wr_data(theight >> 8);
        lcd_wr_regno(lcddev.setycmd + 3);
        lcd_wr_data(theight & 0xFF);
    }
    else    /* 9341/5310/7789/1963/7796/9806横屏 等 设置窗口 */
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_data(twidth >> 8);
        lcd_wr_data(twidth & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_data(theight >> 8);
        lcd_wr_data(theight & 0xFF);
    }
}

/**
 * @brief       在指定区域内填充指定颜色块
 * @param       (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 * @param       color: 要填充的颜色数组首地址
 * @retval      无
 */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;            /* 得到填充的宽度 */
    height = ey - sy + 1;           /* 高度 */

    for (i = 0; i < height; i++)
    {
        lcd_set_cursor(sx, sy + i); /* 设置光标位置 */
        lcd_write_ram_prepare();    /* 开始写入GRAM */

        for (j = 0; j < width; j++)
        {
            LCD->LCD_RAM = color[i * width + j]; /* 写入数据 */
        }
    }
}


