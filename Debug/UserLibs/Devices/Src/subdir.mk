################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UserLibs/Devices/Src/car.c \
../UserLibs/Devices/Src/encoder.c \
../UserLibs/Devices/Src/exti_devices.c \
../UserLibs/Devices/Src/imu.c \
../UserLibs/Devices/Src/motor.c \
../UserLibs/Devices/Src/potentiometers.c 

OBJS += \
./UserLibs/Devices/Src/car.o \
./UserLibs/Devices/Src/encoder.o \
./UserLibs/Devices/Src/exti_devices.o \
./UserLibs/Devices/Src/imu.o \
./UserLibs/Devices/Src/motor.o \
./UserLibs/Devices/Src/potentiometers.o 

C_DEPS += \
./UserLibs/Devices/Src/car.d \
./UserLibs/Devices/Src/encoder.d \
./UserLibs/Devices/Src/exti_devices.d \
./UserLibs/Devices/Src/imu.d \
./UserLibs/Devices/Src/motor.d \
./UserLibs/Devices/Src/potentiometers.d 


# Each subdirectory must supply rules for building sources it contributes
UserLibs/Devices/Src/%.o UserLibs/Devices/Src/%.su UserLibs/Devices/Src/%.cyclo: ../UserLibs/Devices/Src/%.c UserLibs/Devices/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Algorithm/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Bsp/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Controller/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Devices/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Support/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Tasks/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UserLibs-2f-Devices-2f-Src

clean-UserLibs-2f-Devices-2f-Src:
	-$(RM) ./UserLibs/Devices/Src/car.cyclo ./UserLibs/Devices/Src/car.d ./UserLibs/Devices/Src/car.o ./UserLibs/Devices/Src/car.su ./UserLibs/Devices/Src/encoder.cyclo ./UserLibs/Devices/Src/encoder.d ./UserLibs/Devices/Src/encoder.o ./UserLibs/Devices/Src/encoder.su ./UserLibs/Devices/Src/exti_devices.cyclo ./UserLibs/Devices/Src/exti_devices.d ./UserLibs/Devices/Src/exti_devices.o ./UserLibs/Devices/Src/exti_devices.su ./UserLibs/Devices/Src/imu.cyclo ./UserLibs/Devices/Src/imu.d ./UserLibs/Devices/Src/imu.o ./UserLibs/Devices/Src/imu.su ./UserLibs/Devices/Src/motor.cyclo ./UserLibs/Devices/Src/motor.d ./UserLibs/Devices/Src/motor.o ./UserLibs/Devices/Src/motor.su ./UserLibs/Devices/Src/potentiometers.cyclo ./UserLibs/Devices/Src/potentiometers.d ./UserLibs/Devices/Src/potentiometers.o ./UserLibs/Devices/Src/potentiometers.su

.PHONY: clean-UserLibs-2f-Devices-2f-Src

