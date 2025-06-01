#ifndef MULTITASK_H_
#define MULTITASK_H_

#include "main.h"

/**
  * @file    multitask.h
  * @brief   多任务启动接口 | Interface to start multi-task
  */

/**
  * @brief   启动多任务 | Start multi-task
  * @param   argument 任务参数指针 | Pointer to task argument
  */
void StartMultiTask(void const * argument);

#endif /* MULTITASK_H_ */
