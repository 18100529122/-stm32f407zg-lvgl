#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "main.h"

#define ADC_BUFF_SIZE 1024

extern uint16_t *g_adc_buff;

void bsp_adc_init(void);
void bsp_adc_start(void);
void bsp_adc_stop(void);
uint32_t bsp_adc_get_voltage(uint16_t raw_value);

#endif /* __BSP_ADC_H__ */
