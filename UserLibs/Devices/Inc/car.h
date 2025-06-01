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

// ������/�ҵ���ͱ�������ص�Ӳ�����ã���ʱ����GPIO�˿������ţ�
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

// ����ƽ��Ƕ� PID ���ٶ� PID �Ĳ���
// Define PID parameters for angle and velocity control
#define PID_A_P 3000.0f//2800.0f
#define PID_A_I  0.0f
#define PID_A_D  0.0f //1200.0f

#define PID_L_P  2800.0f
#define PID_L_I  50.0f
#define PID_L_D  0.0f

#define PID_R_P  2800.0f
#define PID_R_I  50.0f
#define PID_R_D  0.0f


#define MECHANICAL_BALANCE_BIAS (-3.4f)

#define V_MAX_OUT  33000.0f
#define V_MAX_IOUT 6000.0f

#define A_MAX_OUT  30000.0f
#define A_MAX_IOUT 6000.0f

typedef enum {
    CAR_MOTION_STOP=0,
    CAR_MOTION_FOWARD,
    CAR_MOTION_BACKWARD,
    CAR_MOTION_LEFT,
    CAR_MOTION_RIGHT
} MotionState;


typedef struct Car Car;

struct Car {
    //״̬����
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

    //�豸����
    Motor motor_l;
    Motor motor_r;
    Encoder encoder_l;
    Encoder encoder_r;
    Imu imu;

    //��Ա����
    void (*CarMove)(Car *self, int8_t setSpeed);
};

Car newCar(void);

void CarMove(Car *self, int8_t setSpeed);

#endif
