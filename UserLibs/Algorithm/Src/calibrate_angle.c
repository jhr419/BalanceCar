#include "calibrate_angle.h"
#include "car.h"

// ==== 全局变量示例 ====
// angle_target: 自学习后目标角度（初始为机械平衡偏置） | Learned target angle (initialized to mechanical balance bias)
// learning_rate: 学习率，数值越小调整越慢 | Learning rate; smaller value → slower adjustment
// speed_filter: 一阶滤波后速度 | First-order filtered speed
// speed_alpha: 滤波系数（越接近1越平滑） | Filter coefficient (closer to 1 → smoother)
float angle_target = MECHANICAL_BALANCE_BIAS;
float learning_rate = 0.00001f;
float speed_filter = 0.0f;
float speed_alpha = 0.98f;

/**
  * @brief   更新平衡目标角度 | Update balance target angle
  * @param   speed_l 左轮速度 | Left wheel speed
  * @param   speed_r 右轮速度 | Right wheel speed
  * @return  更新后的目标角度 | Updated target angle
  */
float update_balance_target(float speed_l, float speed_r) {
    // 步骤1：计算车体整体速度（左右轮平均） | Step 1: compute chassis speed (average of both wheels)
    float current_speed = (speed_l + speed_r) / 2.0f;

    // 步骤2：滑动平均滤波处理速度，抑制波动 | Step 2: apply first-order filter to suppress noise
    speed_filter = speed_alpha * speed_filter + (1.0f - speed_alpha) * current_speed;

    // 步骤3：根据速度趋势微调目标角度 | Step 3: adjust target angle based on speed trend
    // 速度向前（正值）时，减少目标角度（向后倾斜） | If moving forward (positive), decrease angle (lean backward)
    angle_target -= learning_rate * speed_filter;

    // 步骤4（可选）：限制角度范围，防止过度偏移 | Step 4 (optional): limit angle to prevent excessive offset
    if (angle_target > 5.0f) angle_target = 5.0f;    // 最大 5 度 | Max ±5°
    if (angle_target < -5.0f) angle_target = -5.0f;  // 最小 -5 度 | Min ±5°

    return angle_target;  // 返回新目标角度 | Return new target angle
}
