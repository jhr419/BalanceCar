#include "pid.h"

#define V_Kp (-0.6f)

float
        Vertical_Kp = 5000.0f * 0.6,
        Vertical_Kd = 1000.0f * 0.6;
float
        Velocity_Kp = V_Kp,
        Velocity_Ki = V_Kp / 200.0f;   // 速度环Kp、Ki（正反馈）
float
        Turn_Kp = -1.0f;

int VerticalPidCalc(float Med, float Angle, float gyro) {
  int PWM_out;

  PWM_out = Vertical_Kp * (Angle - Med) + Vertical_Kd * (gyro);

  return PWM_out;
}

int VelocityPidCalc(int Target, int encoder_left, int encoder_right) {
  // 定义成静态变量，保存在静态存储器，使得变量不丢掉
  static int PWM_out, Encoder_Err, Encoder_S, EnC_Err_Lowout, EnC_Err_Lowout_last;
  float a = 0.7;

  Encoder_Err = ((encoder_left + encoder_right) / 2.0f - Target);

  EnC_Err_Lowout = (1 - a) * Encoder_Err + a * EnC_Err_Lowout_last; // 使得波形更加平滑，滤除高频干扰，放置速度突变
  EnC_Err_Lowout_last = EnC_Err_Lowout;   // 防止速度过大影响直立环的正常工作

  Encoder_S += EnC_Err_Lowout;

  Encoder_S = Encoder_S > 15000 ? 15000 : (Encoder_S < (-15000) ? (-15000) : Encoder_S);

  PWM_out = Velocity_Kp * EnC_Err_Lowout + Velocity_Ki * Encoder_S;

  return PWM_out;
}

int Turn(int gyro_Z) {
  int PWM_out;

  PWM_out = (int) Turn_Kp * gyro_Z;

  return PWM_out;
}