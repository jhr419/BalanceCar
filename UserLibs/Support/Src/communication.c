#include "communication.h"
#include "car.h"

extern Car car;  // 全局小车实例 | Global car instance

uint8_t tx_buffer[BUF_SIZE];       // 通用发送缓冲区 | General TX buffer
uint8_t rx_data_buffer2[BUF_SIZE]; // USART2 接收缓冲区 | USART2 RX buffer
uint8_t rx_data_buffer6[BUF_SIZE]; // USART6 接收缓冲区 | USART6 RX buffer

/**
  * @brief   发送消息（非阻塞中断模式） | Send message (non-blocking IT mode)
  * @param   huart  指定的 UART 句柄 | UART handle
  * @param   msg    待发送数据指针 | Pointer to message data
  */
void uart_SendMsg(UART_HandleTypeDef *huart, uint8_t *msg) {
    uint8_t len = sizeof(msg);  // 获取指针大小（此处示例） | Get size of pointer (example)
    HAL_UART_Transmit_IT(huart, msg, len);  // 通过中断发送 | Transmit via interrupt
}

/**
  * @brief   格式化并发送字符串 | Formatted string transmission
  * @param   huart  指定的 UART 句柄 | UART handle
  * @param   fmt    格式化字符串 | Format string
  * @param   ...    可变参数列表 | Variable arguments
  */
void uart_printf(UART_HandleTypeDef *huart, const char *fmt, ...) {
    static uint8_t tx_buf[256] = {0};  // 临时格式化缓冲区 | Temporary format buffer
    static va_list ap;
    static uint16_t len;

    va_start(ap, fmt);
    len = vsprintf((char *)tx_buf, fmt, ap);  // 格式化字符串 | Format string
    va_end(ap);

    HAL_UART_Transmit_IT(huart, tx_buf, len);  // 发送格式化数据 | Transmit formatted data
}

/**
  * @brief   UART 空闲中断回调处理 | UART idle interrupt callback
  * @param   huart  触发空闲中断的 UART 句柄 | UART handle triggering idle interrupt
  * @note    通过 DMA 模式重新启动接收 | Restart DMA reception
  */
void UART_IdleCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        HAL_UART_DMAStop(huart);  // 停止 DMA 接收 | Stop DMA reception

        uint16_t rx_len = huart->RxXferSize - huart->RxXferCount;  // 本次接收长度 | Received length this time
        memset(rx_data_buffer2, 0, BUF_SIZE);  // 清空缓冲区 | Clear buffer

        HAL_UART_Receive_DMA(&huart_pc, rx_data_buffer2, BUF_SIZE);  // 重启 DMA 接收 | Restart DMA reception
    }
    else if (huart->Instance == USART6) {
        HAL_UART_DMAStop(huart);  // 停止 DMA 接收 | Stop DMA reception

        uint16_t rx_len = huart->RxXferSize - huart->RxXferCount;  // 本次接收长度 | Received length this time

        if (!car.isObstacleDetected)  // 若无障碍，则更新命令 | If no obstacle, update command
            car.cmd = rx_data_buffer6[0];

        memset(rx_data_buffer6, 0, BUF_SIZE);  // 清空缓冲区 | Clear buffer

        HAL_UART_Receive_DMA(&huart_bt, rx_data_buffer6, BUF_SIZE);  // 重启 DMA 接收 | Restart DMA reception
    }
}

/**
  * @brief   USART2 中断服务程序 | USART2 IRQ handler
  * @note    检测 UART 空闲标志并调用回调 | Check UART IDLE flag and invoke callback
  */
void USART2_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart2);  // 调用 HAL 库处理 | Call HAL handler

    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE)) {  // 空闲中断 | Idle interrupt
        __HAL_UART_CLEAR_IDLEFLAG(&huart2);             // 清除空闲标志 | Clear idle flag
        UART_IdleCallback(&huart2);                     // 调用空闲回调 | Invoke idle callback
    }
}

/**
  * @brief   USART6 中断服务程序 | USART6 IRQ handler
  * @note    检测 UART 空闲标志并调用回调 | Check UART IDLE flag and invoke callback
  */
void USART6_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart6);  // 调用 HAL 库处理 | Call HAL handler

    if (__HAL_UART_GET_FLAG(&huart6, UART_FLAG_IDLE)) {  // 空闲中断 | Idle interrupt
        __HAL_UART_CLEAR_IDLEFLAG(&huart6);             // 清除空闲标志 | Clear idle flag
        UART_IdleCallback(&huart6);                     // 调用空闲回调 | Invoke idle callback
    }
}
