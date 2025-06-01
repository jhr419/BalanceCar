#include "encoder.h"

// 创建一个新的编码器实例，初始化计数器和通道信息
// Create a new encoder instance and initialize counter and channel info
Encoder newEncoder(TIM_HandleTypeDef *htim, uint32_t Channel) {
  Encoder e;
  e.htim = htim;           // 关联定时器句柄
  e.Channel = Channel;     // 设置通道
  e.count = 0;             // 初始化当前计数值
  e.last_count = 0;        // 初始化上一次计数值

  e.GetCountAndRpm = GetCountAndRpm;  // 绑定获取计数函数指针

  // 启动编码器接口（包含通道A和B）
  // Start the encoder interface (both channel A and B)
  HAL_TIM_Encoder_Start(htim, Channel);

  return e; // 返回初始化后的编码器结构体
}

uint16_t GetCountAndRpm(Encoder *self) {
  self->last_count = self->count;

  static uint16_t cnt = 0;

  cnt = (uint16_t) __HAL_TIM_GET_COUNTER(self->htim);

  __HAL_TIM_SetCounter(self->htim, 0);

  self->rpm = (float) ((cnt > 30000) ? (cnt - 65536) : cnt);

  return self->count;
}
