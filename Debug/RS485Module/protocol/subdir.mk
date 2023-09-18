################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RS485Module/protocol/rs_protocol.c 

OBJS += \
./RS485Module/protocol/rs_protocol.o 

C_DEPS += \
./RS485Module/protocol/rs_protocol.d 


# Each subdirectory must supply rules for building sources it contributes
RS485Module/protocol/%.o: ../RS485Module/protocol/%.c RS485Module/protocol/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/zanki/STM32CubeIDE/workspace_1.7.0/RS485_example/RS485Module/protocol" -I"C:/Users/zanki/STM32CubeIDE/workspace_1.7.0/RS485_example/RS485Module/portserial" -I"C:/Users/zanki/STM32CubeIDE/workspace_1.7.0/RS485_example/RS485Module/rs_app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

