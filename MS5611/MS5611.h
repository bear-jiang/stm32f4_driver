#ifndef _MS5661__H_
#define _MS5661__H_

#include <I2C_Soft/I2C_Soft.h>

#define MS5611_ADDR             0x77   

#define CMD_RESET               0x1E // ADC reset command
#define CMD_ADC_READ            0x00 // ADC read command
#define CMD_ADC_CONV            0x40 // ADC conversion command
#define CMD_ADC_D1              0x00 // ADC D1 conversion
#define CMD_ADC_D2              0x10 // ADC D2 conversion
#define CMD_ADC_256             0x00 // ADC OSR=256
#define CMD_ADC_512             0x02 // ADC OSR=512
#define CMD_ADC_1024            0x04 // ADC OSR=1024
#define CMD_ADC_2048            0x06 // ADC OSR=2048
#define CMD_ADC_4096            0x08 // ADC OSR=4096
#define CMD_PROM_RD             0xA0 // Prom read command
#define PROM_NB                 8
#define MS5611_OSR							0x08	

typedef struct
{
	uint8_t p[3];
	uint8_t t[3];	
}Baro;
extern Baro baro;
void MS5611_Init(void);
void MS5611_Reset(void);
void MS5611_Start_P(void);
void MS5611_Read_Adc_P(void);
uint8_t MS5611_Read_Prom(void);
#endif
