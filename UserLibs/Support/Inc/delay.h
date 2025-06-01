#ifndef DELAY_H
#define DELAY_H

#include "main.h"

/**
  * @file    delay.h
  * @brief   延时函数接口 | Delay function interfaces
  */

/**
  * @brief   初始化延时功能 | Initialize delay functions
  * @note    在使用 delay_us 或 delay_ms 前必须调用 | Must be called before using delay_us or delay_ms
  */
void delay_init(void);

/**
  * @brief   微秒级延时 | Delay in microseconds
  * @param   nus  需要延时的微秒数 | Number of microseconds to delay
  */
void delay_us(uint32_t nus);

/**
  * @brief   毫秒级延时 | Delay in milliseconds
  * @param   nms  需要延时的毫秒数 | Number of milliseconds to delay
  */
void delay_ms(uint32_t nms);

#endif /* DELAY_H */
