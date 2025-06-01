#include "exti_devices.h"
#include "tim.h"
#include "car.h"

#define MAX_PAGE 5

extern Car car;  // 全局小车实例 | Global car instance

// 按键状态标志 | Key state flags
uint8_t K[4] = {0, 0, 0, 0};

// 系统状态变量 | System state variables
uint8_t alarm = 0;
uint8_t cnt = 0;

// 超声波测距相关变量 | Ultrasonic measurement variables
uint32_t current = 0;
uint32_t lastCapture = 0;
volatile uint32_t pulseWidth_us = 0;
float dis = 0;

/**
  * @brief   触发超声波传感器测距 | Trigger ultrasonic sensor for distance measurement
  */
void HC_trig(void) {
    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);  // 拉高 TRIG 引脚 | Set TRIG high
    delay_us(50);                                               // 保持 50us | Hold 50µs
    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET); // 拉低 TRIG 引脚 | Set TRIG low
}

/**
  * @brief   根据脉宽计算距离（单位：cm） | Calculate distance (cm) from pulse width
  * @return  返回计算后的距离 | Returns calculated distance
  */
float calc_dis(void) {
    return (float)pulseWidth_us * 0.001f * 342.62f / 2.0f;  // 声速 342.62 m/s, 取半程 | Speed of sound 342.62 m/s, divide by 2
}

/**
  * @brief   外部中断回调 | External interrupt callback
  * @param   GPIO_Pin  触发中断的引脚号 | Pin number causing the interrupt
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    switch (GPIO_Pin) {
        case BT_STATE_Pin:
            if (HAL_GPIO_ReadPin(BT_STATE_GPIO_Port, BT_STATE_Pin) == GPIO_PIN_SET) {
                car.isBluetoothConnected = TRUE;   // 蓝牙已连接 | Bluetooth connected
            } else {
                car.isBluetoothConnected = FALSE;  // 蓝牙断开 | Bluetooth disconnected
                car.targetLinearSpeed = 0;         // 停止前进 | Stop movement
            }
            break;

        case EHCO_Pin:
            current = __HAL_TIM_GET_COUNTER(&htim10);  // 读取计时器计数 | Read timer counter
            if (HAL_GPIO_ReadPin(EHCO_GPIO_Port, EHCO_Pin) == GPIO_PIN_SET) {
                lastCapture = current;  // 上升沿：记录起始时间 | Rising edge: record start time
            } else {
                // 下降沿：计算脉宽，处理计数回绕 | Falling edge: calculate pulse width, handle overflow
                pulseWidth_us = (current >= lastCapture) ?
                                (current - lastCapture) :
                                (65535 - lastCapture + current + 1);
                dis = calc_dis();  // 计算距离 | Compute distance

                if (dis < 800) {  // 距离小于 800cm 认为有障碍 | If distance < 800cm → obstacle
                    car.isObstacleDetected = TRUE;  // 标记障碍检测 | Mark obstacle detected
                    HAL_TIM_Base_Stop_IT(&htim11); // 停止定时器 | Stop timer
                    __HAL_TIM_SET_AUTORELOAD(&htim11, 7999);
                    HAL_TIM_Base_Start_IT(&htim11); // 重启定时器 | Restart timer
                }
                // else 可添加无障碍逻辑 | else handle no obstacle
            }
            break;

        case K1_Pin:  // 上一页 | Previous page
            if (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_SET) {
                K[0] = 1;  // 按下标志 | Pressed flag
                cnt = (cnt == 0) ? 0 : (cnt - 1);  // 页码减 1（下限 0） | Decrement page, min 0
            } else {
                K[0] = 0;        // 释放标志 | Release flag
                OLED_Clear();    // 清屏 | Clear display
                OLED_Update();   // 更新屏幕 | Update display
            }
            break;

        case K2_Pin:  // 下一页 | Next page
            if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_SET) {
                K[1] = 1;  // 按下标志 | Pressed flag
                cnt = (cnt == MAX_PAGE) ? MAX_PAGE : (cnt + 1);  // 页码加 1（上限 MAX_PAGE） | Increment page, max MAX_PAGE
            } else {
                K[1] = 0;        // 释放标志 | Release flag
                OLED_Clear();    // 清屏 | Clear display
                OLED_Update();   // 更新屏幕 | Update display
            }
            break;

        case K3_Pin:  // 报警控制开关 | Alarm control toggle
            if (HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin) == GPIO_PIN_SET) {
                K[2] = 1;  // 按下标志 | Pressed flag
            } else if (HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin) == GPIO_PIN_RESET) {
                car.isBrake = (car.isBrake == 0) ? 1 : 0;  // 切换刹车 | Toggle brake
                K[2] = 0;  // 释放标志 | Release flag
            }
            break;

        case K4_Pin:  // 单位/目标值重置 | Unit/target reset
            if (HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin) == GPIO_PIN_SET) {
                K[3] = 1;                   // 按下标志 | Pressed flag
                car.targetStartLinearSpeed = 8;  // 重置起始速度 | Reset start speed
            } else {
                K[3] = 0;  // 释放标志 | Release flag
            }
            break;

        default:
            break;
    }
}
