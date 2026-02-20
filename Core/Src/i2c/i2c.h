/*
 * i2c.h
 *
 *  Created on: Oct 4, 2025
 *  Author: moshte
 */

#ifndef I2C_H
#define I2C_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "type.h"
#include "log.h"
#include "ap33772s.h"
#include "bq25798.h"

#include <stdint.h>
#include <stddef.h>


#define READ_BUFF_LEN 50
#define WRITE_BUFF_LEN 6

#define I2C_TO HAL_MAX_DELAY

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

extern byte readBuf[READ_BUFF_LEN];
extern byte writeBuf[WRITE_BUFF_LEN];

/***************************************************GENERAL FUNCTIONS******************************************************/

/**
 * @brief: Clear write buffer
 */
extern void clearWriteBuf(void);

/**
 * @brief: Clear read buffer
 */
extern void clearReadBuf(void);

/**********************************AP33772S WRITE AND READ I2C FUNCTIONS*********************************************************/
/**
 * @brief: Writes t0 AP33772S registers via I2c
 * @param: ctx - Device context
 * @param: cmd - Operation specific command
 * @param: data - Array to be written
 * @param: len - Length of the data array
 *
 * @return: HAL status of the transaction. HAL_OK or HAL_ERORR
 */
extern int i2cApWrite(void *ctx, byte cmd, byte* data, size_t len);

/**
 * @brief: Reads from AP33772S registers via I2c
 * @param: ctx - Device context
 * @param: cmd - Operation specific command
 * @param: data - Pointer to the buffer when data will be stored
 * @param: len - Expected length of the read data array
 *
 * @return: HAL status of the transaction. HAL_OK or HAL_ERORR
 */
extern int i2cApRead(void *ctx, byte cmd, byte* data, size_t len);


/**
 * @brief: A delay function for the AP33772s
 * @param: Device context
 * @param: Delay time in microseconds
 */
extern void i2cApDelay(void *ctx, qbyte usec);

/**********************************BQ25790 WRITE AND READ I2C FUNCTIONS**********************************************************/
/**
 * @brief Write a value to a register via I2C
 *
 * @param: slvAdrss - device address
 * @param: regAdrss -  register address to write to
 * @param: data -  data to be written in @ref reg
 * @param: dlen - length of @ref data
 *
 * @return: HAL status of the transaction. HAL_OK or HAL_ERORR
 */
int i2cBqWrite(void *ctx, byte reg, byte* data, size_t len);

/**
 * @brief Read a register value via I2C
 *
 * @param: slvAdrss - device address
 * @param: regAdrss- register address to read from
 * @param: p - pointer to where the read data is stored. readBuf can be passed here
 * @param: len - Expected length of the read data array
 *
 * @return: HAL status of the transaction. HAL_OK or HAL_ERORR
 */
int i2cBqRead(void *ctx, byte reg, byte* data, size_t len);


void i2cBqDelay(void *ctx, qbyte usec);
#endif /* I2C_H */
