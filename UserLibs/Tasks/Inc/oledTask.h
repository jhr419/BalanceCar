#ifndef OLEDTASK_H_
#define OLEDTASK_H_

#include "main.h"

/**
  * @file    oledtask.h
  * @brief   OLED 显示任务启动接口 | OLED display task start interface
  */

/**
  * @brief   启动 OLED 任务 | Start the OLED task
  * @param   argument 任务参数指针 | Pointer to task argument
  */
void StartOledTask(void const *argument);

#endif /* OLEDTASK_H_ */
