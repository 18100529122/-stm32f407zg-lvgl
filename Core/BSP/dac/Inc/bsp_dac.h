#ifndef __BSP_DAC_H__
#define __BSP_DAC_H__

#include "main.h"

#define DAC_BUFF_SIZE 1024

extern uint16_t g_dac_buff[DAC_BUFF_SIZE];

void bsp_dac_init(void);
void bsp_dac_set_value(uint16_t value);
void bsp_dac_set_sine_wave(uint32_t frequency);

#endif /* __BSP_DAC_H__ */
