#include "AK8975.h"
Mag mag;
void AK8975Enable()
{
	IIC_Write_1Byte(AK8975_ADDRESS,AK8975_CNTL,0x01);
}
uint8_t AK8975Init()
{
	uint8_t res;
	AK8975Enable();
	IIC_Read_1Byte(AK8975_ADDRESS,AK8975_WIA,&res);
	if(res==0x48)
		return 0;
	else
		return 1;
}
void GetMag(Mag* mag)
{
	uint8_t res;
	IIC_Read_1Byte(AK8975_ADDRESS,AK8975_ST1,&res);
	if(res==0x01)
	{
		uint8_t data_1,data_2;
		IIC_Read_1Byte(AK8975_ADDRESS,AK8975_HXL,&data_1);
		IIC_Read_1Byte(AK8975_ADDRESS,AK8975_HXH,&data_2);
		mag->x_data = (int16_t)(data_1<<8|data_2);
		IIC_Read_1Byte(AK8975_ADDRESS,AK8975_HYL,&data_1);
		IIC_Read_1Byte(AK8975_ADDRESS,AK8975_HYH,&data_2);
		mag->y_data = (int16_t)(data_1<<8|data_2);
		IIC_Read_1Byte(AK8975_ADDRESS,AK8975_HZL,&data_1);
		IIC_Read_1Byte(AK8975_ADDRESS,AK8975_HZH,&data_2);
		mag->z_data = (int16_t)(data_1<<8|data_2);
		AK8975Enable();
	}
}


