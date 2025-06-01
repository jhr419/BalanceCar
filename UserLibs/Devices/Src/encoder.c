#include "encoder.h"

/**
  * @brief   创建并初始化编码器实例 | Create and initialize an encoder instance
  * @param   htim      定时器句柄 | Timer handle
  * @param   Channel   编码器通道 | Encoder channel
  * @return  返回初始化后的 Encoder 结构 | Returns the initialized Encoder struct
  */
Encoder newEncoder(TIM_HandleTypeDef *htim, uint32_t Channel) {
    Encoder e;
    e.htim = htim;            // 关联定时器 | Associate timer
    e.Channel = Channel;      // 设置通道 | Set channel
    e.count = 0;              // 初始化计数 | Initialize count
    e.last_count = 0;         // 初始化上次计数 | Initialize last count

    e.GetCountAndRpm = GetCountAndRpm;  // 绑定函数指针 | Bind function pointer

    HAL_TIM_Encoder_Start(htim, Channel);  // 启动编码器接口 | Start encoder interface

    return e;  // 返回实例 | Return instance
}

/**
  * @brief   获取当前计数并计算 RPM | Get current count and compute RPM
  * @param   self  指向 Encoder 实例的指针 | Pointer to Encoder instance
  * @return  返回上次记录的计数值 | Returns the last recorded count value
  */
uint16_t GetCountAndRpm(Encoder *self) {
    self->last_count = self->count;  // 更新上次计数 | Update last count

    static uint16_t cnt = 0;
    cnt = (uint16_t)__HAL_TIM_GET_COUNTER(self->htim);  // 读取当前计数 | Read current counter

    __HAL_TIM_SetCounter(self->htim, 0);  // 计数器清零 | Reset counter

    // 计算 RPM（考虑计数回绕） | Compute RPM (handle wrap-around)
    self->rpm = (float)((cnt > 30000) ? (cnt - 65536) : cnt);

    return self->count;  // 返回之前的 count（若有其它逻辑可改） | Return previous count
}
