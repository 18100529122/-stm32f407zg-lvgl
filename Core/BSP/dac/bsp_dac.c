#include "bsp_dac.h"
#include "dac.h"

uint16_t g_dac_buff[DAC_BUFF_SIZE];

/**
 * @brief 初始化DAC并开启DMA输出
 */
void bsp_dac_init(void)
{
    /* 启动 DAC DMA 输出 */
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)g_dac_buff, DAC_BUFF_SIZE, DAC_ALIGN_12B_R);
}

/**
 * @brief 设置DAC输出值 (0-4095)
 */
void bsp_dac_set_value(uint16_t value)
{
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
}
