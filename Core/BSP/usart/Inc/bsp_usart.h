#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "main.h"
#include "usart.h"

/* DMA 接收缓冲区大小 */
#define USART_RX_BUF_SIZE 256

extern uint8_t g_usart_rx_buf[USART_RX_BUF_SIZE];

/**
 * @brief 初始化 BSP USART (启动 DMA 接收)
 */
void BSP_USART_Init(void);

/**
 * @brief 通过 DMA 发送数据
 * @param data 数据指针
 * @param len 数据长度
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef BSP_USART_Send_DMA(uint8_t *data, uint16_t len);

#endif /* __BSP_USART_H */
