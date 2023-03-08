################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/lsm6dsl/lsm6dsl.c 

OBJS += \
./Components/lsm6dsl/lsm6dsl.o 

C_DEPS += \
./Components/lsm6dsl/lsm6dsl.d 


# Each subdirectory must supply rules for building sources it contributes
Components/lsm6dsl/%.o Components/lsm6dsl/%.su: ../Components/lsm6dsl/%.c Components/lsm6dsl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L475xx -c -I../BSP -I../Components -I../Core/Inc -I../LibWIFI/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-lsm6dsl

clean-Components-2f-lsm6dsl:
	-$(RM) ./Components/lsm6dsl/lsm6dsl.d ./Components/lsm6dsl/lsm6dsl.o ./Components/lsm6dsl/lsm6dsl.su

.PHONY: clean-Components-2f-lsm6dsl

