#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "main.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/* UART 句柄映射 | UART handle mappings */
#define huart_pc        huart2    /**< 上位机通信 UART | UART for PC communication */
#define huart_bt        huart6    /**< 蓝牙模块通信 UART | UART for Bluetooth module */

/* 缓冲区大小 | Buffer size */
#define BUF_SIZE        64        /**< 串口收发缓冲区长度 | UART RX/TX buffer length */

/* 控制命令宏定义 | Command macros */
#define CMD_LEFT            0xC1  /**< 左转命令 | Turn left command */
#define CMD_RIGHT           0xC2  /**< 右转命令 | Turn right command */
#define CMD_FORWARD         0xC3  /**< 前进命令 | Move forward command */
#define CMD_BACKWARD        0xC4  /**< 后退命令 | Move backward command */
#define CMD_STOP            0xC5  /**< 停止命令 | Stop command */

#define CMD_STOP_SLOWLY     0xC6  /**< 缓慢停止命令 | Stop slowly command */
#define CMD_SPEED_UP        0xC7  /**< 加速命令 | Speed up command */
#define CMD_SPEED_DOWN      0xC8  /**< 减速命令 | Slow down command */

#define CMD_ROAD_PLANNING   0xC9  /**< 路径规划模式切换命令 | Toggle road planning mode */

#define CMD_TURN_AROUND     0xCA  /**< 原地掉头命令 | Turn around in place command */
#define CMD_TURN_CLEAR      0xCB  /**< 清除转向命令 | Clear turning command */

#define CMD_POWER_SWITCH    0xCC  /**< 电源开关命令 | Power switch command */
#define CMD_SPEED_CONSTANT  0xCD  /**< 固定速度模式命令 | Constant speed mode command */

/**
  * @brief   格式化串口打印 | Formatted UART print
  * @param   huart  指定的 UART 句柄 | UART handle to use
  * @param   fmt    格式化字符串（类似 printf） | Format string (like printf)
  * @param   ...    可选参数列表 | Variable argument list
  * @return  无 | None
  *
  * @note    通过 HAL_UART_Transmit 实现可变参数格式输出 | Uses HAL_UART_Transmit to send formatted data
  */
void uart_printf(UART_HandleTypeDef *huart, const char *fmt, ...);

#endif /* COMMUNICATION_H_ */
