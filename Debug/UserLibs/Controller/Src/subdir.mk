################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UserLibs/Controller/Src/pid.c 

OBJS += \
./UserLibs/Controller/Src/pid.o 

C_DEPS += \
./UserLibs/Controller/Src/pid.d 


# Each subdirectory must supply rules for building sources it contributes
UserLibs/Controller/Src/%.o UserLibs/Controller/Src/%.su UserLibs/Controller/Src/%.cyclo: ../UserLibs/Controller/Src/%.c UserLibs/Controller/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Algorithm/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Bsp/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Controller/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Devices/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Support/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Tasks/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UserLibs-2f-Controller-2f-Src

clean-UserLibs-2f-Controller-2f-Src:
	-$(RM) ./UserLibs/Controller/Src/pid.cyclo ./UserLibs/Controller/Src/pid.d ./UserLibs/Controller/Src/pid.o ./UserLibs/Controller/Src/pid.su

.PHONY: clean-UserLibs-2f-Controller-2f-Src

