################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/stm32l475e_iot01.c \
../BSP/stm32l475e_iot01_accelero.c \
../BSP/stm32l475e_iot01_gyro.c \
../BSP/stm32l475e_iot01_hsensor.c \
../BSP/stm32l475e_iot01_magneto.c \
../BSP/stm32l475e_iot01_psensor.c \
../BSP/stm32l475e_iot01_qspi.c \
../BSP/stm32l475e_iot01_tsensor.c 

OBJS += \
./BSP/stm32l475e_iot01.o \
./BSP/stm32l475e_iot01_accelero.o \
./BSP/stm32l475e_iot01_gyro.o \
./BSP/stm32l475e_iot01_hsensor.o \
./BSP/stm32l475e_iot01_magneto.o \
./BSP/stm32l475e_iot01_psensor.o \
./BSP/stm32l475e_iot01_qspi.o \
./BSP/stm32l475e_iot01_tsensor.o 

C_DEPS += \
./BSP/stm32l475e_iot01.d \
./BSP/stm32l475e_iot01_accelero.d \
./BSP/stm32l475e_iot01_gyro.d \
./BSP/stm32l475e_iot01_hsensor.d \
./BSP/stm32l475e_iot01_magneto.d \
./BSP/stm32l475e_iot01_psensor.d \
./BSP/stm32l475e_iot01_qspi.d \
./BSP/stm32l475e_iot01_tsensor.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o BSP/%.su: ../BSP/%.c BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L475xx -c -I../BSP -I../Components -I../Core/Inc -I../LibWIFI/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP

clean-BSP:
	-$(RM) ./BSP/stm32l475e_iot01.d ./BSP/stm32l475e_iot01.o ./BSP/stm32l475e_iot01.su ./BSP/stm32l475e_iot01_accelero.d ./BSP/stm32l475e_iot01_accelero.o ./BSP/stm32l475e_iot01_accelero.su ./BSP/stm32l475e_iot01_gyro.d ./BSP/stm32l475e_iot01_gyro.o ./BSP/stm32l475e_iot01_gyro.su ./BSP/stm32l475e_iot01_hsensor.d ./BSP/stm32l475e_iot01_hsensor.o ./BSP/stm32l475e_iot01_hsensor.su ./BSP/stm32l475e_iot01_magneto.d ./BSP/stm32l475e_iot01_magneto.o ./BSP/stm32l475e_iot01_magneto.su ./BSP/stm32l475e_iot01_psensor.d ./BSP/stm32l475e_iot01_psensor.o ./BSP/stm32l475e_iot01_psensor.su ./BSP/stm32l475e_iot01_qspi.d ./BSP/stm32l475e_iot01_qspi.o ./BSP/stm32l475e_iot01_qspi.su ./BSP/stm32l475e_iot01_tsensor.d ./BSP/stm32l475e_iot01_tsensor.o ./BSP/stm32l475e_iot01_tsensor.su

.PHONY: clean-BSP

