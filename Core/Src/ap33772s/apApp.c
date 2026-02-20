/*
 * apApp.c
 *
 *  Created on: Dec 17, 2025
 *      Author: Dell
 */

#include "apApp.h"

struct ap_bus_delegate apbus = {
    .read = i2cApRead,
    .write = i2cApWrite,
    .delay_us = i2cApDelay,
    .ctx = &hi2c1
};


