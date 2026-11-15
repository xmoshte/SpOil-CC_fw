/*
 * tb6612fng.c
 *
 *  Created on: Oct 11, 2025
 *  Author: moshte
 */

#include "tb6612fng.h"

void tbSetStndbyPin(enum gpioLevel opt){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, opt);
}

void tbSetAin1Pin(enum gpioLevel opt){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, opt);
}

void tbSetAin2Pin(enum gpioLevel opt){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, opt);
}

void tbPmwStart(void){
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

/**
 * @brief: Vary the duty cycle PMW output
 * @param: duty - Value in percentage for the duty cycle. (0-100)
 */
void tbSetDutyCycle(float duty){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (qbyte)duty);
}

void tbResetDutyCycle(void){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}

void tbMotorCw(dbyte rpm){
	if(rpm > TBMAXRPM){
	   rpm = TBMAXRPM;
	}

    tbSetAin1Pin(HIGH);
    tbSetAin2Pin(LOW);
	tbSetStndbyPin(HIGH);

	float voltsMtr =  rpm * VOLTSPERRPMTB;
	float duty = ((voltsMtr/MAXVOLTAGE) * 100);
    tbSetDutyCycle(duty);

    logString("TB6612FNG: Clockwise mode\r\n");
}

void tbMotorCcw(dbyte rpm){
	if(rpm > TBMAXRPM){
	   rpm = TBMAXRPM;
	}

    tbSetAin1Pin(LOW);
    tbSetAin2Pin(HIGH);
	tbSetStndbyPin(HIGH);

	float voltsMtr =  rpm * VOLTSPERRPMTB;
	float duty = ((voltsMtr/MAXVOLTAGE) * 100);
    tbSetDutyCycle(duty);

    logString("TB6612FNG: Counter clockwise mode\r\n");
}

void tbMotorShortBrake(void){
    tbSetAin1Pin(HIGH);
    tbSetAin2Pin(HIGH);

    tbResetDutyCycle();

    logString("TB6612FNG: Short brake\r\n");
}

void tbMotorStop(void){
    tbSetAin1Pin(LOW);
    tbSetAin2Pin(LOW);

    tbSetDutyCycle(100);

    logString("TB6612FNG: Stop\r\n");
}

void tbMotorStndby(void){
	tbSetStndbyPin(LOW);
	logString("TB6612FNG: Standby\r\n");
}

/**
 * @brief: Drive the motor at a specific rpm and direction
 * @param: rpm - revolution per minute for the motor (0-200)
 * @param: dir - direction of rotation. 0 for clockwise, 1 for counter clockwise
 */
void tbMotorDrive(dbyte rpm, byte dir){

	if(dir == 0){
		tbMotorCw(rpm);
	}
	else if(dir == 1){
		tbMotorCcw(rpm);
	}

}

void tbMotorDriveRevolutions(dbyte rpm, byte dir, byte rev){
	qbyte msec = ((qbyte)rev * 60000) / rpm;

    tbMotorDrive(rpm, dir);
    osDelay(msec);
    tbMotorStop();
};

void tbMotorDriveDuration(qbyte rpm, byte dir, dbyte sdur){
	dbyte msec = sdur * 1000;

	tbMotorDrive(rpm, dir);
	osDelay(msec);
	tbMotorStop();
};

/**
 * @brief: One stroke with a full-duty kick-start, then the requested rpm.
 *         Total stroke time equals strokeMs (the kick is part of it).
 */
void tbKickStroke(dbyte rpm, byte dir, qbyte strokeMs){
	qbyte kickMs = TBKICKMS;

	/* Kick only when below full speed and the stroke is long enough */
	if(rpm > 0 && rpm < TBMAXRPM && strokeMs > kickMs){
		tbMotorDrive(TBMAXRPM, dir);
		osDelay(kickMs);
		tbMotorDrive(rpm, dir);
		osDelay(strokeMs - kickMs);
	}
	else{
		tbMotorDrive(rpm, dir);
		osDelay(strokeMs);
	}

	tbMotorStop();
}

/**
 * @brief: Run full protrusion/retraction cycles.
 * @param: cycles         - number of cycles. One cycle = protrusion (dir 1),
 *                          dwell at the end, then retraction (dir 0).
 * @param: protrudeRpm    - motor rpm during protrusion
 * @param: retractRpm     - motor rpm during retraction
 * @param: protrudeDur    - duration of each protrusion stroke in seconds
 * @param: retractDur     - duration of each retraction stroke in seconds
 * @param: strokeDurExtra - extra seconds added to the last retraction
 * @param: dwellDur       - seconds to stay at the end of the protrusion
 *                          before retracting
 */
void tbMotorCycles(byte cycles, dbyte protrudeRpm, dbyte retractRpm, dbyte protrudeDur, dbyte retractDur, dbyte strokeDurExtra, dbyte dwellDur){

	for(byte i = 0; i < cycles; i++){
		tbKickStroke(protrudeRpm, 1, (qbyte)protrudeDur * 1000);

		/* Hold at the end of the protrusion (motor already stopped) */
		if(dwellDur > 0){
			osDelay((qbyte)dwellDur * 1000);
		}

		/* Last retraction runs longer to make sure it fully homes */
		qbyte retractSec = (i == (cycles - 1)) ? ((qbyte)retractDur + strokeDurExtra) : retractDur;

		tbKickStroke(retractRpm, 0, retractSec * 1000);
	}
}
