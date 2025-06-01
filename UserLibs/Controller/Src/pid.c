#include "pid.h"

#define V_Kp (-0.6f)  // 速度环比例系数 | Velocity loop Kp

// 垂直环参数 | Vertical loop parameters
float
    Vertical_Kp = 5000.0f * 0.6f,  // 垂直环 Kp | Vertical Kp
    Vertical_Kd = 1000.0f * 0.6f; // 垂直环 Kd | Vertical Kd

// 速度环参数 | Velocity loop parameters
float
    Velocity_Kp = V_Kp,            // 速度环 Kp | Velocity Kp
    Velocity_Ki = V_Kp / 200.0f;   // 速度环 Ki | Velocity Ki

// 转向环参数 | Turn loop parameter
float
    Turn_Kp = -1.0f;               // 转向环 Kp | Turn Kp

/**
  * @brief   垂直 PID 计算 | Vertical PID calculation
  * @param   Med   平衡目标角度 | Balance target angle
  * @param   Angle 当前倾角 | Current tilt angle
  * @param   gyro  陀螺 Y 轴角速度 | Gyro Y-axis rate
  * @return  返回 PWM 输出 | Returns PWM output
  */
int VerticalPidCalc(float Med, float Angle, float gyro) {
    // 误差比例 + 微分 | P error plus D term
    int PWM_out = Vertical_Kp * (Angle - Med) + Vertical_Kd * gyro;
    return PWM_out;
}

/**
  * @brief   速度 PID 计算 | Velocity PID calculation
  * @param   Target         目标速度 | Target speed
  * @param   encoder_left   左编码器计数 | Left encoder count
  * @param   encoder_right  右编码器计数 | Right encoder count
  * @return  返回 PWM 输出 | Returns PWM output
  */
int VelocityPidCalc(int Target, int encoder_left, int encoder_right) {
    // 静态变量保持状态 | Static variables to preserve state
    static int PWM_out, Encoder_Err, Encoder_Sum, Err_Low, Err_Low_last;
    float alpha = 0.7f;  // 滤波系数 | Filter coefficient

    // 计算平均误差 | Calculate average error
    Encoder_Err = ((encoder_left + encoder_right) / 2.0f - Target);

    // 低通滤波 | Low-pass filter
    Err_Low = (1 - alpha) * Encoder_Err + alpha * Err_Low_last;
    Err_Low_last = Err_Low;  // 更新上次滤波值 | Update previous filtered error

    // 误差累积 | Accumulate error
    Encoder_Sum += Err_Low;

    // 限制累积和范围防止积分饱和 | Limit accumulator to prevent windup
    if (Encoder_Sum > 15000) Encoder_Sum = 15000;
    if (Encoder_Sum < -15000) Encoder_Sum = -15000;

    // PI 控制 | PI control
    PWM_out = Velocity_Kp * Err_Low + Velocity_Ki * Encoder_Sum;
    return PWM_out;
}

/**
  * @brief   转向计算 | Turn calculation
  * @param   gyro_Z  陀螺 Z 轴角速度 | Gyro Z-axis rate
  * @return  返回 PWM 输出 | Returns PWM output
  */
int Turn(int gyro_Z) {
    // 线性比例 | Proportional control
    int PWM_out = (int)(Turn_Kp * gyro_Z);
    return PWM_out;
}
