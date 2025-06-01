#ifndef FILTER_H
#define FILTER_H

#include "main.h"

#define FILTER_WINDOW_SIZE 16  /**< 滤波窗口长度，建议取值 8–16
                                  Filter window length; recommend 8–16 */

/**
  * @file    filter.h
  * @brief   电机电压滑动平均滤波接口 | Motor voltage moving-average filter interface
  */

/**
  * @struct  MotorVoltageFilter
  * @brief   电机电压滤波器结构 | Filter for motor voltage readings
  */
typedef struct {
    int16_t buffer[FILTER_WINDOW_SIZE];  /**< 环形缓冲区 | Circular buffer */
    uint8_t index;                       /**< 缓冲区索引 | Buffer index */
    int16_t filtered_value;              /**< 滤波后值 | Filtered output */
} MotorVoltageFilter;

/**
  * @brief   初始化滤波器实例 | Initialize filter instance
  * @param   filter          滤波器结构指针 | Pointer to filter struct
  * @param   initial_voltage 初始填充值 | Initial fill voltage
  * @return  无 | None
  */
void Filter_Init(MotorVoltageFilter *filter, int16_t initial_voltage);

/**
  * @brief   处理一次原始电压并返回滤波值 | Process raw voltage and return filtered value
  * @param   filter      滤波器结构指针 | Pointer to filter struct
  * @param   raw_voltage 原始电压值 | Raw voltage sample
  * @return  滤波后电压值 | Filtered voltage
  */
int16_t Filter_Process(MotorVoltageFilter *filter, int16_t raw_voltage);

#endif /* FILTER_H */
