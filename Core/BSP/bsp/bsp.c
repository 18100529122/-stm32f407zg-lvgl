#include "bsp.h"
#include "bsp_usart.h"

/**
 * @brief 硬件抽象层初始化 (板级支持包初始化)
 */
void BSP_Init(void)
{
    /* 初始化串口 */
    BSP_USART_Init();
    
    /* 这里可以添加其他外设的初始化，如 LCD, Key, LED 等 */
}
