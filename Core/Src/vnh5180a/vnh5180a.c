/*
 * vnh5180a.c
 *
 *  Created on: Oct 14, 2025
 *      Author: moshte
 */
#include "vnh5180a.h"

void vnSetInAPin(enum gpioLevel opt){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, opt);
}

void vnSetInBPin(enum gpioLevel opt){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, opt);
}

GPIO_PinState vnReadDiagAPin(void){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)){
		return HIGH;
	}
	else{
		return LOW;
	}
}

GPIO_PinState vnReadDiagBPin(void){
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)){
		return HIGH;
	}
	else{
		return LOW;
	}
}

byte vnCheckMotorStatus(void){
	GPIO_PinState pinAStatus = 0;
	GPIO_PinState pinBStatus = 0;

	pinAStatus = vnReadDiagAPin();
	pinBStatus = vnReadDiagBPin();

	if(pinAStatus && pinBStatus){
        logString("VNH5180A-E: Normal\r\n");
        return 1;
	}
	else{
		logString("VNH5180A-E: Faulty\r\n");
		return 0;
	}
}

void vnPmwStart(void){
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void vnSetDutyCycle(float duty){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, (qbyte)duty);
}

void vnResetDutyCycle(void){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
}


void vnMotorCw(qbyte rpm){
	byte sts = 0;
	sts = vnCheckMotorStatus();

	if(rpm > VNMAXRPM){
	   rpm = VNMAXRPM;
    }

	float voltsMtr =  rpm * VOLTSPERRPMVN;
	float duty = ((voltsMtr/MAXVOLTAGE) * 100);

	if(sts){
		vnSetInAPin(HIGH);
		vnSetInBPin(LOW);

		vnSetDutyCycle(duty);

		logString("VNH5180A-E: Clockwise Mode\r\n");
	}
	else{
		logString("VNH5180A-E: High Impedance State\r\n");
		return;
	}
	return;
}

void vnMotorCcw(qbyte rpm){
	byte sts = 0;
	sts = vnCheckMotorStatus();

	if(rpm > VNMAXRPM){
	   rpm = VNMAXRPM;
    }

	float voltsMtr =  rpm * VOLTSPERRPMVN;
	float duty = ((voltsMtr/MAXVOLTAGE) * 100);

	if(sts){
		vnSetInAPin(LOW);
		vnSetInBPin(HIGH);

		vnSetDutyCycle(duty);

		logString("VNH5180A-E: Counter Clockwise Mode\r\n");
	}
	else{
		logString("VNH5180A-E: High Impedance State or IoutK\r\n");
		return;
	}
	return;
}

void vnMotorBrakeToGnd(void){
	byte sts = 0;
	sts = vnCheckMotorStatus();

	if(sts){
		vnSetInAPin(LOW);
		vnSetInBPin(LOW);

		vnResetDutyCycle();

		logString("VNH5180A-E: Brake to ground\r\n");
	}
	else{
		logString("VNH5180A-E: High Imp state\r\n");
		return;
	}
	return;
}

void vnMotorBrakeToVcc(void){
	byte sts = 0;
	sts = vnCheckMotorStatus();

	if(sts){
		vnSetInAPin(HIGH);
		vnSetInBPin(HIGH);

		vnResetDutyCycle();

		logString("VNH5180A-E: Brake to VCC\r\n");
	}
	else{
		logString("VNH5180A-E: High Imp stater\\r\n");
		return;
	}
	return;
}


void vnMotorDrive(qbyte rpm, byte dir){

	if(dir == 0){
		vnMotorCw(rpm);
	}
	else if(dir == 1){
		vnMotorCcw(rpm);
	}
}

void vnMotorDriveDuration(qbyte rpm, byte dir, dbyte sdur){
	dbyte msec = sdur * 1000;

	vnMotorDrive(5000, 1);
	osDelay(msec);
	vnMotorBrakeToGnd();
};

void csEnOrDis(byte enOrDis){
	if(enOrDis != 0 || enOrDis != 1){
		logString("VNH5180A-E: Incorrect CS enable or disable parameter!\r\n");
		return;
	}
	if(enOrDis){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LOW);
	}
	else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, HIGH);
	}
}
