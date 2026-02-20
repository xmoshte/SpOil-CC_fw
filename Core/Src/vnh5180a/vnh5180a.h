/*
 * vnh5180a.h
 *
 *  Created on: Oct 14, 2025
 *      Author: moshte
 */

#ifndef VNH5180A_H
#define VNH5180A_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "type.h"
#include "log.h"
#include <stdint.h>
#include <stddef.h>

#define VOLTSPERRPMVN 0.00106 /* 12/11300 */
#define MAXVOLTAGE 12
#define VNMAXRPM 11300

extern TIM_HandleTypeDef htim3;

void vnSetInAPin(enum gpioLevel opt);
void vnSetInBPin(enum gpioLevel opt);

GPIO_PinState vnReadDiagAPin(void);
GPIO_PinState vnReadDiagBPin(void);

byte vnCheckMotorStatus(void);

void vnPmwStart(void);
void vnSetDutyCycle(float duty);
void vnResetDutyCycle(void);

void vnMotorCw(qbyte rpm);
void vnMotorCcw(qbyte rpm);

void vnMotorBrakeToGnd(void);
void vnMotorBrakeToVcc(void);

void vnMotorDrive(qbyte rpm, byte dir);
void vnMotorDriveDuration(qbyte rpm, byte dir, dbyte sdur);

void csEnOrDis(byte enOrDis);

#endif /* VNH5180A_H */
