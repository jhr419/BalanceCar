#include "carTask.h"
#include "car.h"
#include "communication.h"
#include "cmsis_os.h"

extern Car car;
void StartCarTask(void const * argument){
	car.balance_bias = MECHANICAL_BALANCE_BIAS;
	while(1){
		car.imu.Get_Data(&car.imu);
//		car.CarMove(&car, 0);

//		uart_printf(&huart_pc,"%f\n", car.imu.roll);
		osDelay(5);
	}
}
