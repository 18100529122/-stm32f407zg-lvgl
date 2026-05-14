#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "main.h"

#define ADC_BUFF_SIZE 1024

extern uint16_t g_adc_buff[ADC_BUFF_SIZE];
extern volatile uint16_t g_adc_average;

void bsp_adc_init(void);
uint32_t bsp_adc_get_voltage(uint16_t raw_value);
uint32_t bsp_adc_get_average_voltage(void);

#endif /* __BSP_ADC_H__ */
