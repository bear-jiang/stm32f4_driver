#include "AK8975.h"
Mag mag;
void AK8975Enable()
{
	I2C1_Write(AK8975_ADDRESS,AK8975_CNTL,0x01);
}
uint8_t AK8975Init()
{
	AK8975Enable();
	if(I2C1_Read(AK8975_ADDRESS,AK8975_WIA)==0x48)
	{
		AK8975Enable();
		return 0;
	}
	else
	{
		return 1;
	}
}
void GetMag(Mag* mag)
{
	if(I2C1_Read(AK8975_ADDRESS,AK8975_ST1)==0x01)
	{
		uint8_t data_1,data_2;
		data_1=I2C1_Read(AK8975_ADDRESS,AK8975_HXL);
		data_2=I2C1_Read(AK8975_ADDRESS,AK8975_HXH);
		mag->x_data = (int16_t)(data_1<<8|data_2);
		data_1=I2C1_Read(AK8975_ADDRESS,AK8975_HYL);
		data_2=I2C1_Read(AK8975_ADDRESS,AK8975_HYH);
		mag->y_data = (int16_t)(data_1<<8|data_2);
		data_1=I2C1_Read(AK8975_ADDRESS,AK8975_HZL);
		data_2=I2C1_Read(AK8975_ADDRESS,AK8975_HZH);
		mag->z_data = (int16_t)(data_1<<8|data_2);
		AK8975Enable();
	}
}


