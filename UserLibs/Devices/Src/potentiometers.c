#include "potentiometers.h"
#include "car.h"
#include "communication.h"

#define NUM_CHANNELS 3  // ADC通道数量 | Number of ADC channels

extern Car car;

uint32_t ADC_value[NUM_CHANNELS];  // ADC采样值缓存 | ADC sample buffer
uint32_t GetADC;                   // 读取的ADC值 | Converted ADC value

/**
  * @brief   启动ADC DMA连续转换 | Start ADC DMA continuous conversion
  */
void ADC_Start(void) {
    HAL_ADC_Start_DMA(&hadc1,                  // ADC1外设句柄 | ADC1 handle
                      (uint32_t*)ADC_value,   // 数据缓存 | Data buffer
                      NUM_CHANNELS);          // 通道数量 | Number of channels
}

/**
  * @brief   ADC DMA转换完成回调 | ADC DMA conversion complete callback
  * @param   hadc  ADC句柄 | ADC handle
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    // 计算阈值：通道0值除20，并限幅在0~40 | Compute threshold: channel 0 /20, limit 0–40
    GetADC = (uint32_t)(ADC_value[0] / 20);
    GetADC = LIMIT(GetADC, 0, 40);
    car.targetStartLinearSpeed = (int8_t)GetADC;  // 更新小车起始速度 | Update car start speed

    // 重新启动ADC DMA转换 | Restart ADC DMA conversion
    HAL_ADC_Start_DMA(&hadc1,
                      (uint32_t*)ADC_value,
                      NUM_CHANNELS);
}
