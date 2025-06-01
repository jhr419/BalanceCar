#ifndef IMU_H_
#define IMU_H_

#include "main.h"
#include "MPU6500.h"

/**
  * @file    imu.h
  * @brief   IMU（惯性测量单元）接口定义 | IMU (Inertial Measurement Unit) interface definitions
  */

/**
  * @struct  Imu
  * @brief   IMU 数据结构 | IMU data structure
  *
  * @note    包含初始化结果、姿态角、加速度和角速度数据，以及函数指针 | Contains init status, attitude angles, accel/gyro data, and function pointers
  */
typedef struct Imu Imu;

typedef struct Imu {
    uint8_t init_result;  /**< 初始化状态（0 成功） | Initialization status (0 = success) */
    float pitch;          /**< 俯仰角 | Pitch angle */
    float roll;           /**< 横滚角 | Roll angle */
    float yaw;            /**< 偏航角 | Yaw angle */

    float ax;             /**< X 轴加速度 | Acceleration X */
    float ay;             /**< Y 轴加速度 | Acceleration Y */
    float az;             /**< Z 轴加速度 | Acceleration Z */

    float gyrox;          /**< X 轴角速度 | Gyro rate X */
    float gyroy;          /**< Y 轴角速度 | Gyro rate Y */
    float gyroz;          /**< Z 轴角速度 | Gyro rate Z */

    int  (*Enable)(Imu *self);    /**< 启用并初始化 IMU | Pointer to enable/init function */
    void (*Get_Data)(Imu *self);  /**< 获取 IMU 数据 | Pointer to data retrieval function */
} Imu;

/**
  * @brief   创建并初始化 IMU 实例 | Create and initialize an IMU instance
  * @return  返回初始化后的 Imu 结构体 | Returns initialized Imu struct
  */
Imu newImu(void);

/**
  * @brief   启用 IMU 并初始化底层 MPU6500 | Enable IMU and initialize underlying MPU6500
  * @param   self  指向 Imu 实例的指针 | Pointer to Imu instance
  * @return  返回初始化结果（0 = 成功） | Returns init status (0 = success)
  */
int Enable(Imu *self);

/**
  * @brief   从 MPU6500 获取姿态和传感器数据 | Get attitude and sensor data from MPU6500
  * @param   self  指向 Imu 实例的指针 | Pointer to Imu instance
  */
void Get_Data(Imu *self);

#endif /* IMU_H_ */
