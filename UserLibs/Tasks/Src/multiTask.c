#include "multiTask.h"
#include "cmsis_os.h"
#include "car.h"
#include "calibrate_angle.h"
#include "exti_devices.h"
#include "potentiometers.h"

extern Car car;  // 全局小车实例 | Global car instance

/**
  * @brief   启动多任务 | Start multi-task
  * @param   argument 任务参数指针（未使用） | Task argument pointer (unused)
  * @note    周期性触发超声波测距 | Periodically trigger ultrasonic measurement
  */
void StartMultiTask(void const *argument) {
    while (1) {
        HC_trig();      // 触发超声波传感器 | Trigger ultrasonic sensor
        osDelay(100);   // 延时100ms | Delay 100ms
    }
}
