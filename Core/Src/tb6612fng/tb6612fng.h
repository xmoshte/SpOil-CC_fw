/*
 * tb6612fng.h
 *
 * Created on: Oct 11, 2025
 * Author: moshte
 */

#ifndef TB6612FNG_H
#define TB6612FNG_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "type.h"
#include "log.h"
#include "cmsis_os.h"
#include <stdint.h>
#include <stddef.h>

#define VOLTSPERRPMTB 0.04 /* 12/200 */
#define MAXVOLTAGE 12
#define TBMAXRPM 300
#define NOOFREVOLUTIONS 8

extern TIM_HandleTypeDef htim3;

void tbPmwStart(void); //

void tbSetStndbyPin(enum gpioLevel opt);
void tbSetAin1Pin(enum gpioLevel opt);
void tbSetAin2Pin(enum gpioLevel opt);

void tbSetDutyCycle(float duty);
void tbResetDutyCycle(void);

void tbMotorCw(dbyte rpm);
void tbMotorCcw(dbyte rpm);
void tbMotorShortBrake(void);
void tbMotorStop(void);
void tbMotorStndby(void);

void tbMotorDrive(dbyte rpm, byte dir); //
void tbMotorDriveRevolutions(dbyte rpm, byte dir, byte rev);
#endif /*TB6612FNG_H */
