#include "motor.h"

/**
  * @brief   创建并初始化电机实例 | Create and initialize motor instance
  * @param   Init  电机初始化参数 | Motor initialization parameters
  * @return  返回 Motor 结构体 | Returns Motor struct
  */
Motor newMotor(Motor_InitTypeDef Init) {
    Motor m;
    m.Init = Init;                   // 保存初始化配置 | store Init config
    m.direction = FORWARD;           // 初始方向前进 | default direction FORWARD
    m.setRPM = MOTOR_MIN_RPM;        // 初始转速最小 | default RPM = MOTOR_MIN_RPM
    m.Move = Move;                   // 绑定 Move 函数 | bind Move function

    HAL_TIM_PWM_Start(Init.htim, Init.Channel);  // 启动 PWM | start PWM on channel

    return m;                        // 返回实例 | return instance
}

/**
  * @brief   控制电机动作 | Control motor action
  * @param   self    指向 Motor 实例 | Pointer to Motor instance
  * @param   isBrake 是否刹车 | Brake flag
  * @param   setRPM  目标 RPM，可正可负 | Target RPM (positive/negative)
  */
void Move(Motor *self, uint8_t isBrake, int32_t setRPM) {
    if (isBrake) {
        // 刹车：IN1、IN2 都高 | Brake: IN1/IN2 high
        HAL_GPIO_WritePin(self->Init.IN1_GPIOx, self->Init.IN1_GPIO_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(self->Init.IN2_GPIOx, self->Init.IN2_GPIO_Pin, GPIO_PIN_SET);
        self->direction = BRAKE;     // 方向设为刹车 | set direction BRAKE
    } else {
        if (setRPM > 0) {
            // 正转：IN1 高、IN2 低 | Forward: IN1 high, IN2 low
            HAL_GPIO_WritePin(self->Init.IN1_GPIOx, self->Init.IN1_GPIO_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(self->Init.IN2_GPIOx, self->Init.IN2_GPIO_Pin, GPIO_PIN_RESET);
            self->direction = FORWARD; // 设置方向前进 | set direction FORWARD
        } else if (setRPM < 0) {
            // 反转：IN1 低、IN2 高 | Reverse: IN1 low, IN2 high
            HAL_GPIO_WritePin(self->Init.IN1_GPIOx, self->Init.IN1_GPIO_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(self->Init.IN2_GPIOx, self->Init.IN2_GPIO_Pin, GPIO_PIN_SET);
            self->direction = BACKWARD; // 设置方向后退 | set direction BACKWARD
        } else {
            // 停止：IN1、IN2 都低 | Stop: IN1/IN2 low
            HAL_GPIO_WritePin(self->Init.IN1_GPIOx, self->Init.IN1_GPIO_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(self->Init.IN2_GPIOx, self->Init.IN2_GPIO_Pin, GPIO_PIN_RESET);
        }
    }

    self->setRPM = (float)setRPM;    // 更新目标转速 | update target RPM

    __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel, abs(setRPM));
    // 设置 PWM 占空比 | set PWM duty = |RPM|
}
