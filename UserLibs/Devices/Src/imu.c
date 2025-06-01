#include "imu.h"

/**
  * @brief   创建并初始化 IMU 实例 | Create and initialize IMU instance
  * @return  返回 IMU 结构体 | Returns IMU struct
  */
Imu newImu(void) {
    Imu i;
    i.Enable   = Enable;    // 绑定启用函数 | Bind enable function
    i.Get_Data = Get_Data;  // 绑定数据获取函数 | Bind data retrieval function
    return i;               // 返回实例 | Return instance
}

/**
  * @brief   启用 IMU 并初始化 MPU6500 | Enable IMU and init MPU6500
  * @param   self  指向 IMU 实例指针 | Pointer to IMU instance
  * @return  返回初始化结果（0 成功） | Returns init status (0 = success)
  */
int Enable(Imu *self) {
    self->init_result = (uint8_t)MPU_6500_Init();  // 调用底层初始化 | Call low-level init
    return self->init_result;                      // 返回状态 | Return status
}

/**
  * @brief   获取传感器姿态和原始数据 | Get sensor attitude and raw data
  * @param   self  指向 IMU 实例指针 | Pointer to IMU instance
  */
void Get_Data(Imu *self) {
    // 调用 DMP 获取俯仰、横滚、航向、加速度、陀螺仪数据
    // Call DMP to get pitch, roll, yaw, accel, and gyro data
    MPU6500_DMP_Get_Data(
            &self->pitch, &self->roll, &self->yaw,
            &self->ax,    &self->ay,   &self->az,
            &self->gyrox, &self->gyroy,&self->gyroz
    );
}
