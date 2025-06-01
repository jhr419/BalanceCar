#include "multiTask.h"
#include "cmsis_os.h"
#include "car.h"
#include "calibrate_angle.h"
#include "exti_devices.h"
#include "potentiometers.h"

extern Car car;

void StartMultiTask(void const * argument){
	while(1){
		HC_trig();
		osDelay(100);
	}
}
