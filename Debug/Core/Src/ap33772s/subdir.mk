################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ap33772s/ap33772s.c \
../Core/Src/ap33772s/apApp.c 

OBJS += \
./Core/Src/ap33772s/ap33772s.o \
./Core/Src/ap33772s/apApp.o 

C_DEPS += \
./Core/Src/ap33772s/ap33772s.d \
./Core/Src/ap33772s/apApp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ap33772s/%.o Core/Src/ap33772s/%.su Core/Src/ap33772s/%.cyclo: ../Core/Src/ap33772s/%.c Core/Src/ap33772s/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/ap33772s" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/bq25798" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/vnh5180a" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/log" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/tb6612fng" -I"C:/Users/Dell/STM32CubeIDE/workspace_1.19.0/SpOil-CC_v2/Core/Src/i2c" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ap33772s

clean-Core-2f-Src-2f-ap33772s:
	-$(RM) ./Core/Src/ap33772s/ap33772s.cyclo ./Core/Src/ap33772s/ap33772s.d ./Core/Src/ap33772s/ap33772s.o ./Core/Src/ap33772s/ap33772s.su ./Core/Src/ap33772s/apApp.cyclo ./Core/Src/ap33772s/apApp.d ./Core/Src/ap33772s/apApp.o ./Core/Src/ap33772s/apApp.su

.PHONY: clean-Core-2f-Src-2f-ap33772s

