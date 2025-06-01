#ifndef EXTI_DEVICES_H_
#define EXTI_DEVICES_H_

#include "main.h"
#include "delay.h"

/**
  * @file    exti_devices.h
  * @brief   外部设备接口声明 | External device interface declarations
  *
  * @note    包含超声波触发和距离计算函数原型 | Contains prototypes for ultrasonic trigger and distance calculation
  */

/**
  * @brief   触发超声波传感器测距 | Trigger ultrasonic sensor for distance measurement
  * @note    拉高 TRIG 引脚 50µs 后拉低以发出超声波脉冲 | Set TRIG pin high for 50µs then low to emit ultrasonic pulse
  */
void HC_trig(void);

/**
  * @brief   根据脉宽计算距离（单位：cm） | Calculate distance (cm) from pulse width
  * @return  返回计算得到的距离值 | Returns calculated distance value
  */
float calc_dis(void);

#endif /* EXTI_DEVICES_H_ */
