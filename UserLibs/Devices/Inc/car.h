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

// 定义左/右电机和编码器相关的硬件配置（定时器、GPIO端口与引脚）
// Define hardware configuration for left/right motors and encoders
#define MOTOR_TIM        htim2
#define MOTOR_L_CHANNEL  TIM_CHANNEL_1
#define MOTOR_L_IN1_PORT  DIN1_GPIO_Port
#define MOTOR_L_IN1_PIN  DIN1_Pin
#define MOTOR_L_IN2_PORT  DIN2_GPIO_Port
#define MOTOR_L_IN2_PIN  DIN2_Pin

#define MOTOR_R_CHANNEL  TIM_CHANNEL_2
#define MOTOR_R_IN1_PORT  AIN1_GPIO_Port
#define MOTOR_R_IN1_PIN  AIN1_Pin
#define MOTOR_R_IN2_PORT  AIN2_GPIO_Port
#define MOTOR_R_IN2_PIN  AIN2_Pin

#define ENCODER_L_TIM htim3
#define ENCODER_R_TIM htim1

#define MECHANICAL_BALANCE_BIAS (-3.4f)

typedef enum {
    CAR_MOTION_STOP=0,
    CAR_MOTION_FOWARD,
    CAR_MOTION_BACKWARD,
    CAR_MOTION_LEFT,
    CAR_MOTION_RIGHT
} MotionState;


typedef struct Car Car;

struct Car {
    //状态变量
    bool_t isObstacleAvoidanceOn;
    bool_t isObstacleDetected;
    bool_t isBluetoothConnected;
    bool_t isBrake;

    uint8_t motionState;
    int8_t targetLinearSpeed;
    int16_t targetAngularSpeed;
    int8_t targetStartLinearSpeed;

    fp32 balanceBias;
    uint8_t cmd;

    //设备变量
    Motor motor_l;
    Motor motor_r;
    Encoder encoder_l;
    Encoder encoder_r;
    Imu imu;

    //成员函数
    void (*CarMove)(Car *self, int8_t setSpeed);
};

Car newCar(void);

void CarMove(Car *self, int8_t setSpeed);

#endif
