################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/vnh5180a/vnh5180a.c 

OBJS += \
./Core/Src/vnh5180a/vnh5180a.o 

C_DEPS += \
./Core/Src/vnh5180a/vnh5180a.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/vnh5180a/%.o Core/Src/vnh5180a/%.su Core/Src/vnh5180a/%.cyclo: ../Core/Src/vnh5180a/%.c Core/Src/vnh5180a/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/ap33772s" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/bq25798" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/vnh5180a" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/log" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/tb6612fng" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/i2c" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-vnh5180a

clean-Core-2f-Src-2f-vnh5180a:
	-$(RM) ./Core/Src/vnh5180a/vnh5180a.cyclo ./Core/Src/vnh5180a/vnh5180a.d ./Core/Src/vnh5180a/vnh5180a.o ./Core/Src/vnh5180a/vnh5180a.su

.PHONY: clean-Core-2f-Src-2f-vnh5180a

