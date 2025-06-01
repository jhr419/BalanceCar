#ifndef PID2_H_
#define PID2_H_

#include "main.h"

/**
  * @brief   计算垂直方向 PID 输出 | Compute vertical PID output
  * @param   Med      期望值 | Desired value
  * @param   Angle    当前倾角 | Current tilt angle
  * @param   gyro_Y   陀螺仪 Y 轴角速度 | Gyro Y-axis rate
  * @return  PID 控制信号 | PID control signal
  */
int VerticalPidCalc(float Med, float Angle, float gyro_Y);

/**
  * @brief   计算速度 PID 输出 | Compute velocity PID output
  * @param   Target        期望速度 | Target speed
  * @param   encoder_left  左编码器计数 | Left encoder count
  * @param   encoder_right 右编码器计数 | Right encoder count
  * @return  差速控制信号 | Differential speed control signal
  */
int VelocityPidCalc(int Target, int encoder_left, int encoder_right);

/**
  * @brief   计算转向控制信号 | Compute turn control signal
  * @param   gyro_Z  陀螺仪 Z 轴角速度 | Gyro Z-axis rate
  * @return  转向调整值 | Turn adjustment value
  */
int Turn(int gyro_Z);

#endif /* PID2_H_ */
