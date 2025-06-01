################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UserLibs/Tasks/Src/carTask.c \
../UserLibs/Tasks/Src/multiTask.c \
../UserLibs/Tasks/Src/oledTask.c 

OBJS += \
./UserLibs/Tasks/Src/carTask.o \
./UserLibs/Tasks/Src/multiTask.o \
./UserLibs/Tasks/Src/oledTask.o 

C_DEPS += \
./UserLibs/Tasks/Src/carTask.d \
./UserLibs/Tasks/Src/multiTask.d \
./UserLibs/Tasks/Src/oledTask.d 


# Each subdirectory must supply rules for building sources it contributes
UserLibs/Tasks/Src/%.o UserLibs/Tasks/Src/%.su UserLibs/Tasks/Src/%.cyclo: ../UserLibs/Tasks/Src/%.c UserLibs/Tasks/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/TH/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Algorithm/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Bsp/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Controller/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Devices/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Support/Inc" -I"D:/development tools/MCUdevelopment/STMIDEworkplace/BalanceCar/UserLibs/Tasks/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UserLibs-2f-Tasks-2f-Src

clean-UserLibs-2f-Tasks-2f-Src:
	-$(RM) ./UserLibs/Tasks/Src/carTask.cyclo ./UserLibs/Tasks/Src/carTask.d ./UserLibs/Tasks/Src/carTask.o ./UserLibs/Tasks/Src/carTask.su ./UserLibs/Tasks/Src/multiTask.cyclo ./UserLibs/Tasks/Src/multiTask.d ./UserLibs/Tasks/Src/multiTask.o ./UserLibs/Tasks/Src/multiTask.su ./UserLibs/Tasks/Src/oledTask.cyclo ./UserLibs/Tasks/Src/oledTask.d ./UserLibs/Tasks/Src/oledTask.o ./UserLibs/Tasks/Src/oledTask.su

.PHONY: clean-UserLibs-2f-Tasks-2f-Src

