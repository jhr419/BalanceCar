#include "exti_devices.h"
#include "tim.h"
#include "car.h"

#define MAX_PAGE 5

extern Car car;

// 按键状态标志
uint8_t K[4] = {0, 0, 0, 0};

// 系统状态变量
uint8_t alarm = 0;
uint8_t cnt = 0;

uint32_t current = 0;
uint32_t lastCapture = 0;
volatile uint32_t pulseWidth_us = 0;
float dis = 0;

// 触发超声波传感器测距
void HC_trig(void) {
  HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
  delay_us(50);  // 拉高50us
  HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
}

// 根据脉宽计算距离（单位：cm）
float calc_dis(void) {
  return (float)pulseWidth_us * 0.001f * 342.62f / 2.0f;
}

// 外部中断回调
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  switch (GPIO_Pin) {
    case BT_STATE_Pin:
      if (HAL_GPIO_ReadPin(BT_STATE_GPIO_Port, BT_STATE_Pin) == GPIO_PIN_SET) {
        car.isBluetoothConnected = TRUE;  // 蓝牙在线
      } else {
        car.isBluetoothConnected = FALSE;  // 蓝牙断开
        car.targetLinearSpeed = 0;
      }
      break;

    case EHCO_Pin:
      current = __HAL_TIM_GET_COUNTER(&htim10);

      if (HAL_GPIO_ReadPin(EHCO_GPIO_Port, EHCO_Pin) == GPIO_PIN_SET) {
        // 上升沿：记录起始时间
        lastCapture = current;
      } else {
        // 下降沿：计算脉宽
        pulseWidth_us = (current >= lastCapture) ?
                        (current - lastCapture) :
                        (65535 - lastCapture + current + 1);

        dis = calc_dis();

        if (dis < 800) {
          car.isObstacleDetected = TRUE;
          HAL_TIM_Base_Stop_IT(&htim11);
          __HAL_TIM_SET_AUTORELOAD(&htim11, 7999);
          HAL_TIM_Base_Start_IT(&htim11);
        }
        // else car.isBarrier = 0; // 待处理逻辑
      }
      break;

    case K1_Pin:  // 上一页
      if (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_SET) {
        K[0] = 1;
        cnt = (cnt == 0) ? 0 : (cnt - 1);
      } else {
        K[0] = 0;
        OLED_Clear();
        OLED_Update();
      }
      break;

    case K2_Pin:  // 下一页
      if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_SET) {
        K[1] = 1;
        cnt = (cnt == MAX_PAGE) ? MAX_PAGE : (cnt + 1);
      } else {
        K[1] = 0;
        OLED_Clear();
        OLED_Update();
      }
      break;

    case K3_Pin:  // 报警控制开关
      if (HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin) == GPIO_PIN_SET) {
        K[2] = 1;
      } else if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_RESET) {  // 注意此处是否应为 K3_GPIO_Port
        car.isBrake = (car.isBrake == 0) ? 1 : 0;
        K[2] = 0;
      }
      break;

    case K4_Pin:  // 单位/目标值重置
      if (HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin) == GPIO_PIN_SET) {
        K[3] = 1;
        car.targetStartLinearSpeed = 8;
      } else {
        K[3] = 0;
      }
      break;

    default:
      break;
  }
}
