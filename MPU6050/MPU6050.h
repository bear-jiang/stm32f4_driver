#ifndef _MPU6050_H__
#define _MPU6050_H__
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_i2c.h"

#define MPU_ADDR				0X68

void MPU6050Init();
void I2C1_Init();
uint8_t MPU6050Read(uint8_t reg);
#endif
