#ifndef CAR_H_
#define CAR_H_

#include "main.h"
#include "motor.h"
#include "encoder.h"
#include "imu.h"
#include "oled.h"
#include "pid.h"
#include "filter.h"
#include "struct_typedef.h"

/* 硬件配置宏定义 | Hardware configuration macros */
// 左电机 PWM 定时器 | Motor PWM timer
#define MOTOR_L_TIM        htim4
// 左电机 IN1 通道 | Left motor IN1 channel
#define MOTOR_L_IN1_CHANNEL  TIM_CHANNEL_1
// 左电机 IN2 通道 | Left motor IN2 channel
#define MOTOR_L_IN2_CHANNEL  TIM_CHANNEL_2

// 右电机 PWM 定时器 | Motor PWM timer
#define MOTOR_R_TIM        htim2
// 右电机 IN1 通道 | Left motor IN1 channel
#define MOTOR_R_IN1_CHANNEL  TIM_CHANNEL_1
// 右电机 IN2 通道 | Left motor IN2 channel
#define MOTOR_R_IN2_CHANNEL  TIM_CHANNEL_2

// 左编码器定时器 | Left encoder timer
#define ENCODER_L_TIM htim3
// 右编码器定时器 | Right encoder timer
#define ENCODER_R_TIM htim1

// 机械平衡偏置值（单位：度） | Mechanical balance bias (degrees)
#define MECHANICAL_BALANCE_BIAS (-3.4f)

/**
  * @brief   小车运动状态枚举 | Car motion state enumeration
  */
typedef enum {
    CAR_MOTION_STOP = 0,     /**< 停止 | Stop */
    CAR_MOTION_FOWARD,       /**< 前进 | Forward */
    CAR_MOTION_BACKWARD,     /**< 后退 | Backward */
    CAR_MOTION_LEFT,         /**< 左转 | Left turn */
    CAR_MOTION_RIGHT         /**< 右转 | Right turn */
} MotionState;

typedef struct Car Car;

/**
  * @struct  Car
  * @brief   小车对象结构体 | Car object structure
  *
  * @note    包含状态标志、目标速度、传感器和驱动设备实例等信息
  *          Contains status flags, target speeds, sensor and actuator instances
  */
struct Car {
    /* 状态标志 | Status flags */
    bool_t isObstacleAvoidanceOn;   /**< 障碍规避开启 | Obstacle avoidance enabled */
    bool_t isObstacleDetected;      /**< 障碍检测到 | Obstacle detected */
    bool_t isBluetoothConnected;    /**< 蓝牙连接状态 | Bluetooth connection status */
    bool_t isBrake;                 /**< 刹车标志 | Brake flag */

    /* 运动参数 | Motion parameters */
    uint8_t motionState;            /**< 当前运动状态 | Current motion state */
    int8_t targetLinearSpeed;       /**< 目标线速度 (cm/s) | Target linear speed */
    int16_t targetAngularSpeed;     /**< 目标角速度 (°/s) | Target angular speed */
    int8_t targetStartLinearSpeed;  /**< 起始线速度 (cm/s) | Initial start speed */

    fp32 balanceBias;               /**< 平衡偏置 (°) | Balance bias */
    uint8_t cmd;                    /**< 当前命令 | Current command */

    /* 设备实例 | Device instances */
    Motor   motor_l;                /**< 左电机实例 | Left motor instance */
    Motor   motor_r;                /**< 右电机实例 | Right motor instance */
    Encoder encoder_l;              /**< 左编码器实例 | Left encoder instance */
    Encoder encoder_r;              /**< 右编码器实例 | Right encoder instance */
    Imu     imu;                    /**< IMU 传感器实例 | IMU sensor instance */

    /* 方法指针 | Method pointer */
    void (*CarMove)(Car *self, int8_t setSpeed);
    /**< 小车移动函数指针 | Pointer to car movement function */
};

/**
  * @brief   创建并初始化小车实例 | Create and initialize a Car instance
  * @return  返回初始化后的 Car 结构 | Returns the initialized Car struct
  */
Car newCar(void);

/**
  * @brief   小车移动控制函数 | Car movement control function
  * @param   self      指向 Car 实例的指针 | Pointer to Car instance
  * @param   setSpeed  未使用参数，可保留 | Unused parameter (can be retained)
  * @note    调用 PID、判断刹车并设置电机输出 | Run PID, check brake, set motor outputs
  */
void CarMove(Car *self, int8_t setSpeed);

#endif /* CAR_H_ */
