#ifndef __BSP_TIME_H__
#define __BSP_TIME_H__

#include "main.h" // 包含HAL库头文件

void bsp_time_init(void);
uint32_t bsp_time_get_us(void);

#endif /* __BSP_TIME_H__ */