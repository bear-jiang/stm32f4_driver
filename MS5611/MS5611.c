#include "MS5611.h"
uint16_t ms5611_prom[PROM_NB];
Baro baro;
void MS5611_Init(void)
{
	int i,j;
	MS5611_Reset();
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++)
		{

		}
	}
	// MS5611_Read_Prom();
	MS5611_Start_P();
	return ;
}

void MS5611_Reset(void)
{
    IIC_Write_1Byte(MS5611_ADDR, CMD_RESET, 1);
}

void MS5611_Start_P(void)
{
	IIC_Write_1Byte(MS5611_ADDR, CMD_ADC_CONV + CMD_ADC_D1 + MS5611_OSR, 1); // D1 (pressure) conversion start!
}

void MS5611_Start_T(void)
{
	IIC_Write_1Byte(MS5611_ADDR, CMD_ADC_CONV + CMD_ADC_D2 + MS5611_OSR, 1); // D2 (temperature) conversion start!
}

void MS5611_Read_Adc_P(void)
{
	IIC_Read_nByte(MS5611_ADDR, CMD_ADC_READ, 3, baro.p);
	MS5611_Start_P();
	return;
}

void MS5611_Read_Adc_T(void)
{
	IIC_Read_nByte( MS5611_ADDR, CMD_ADC_READ, 3, baro.t); // read ADC
	MS5611_Start_T();
	return;
}
// uint8_t MS5611_Read_Prom(void)
// {
// 	uint8_t rxbuf[2] = { 0, 0 };
// 	// uint8_t check = 0;
// 	uint8_t i;

// 	for (i = 0; i < PROM_NB; i++)
// 	{
// 		I2C1_MultiRead(MS5611_ADDR, CMD_PROM_RD + i * 2, rxbuf,2); // send PROM READ command
// 		ms5611_prom[i] = rxbuf[0] << 8 | rxbuf[1];
// 	}

// 	// if(check==PROM_NB)
// 	// 	return 1;
// 	// else
// 		return 0;
// }
