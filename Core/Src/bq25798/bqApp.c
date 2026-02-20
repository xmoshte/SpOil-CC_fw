/*
 * bqApp.c
 *
 *  Created on: Feb 19, 2026
 *      Author: Dell
 */

#include "bqApp.h"

struct bq_bus_delegate bqbus = {
    .read = i2cBqRead,
    .write = i2cBqWrite,
    .delay_us = i2cBqDelay,
    .ctx = &hi2c2
};
