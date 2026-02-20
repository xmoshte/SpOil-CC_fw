/*
 * log.c
 *
 *  Created on: Oct 4, 2025
 *  Author: moshte
 */

#include "log.h"

HAL_StatusTypeDef logString(const char* msg){
	if(HAL_UART_Transmit(&huart2, (byte*)msg, strlen(msg), LOG_TO) == HAL_OK ){
      return HAL_OK;
	}
	else{
      return HAL_ERROR;
	}
}

HAL_StatusTypeDef logByte(byte num){
    char buf[4];
    byte len = snprintf(buf, sizeof(buf), "%u", num);

    return HAL_UART_Transmit(&huart2, (byte*)buf, len, LOG_TO);
}

HAL_StatusTypeDef logInteger(int num){

	char buf[16];
	dbyte len = snprintf(buf, sizeof(buf), "%d", num);

	return HAL_UART_Transmit(&huart2, (byte*)buf, len, LOG_TO);
}

HAL_StatusTypeDef logFloat(float num){
	char buf[16];
	dbyte len = snprintf(buf, sizeof(buf), "%f", num);

	return HAL_UART_Transmit(&huart2, (byte*)buf, len, LOG_TO);
}

void nextLine(void){
	logString("\r\n");
}
