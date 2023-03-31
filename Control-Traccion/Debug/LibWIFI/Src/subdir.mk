################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LibWIFI/Src/es_wifi.c \
../LibWIFI/Src/es_wifi_io.c \
../LibWIFI/Src/wifi.c 

OBJS += \
./LibWIFI/Src/es_wifi.o \
./LibWIFI/Src/es_wifi_io.o \
./LibWIFI/Src/wifi.o 

C_DEPS += \
./LibWIFI/Src/es_wifi.d \
./LibWIFI/Src/es_wifi_io.d \
./LibWIFI/Src/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
LibWIFI/Src/%.o LibWIFI/Src/%.su: ../LibWIFI/Src/%.c LibWIFI/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/carlo/Desktop/SAC/Control-Traccion/LibWIFI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LibWIFI-2f-Src

clean-LibWIFI-2f-Src:
	-$(RM) ./LibWIFI/Src/es_wifi.d ./LibWIFI/Src/es_wifi.o ./LibWIFI/Src/es_wifi.su ./LibWIFI/Src/es_wifi_io.d ./LibWIFI/Src/es_wifi_io.o ./LibWIFI/Src/es_wifi_io.su ./LibWIFI/Src/wifi.d ./LibWIFI/Src/wifi.o ./LibWIFI/Src/wifi.su

.PHONY: clean-LibWIFI-2f-Src

