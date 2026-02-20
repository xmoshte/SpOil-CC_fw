################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/tb6612fng/tb6612fng.c 

OBJS += \
./Core/Src/tb6612fng/tb6612fng.o 

C_DEPS += \
./Core/Src/tb6612fng/tb6612fng.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/tb6612fng/%.o Core/Src/tb6612fng/%.su Core/Src/tb6612fng/%.cyclo: ../Core/Src/tb6612fng/%.c Core/Src/tb6612fng/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/ap33772s" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/bq25798" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/vnh5180a" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/log" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/tb6612fng" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/i2c" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-tb6612fng

clean-Core-2f-Src-2f-tb6612fng:
	-$(RM) ./Core/Src/tb6612fng/tb6612fng.cyclo ./Core/Src/tb6612fng/tb6612fng.d ./Core/Src/tb6612fng/tb6612fng.o ./Core/Src/tb6612fng/tb6612fng.su

.PHONY: clean-Core-2f-Src-2f-tb6612fng

