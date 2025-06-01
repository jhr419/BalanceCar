#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "main.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define huart_pc huart2
#define huart_bt huart6
#define BUF_SIZE 64

#define CMD_LEFT     0xC1
#define CMD_RIGHT    0xC2
#define CMD_FORWARD  0xC3
#define CMD_BACKWARD 0xC4
#define CMD_STOP     0xC5

#define CMD_STOP_SLOWLY 0xC6
#define CMD_SPEED_UP 0xC7
#define CMD_SPEED_DOWN 0xC8

#define CMD_ROAD_PLANNING 0xC9

#define CMD_TURN_AROUND 0xCA
#define CMD_TURN_CLEAR 0xCB

#define CMD_POWER_SWITCH 0xCC
#define CMD_SPEED_CONSTANT 0xCD

void uart_printf(UART_HandleTypeDef *huart, const char *fmt, ...);

#endif
