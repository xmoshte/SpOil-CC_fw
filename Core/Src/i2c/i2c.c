/*
 * i2c.c
 *
 *  Created on: Oct 4, 2025
 *  Author: moshte
 */
#include "i2c.h"

byte readBuf[READ_BUFF_LEN] = {0};
byte writeBuf[WRITE_BUFF_LEN] = {0};

void clearWriteBuf(void){
	for (byte i = 0; i < WRITE_BUFF_LEN; i++)
	{
		writeBuf[i] = 0;
	}
}

void clearReadBuf(void){
	for (byte i = 0; i < READ_BUFF_LEN; i++)
	{
		readBuf[i] = 0;
	}
}

int i2cApWrite(void *ctx, byte cmd, byte* data, size_t len){
	byte slvAdrss = AP_ADDRESS;
  if(HAL_I2C_Mem_Write(ctx, (dbyte)slvAdrss, cmd, I2C_MEMADD_SIZE_8BIT, data, (dbyte)len, I2C_TO) == HAL_OK){

	  clearWriteBuf();
	  return HAL_OK;
  }
  else{
#ifdef LOG_EN
      logString("AP: WRITE FAILURE\r\n");
#endif
	  return HAL_ERROR;
  }
}

int i2cApRead(void *ctx, byte cmd, byte* data, size_t len){
   clearReadBuf();
   byte slvAdrss = AP_ADDRESS;
   if( HAL_I2C_Mem_Read(ctx, (dbyte)slvAdrss, cmd, I2C_MEMADD_SIZE_8BIT, data, (dbyte)len, I2C_TO) == HAL_OK ){
	   return HAL_OK;
   }
   else{
 #ifdef LOG_EN
       logString("AP: READ FAILURE\r\n");
 #endif
 	   return HAL_ERROR;
   }
}

void i2cApDelay(void *ctx, qbyte usec){
	(void)ctx;
//	HAL_Delay(usec);
	osDelay(usec);
}


int i2cBqWrite(void *ctx, byte reg, byte* data, size_t len){
  byte slvAdrss = BQ_ADRS;
  if(HAL_I2C_Mem_Write(ctx, (dbyte)slvAdrss, reg, I2C_MEMADD_SIZE_8BIT, data, (dbyte)len, I2C_TO) == HAL_OK){

	  clearWriteBuf();
	  return HAL_OK;
  }
  else{
#ifdef LOG_EN
      logString("BQ: WRITE FAILURE\r\n");
#endif
	  return HAL_ERROR;
  }
}

int i2cBqRead(void *ctx, byte reg, byte* data, size_t len){
   clearReadBuf();
   byte slvAdrss = BQ_ADRS;
   if( HAL_I2C_Mem_Read(ctx, (dbyte)slvAdrss, reg, I2C_MEMADD_SIZE_8BIT, data, (dbyte)len, I2C_TO) == HAL_OK ){
	   return HAL_OK;
   }
   else{
 #ifdef LOG_EN
       logString("BQ: READ FAILURE\r\n");
 #endif
 	   return HAL_ERROR;
   }
}

void i2cBqDelay(void *ctx, qbyte usec){
	(void)ctx;
	osDelay(usec);
}

