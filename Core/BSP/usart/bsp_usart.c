#include "bsp_usart.h"
#include <string.h>
#include <stdio.h>

/* 全局接收缓冲区 */
uint8_t g_usart_rx_buf[USART_RX_BUF_SIZE];
uint8_t g_usart_tx_buf[USART_RX_BUF_SIZE];

/**
 * @brief 初始化 BSP USART (启动 DMA 接收)
 */
void BSP_USART_Init(void)
{
    /* 
       使用 HAL_UARTEx_ReceiveToIdle_DMA 开启接收。
       该函数会开启 DMA 接收，并在以下两种情况之一发生时触发 HAL_UARTEx_RxEventCallback：
       1. DMA 缓冲区已满 (256 字节)
       2. 串口线路进入 IDLE (空闲) 状态 (收到不定长数据后的间隙)
    */
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, g_usart_rx_buf, USART_RX_BUF_SIZE);
}

/**
 * @brief 通过 DMA 发送数据
 */
HAL_StatusTypeDef BSP_USART_Send_DMA(uint8_t *data, uint16_t len)
{
    /* 检查串口是否忙碌 */
    if (huart1.gState == HAL_UART_STATE_READY)
    {
        return HAL_UART_Transmit_DMA(&huart1, data, len);
    }
    return HAL_BUSY;
}

/**
  * @brief  UART 接收事件回调 (由 IDLE 中断或 DMA 传输完成触发)
  * @param  huart UART 句柄
  * @param  Size  当前接收到的总数据量
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART1)
    {
        /* 
           1. 忙等待：确保上一次 DMA 发送已彻底完成。
           原因：如果连续收到快速数据包，必须等待 TX 状态机回到 READY，
           否则新的 memcpy 会篡改正在被 DMA 搬运的 tx_buf 内容，导致输出字符丢失或错误。
        */
        while (huart->gState != HAL_UART_STATE_READY);

        /* 2. 数据备份 */
        memcpy(g_usart_tx_buf, g_usart_rx_buf, Size);

        /* 
           3. 彻底重置接收状态：
           使用 HAL_UART_AbortReceive 停止接收，并手动清除所有状态标志。
           这能解决您遇到的 "hallo" 变成 "llo" 的偏移问题（通常是由于 ORE 溢出或 IDLE 未清除）。
        */
        HAL_UART_AbortReceive(huart);
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        __HAL_UART_CLEAR_OREFLAG(huart);
        (void)huart->Instance->DR; // 清除数据寄存器残留
        
        /* 4. 清空缓冲区并重启 DMA 接收 */
        memset(g_usart_rx_buf, 0, USART_RX_BUF_SIZE); 
        HAL_UARTEx_ReceiveToIdle_DMA(huart, g_usart_rx_buf, USART_RX_BUF_SIZE);
        
        /* 5. 禁用半传输中断，只处理 IDLE 或传输完成中断，防止干扰 */
        __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);

        /* 6. 启动发送 */
        BSP_USART_Send_DMA(g_usart_tx_buf, Size);
    }
}

/**
 * @brief 串口错误回调
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        /* 发生错误时（如溢出），尝试恢复接收 */
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, g_usart_rx_buf, USART_RX_BUF_SIZE);
    }
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
    /* 
       防止与 DMA 发送冲突：
       在重定向 printf 时，必须先等待串口状态变为 READY。
       否则，如果此时 DMA 正在发送数据，HAL_UART_Transmit 会直接返回 HAL_BUSY，
       导致 printf 的字符被丢弃。
    */
    while (huart1.gState != HAL_UART_STATE_READY);

    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
