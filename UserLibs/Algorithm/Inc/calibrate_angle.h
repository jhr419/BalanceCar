#ifndef _CALIBRATE_ANGLE_H_
#define _CALIBRATE_ANGLE_H_

#include "main.h"

/**
  * @file    calibrate_angle.h
  * @brief   平衡目标角度校准接口 | Interface for balancing target angle update
  */

/**
  * @brief   根据左右轮速度更新平衡目标角度 | Update balance target angle from wheel speeds
  * @param   speed_l 左轮速度 | Left wheel speed
  * @param   speed_r 右轮速度 | Right wheel speed
  * @return  更新后的目标角度 | Updated target angle
  */
float update_balance_target(float speed_l, float speed_r);

#endif /* _CALIBRATE_ANGLE_H_ */
