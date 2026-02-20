/*
 * log.h
 *
 *  Created on: Oct 4, 2025
 *  Author: moshte
 */

#ifndef LOG_H
#define LOG_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "type.h"

#define LOG_TO HAL_MAX_DELAY //Log timeout
#define LOG_EN // Enable or disable logging

extern UART_HandleTypeDef huart2;

enum gpioLevel{
	HIGH = GPIO_PIN_SET,
	LOW = GPIO_PIN_RESET
};

HAL_StatusTypeDef logString(const char* msg);
HAL_StatusTypeDef logByte(byte num);
HAL_StatusTypeDef logInteger(int num);
HAL_StatusTypeDef logFloat(float num);

void nextLine(void);

#endif /* LOG_H */
