################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RS485Module/portserial/port_timer.c \
../RS485Module/portserial/portserial.c \
../RS485Module/portserial/rs_port.c 

OBJS += \
./RS485Module/portserial/port_timer.o \
./RS485Module/portserial/portserial.o \
./RS485Module/portserial/rs_port.o 

C_DEPS += \
./RS485Module/portserial/port_timer.d \
./RS485Module/portserial/portserial.d \
./RS485Module/portserial/rs_port.d 


# Each subdirectory must supply rules for building sources it contributes
RS485Module/portserial/%.o: ../RS485Module/portserial/%.c RS485Module/portserial/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/zanki/STM32CubeIDE/workspace_1.7.0/RS485_example/RS485Module/protocol" -I"C:/Users/zanki/STM32CubeIDE/workspace_1.7.0/RS485_example/RS485Module/portserial" -I"C:/Users/zanki/STM32CubeIDE/workspace_1.7.0/RS485_example/RS485Module/rs_app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

