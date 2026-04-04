################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bq25798/bq25798.c \
../Core/Src/bq25798/bqApp.c 

OBJS += \
./Core/Src/bq25798/bq25798.o \
./Core/Src/bq25798/bqApp.o 

C_DEPS += \
./Core/Src/bq25798/bq25798.d \
./Core/Src/bq25798/bqApp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/bq25798/%.o Core/Src/bq25798/%.su Core/Src/bq25798/%.cyclo: ../Core/Src/bq25798/%.c Core/Src/bq25798/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Dell/Desktop/xmoshte/projects/cubeideprjcts/SpOil-CC_fw/Core/Src/ap33772s" -I"C:/Users/Dell/Desktop/xmoshte/projects/cubeideprjcts/SpOil-CC_fw/Core/Src/bq25798" -I"C:/Users/Dell/Desktop/xmoshte/projects/cubeideprjcts/SpOil-CC_fw/Core/Src/vnh5180a" -I"C:/Users/Dell/Desktop/xmoshte/projects/cubeideprjcts/SpOil-CC_fw/Core/Src/log" -I"C:/Users/Dell/Desktop/xmoshte/projects/cubeideprjcts/SpOil-CC_fw/Core/Src/tb6612fng" -I"C:/Users/Dell/Desktop/xmoshte/projects/cubeideprjcts/SpOil-CC_fw/Core/Src/i2c" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-bq25798

clean-Core-2f-Src-2f-bq25798:
	-$(RM) ./Core/Src/bq25798/bq25798.cyclo ./Core/Src/bq25798/bq25798.d ./Core/Src/bq25798/bq25798.o ./Core/Src/bq25798/bq25798.su ./Core/Src/bq25798/bqApp.cyclo ./Core/Src/bq25798/bqApp.d ./Core/Src/bq25798/bqApp.o ./Core/Src/bq25798/bqApp.su

.PHONY: clean-Core-2f-Src-2f-bq25798

