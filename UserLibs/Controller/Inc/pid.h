#ifndef PID2_H_
#define PID2_H_

#include "main.h"

int VerticalPidCalc(float Med, float Angle, float gyro_Y);

int VelocityPidCalc(int Target, int encoder_left, int encoder_right);

int Turn(int gyro_Z);

#endif
