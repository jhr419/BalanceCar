################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UserLibs/Bsp/Src/MPU6500.c \
../UserLibs/Bsp/Src/OLED.c \
../UserLibs/Bsp/Src/OLED_Data.c \
../UserLibs/Bsp/Src/inv_mpu.c \
../UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.c 

OBJS += \
./UserLibs/Bsp/Src/MPU6500.o \
./UserLibs/Bsp/Src/OLED.o \
./UserLibs/Bsp/Src/OLED_Data.o \
./UserLibs/Bsp/Src/inv_mpu.o \
./UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.o 

C_DEPS += \
./UserLibs/Bsp/Src/MPU6500.d \
./UserLibs/Bsp/Src/OLED.d \
./UserLibs/Bsp/Src/OLED_Data.d \
./UserLibs/Bsp/Src/inv_mpu.d \
./UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.d 


# Each subdirectory must supply rules for building sources it contributes
UserLibs/Bsp/Src/%.o UserLibs/Bsp/Src/%.su UserLibs/Bsp/Src/%.cyclo: ../UserLibs/Bsp/Src/%.c UserLibs/Bsp/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Algorithm/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Bsp/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Controller/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Devices/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Support/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Tasks/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UserLibs-2f-Bsp-2f-Src

clean-UserLibs-2f-Bsp-2f-Src:
	-$(RM) ./UserLibs/Bsp/Src/MPU6500.cyclo ./UserLibs/Bsp/Src/MPU6500.d ./UserLibs/Bsp/Src/MPU6500.o ./UserLibs/Bsp/Src/MPU6500.su ./UserLibs/Bsp/Src/OLED.cyclo ./UserLibs/Bsp/Src/OLED.d ./UserLibs/Bsp/Src/OLED.o ./UserLibs/Bsp/Src/OLED.su ./UserLibs/Bsp/Src/OLED_Data.cyclo ./UserLibs/Bsp/Src/OLED_Data.d ./UserLibs/Bsp/Src/OLED_Data.o ./UserLibs/Bsp/Src/OLED_Data.su ./UserLibs/Bsp/Src/inv_mpu.cyclo ./UserLibs/Bsp/Src/inv_mpu.d ./UserLibs/Bsp/Src/inv_mpu.o ./UserLibs/Bsp/Src/inv_mpu.su ./UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.cyclo ./UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.d ./UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.o ./UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.su

.PHONY: clean-UserLibs-2f-Bsp-2f-Src

