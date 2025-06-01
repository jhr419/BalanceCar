#include "carTask.h"
#include "car.h"
#include "communication.h"
#include "cmsis_os.h"

extern Car car;

/**
  * @brief   启动小车任务 | Start the car task
  * @param   argument 任务参数指针 | Pointer to task argument
  * @note    不断获取 IMU 数据并执行小车移动控制 | Continuously get IMU data and execute car movement control
  */
void StartCarTask(void const *argument) {
    car.balanceBias = MECHANICAL_BALANCE_BIAS;  // 设置平衡偏置 | Set balance bias

    while (1) {
        car.imu.Get_Data(&car.imu);    // 获取IMU数据 | Get IMU data
        car.CarMove(&car, 0);          // 调用移动函数（setSpeed参数未使用） | Call move function (setSpeed unused)
        osDelay(5);                    // 延时5ms | Delay 5ms
    }
}
