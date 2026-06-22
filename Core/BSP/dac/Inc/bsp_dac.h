#ifndef __BSP_DAC_H__
#define __BSP_DAC_H__

#include "main.h"

#define DAC_BUFF_SIZE 1024

extern uint16_t g_dac_buff[DAC_BUFF_SIZE];

void bsp_dac_init(void);
void bsp_dac_set_value(uint16_t value);
void bsp_dac_set_sine_wave(uint32_t frequency);

/* PD脉冲模拟相关函数 */
void bsp_dac_set_pd_wave(uint32_t frequency, float pd_phase1, float pd_phase2, float pd_amplitude, uint8_t pd_enabled);

#endif /* __BSP_DAC_H__ */
