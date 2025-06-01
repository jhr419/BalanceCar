#ifndef POTENTIOMETERS_H
#define POTENTIOMETERS_H

#include "main.h"
#include "adc.h"
#include <stdio.h>

/**
  * @file    potentiometers.h
  * @brief   电位器 ADC 采样接口 | ADC sampling interface for potentiometers
  */

/**
  * @brief   启动 ADC1 DMA 连续转换 | Start ADC1 DMA continuous conversion
  */
void ADC_Start(void);

#endif /* POTENTIOMETERS_H */
