################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/lsm303c/lsm303c.c 

OBJS += \
./Components/lsm303c/lsm303c.o 

C_DEPS += \
./Components/lsm303c/lsm303c.d 


# Each subdirectory must supply rules for building sources it contributes
Components/lsm303c/%.o Components/lsm303c/%.su: ../Components/lsm303c/%.c Components/lsm303c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L475xx -c -I../BSP -I../Components -I../Core/Inc -I../LibWIFI/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-lsm303c

clean-Components-2f-lsm303c:
	-$(RM) ./Components/lsm303c/lsm303c.d ./Components/lsm303c/lsm303c.o ./Components/lsm303c/lsm303c.su

.PHONY: clean-Components-2f-lsm303c

