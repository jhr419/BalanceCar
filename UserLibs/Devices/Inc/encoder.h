#ifndef ENCODER_H_
#define ENCODER_H_

#include "main.h"
#include "tim.h"

/**
  * @file    encoder.h
  * @brief   编码器接口定义 | Encoder interface definitions
  */

/**
  * @struct  Encoder
  * @brief   编码器结构体 | Encoder struct
  *
  * @note    保存定时器句柄、通道、计数和 RPM 信息 | Holds timer handle, channel, count, and RPM info
  */
typedef struct Encoder Encoder;

typedef struct Encoder {
    TIM_HandleTypeDef *htim;     /**< 定时器句柄 | Timer handle */
    uint32_t Channel;            /**< 编码器通道 | Encoder channel */
    uint16_t count;              /**< 当前计数 | Current count */
    uint16_t last_count;         /**< 上一次计数 | Last count */
    float rpm;                   /**< 计算出的 RPM | Calculated RPM */
    uint16_t (*GetCountAndRpm)(Encoder *self);  /**< 函数指针：获取计数和 RPM | Function pointer: get count and RPM */
} Encoder;

/**
  * @brief   创建并初始化编码器实例 | Create and initialize an encoder instance
  * @param   htim     定时器句柄 | Timer handle
  * @param   Channel  编码器通道 | Encoder channel
  * @return  返回初始化后的 Encoder 对象 | Returns initialized Encoder object
  */
Encoder newEncoder(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
  * @brief   获取当前计数并更新 RPM | Get current count and update RPM
  * @param   self  指向 Encoder 实例的指针 | Pointer to Encoder instance
  * @return  返回上一次记录的计数值 | Returns the last recorded count value
  */
uint16_t GetCountAndRpm(Encoder *self);

/**
  * @brief   获取当前 RPM | Get current RPM
  * @param   self  指向 Encoder 实例的指针 | Pointer to Encoder instance
  * @return  返回计算后的 RPM 值 | Returns calculated RPM value
  */
int16_t GetRPM(Encoder *self);

#endif /* ENCODER_H_ */
