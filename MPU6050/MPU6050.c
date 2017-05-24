#include "MPU6050.h"
#define ACC_FSR 16.0
#define GYRO_FSR 2000.0
Gyro gyro;
Acc acc;
void I2C_Delay()
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<10;j++)
		{

		}
	}
	return;
}


// void I2C1_Init()
// {
// 	I2C_InitTypeDef I2C_MPU6050;
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); 
	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
// 	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);

// 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
// 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

// 	I2C_StructInit(&I2C_MPU6050);
// 	I2C_MPU6050.I2C_ClockSpeed=100000;
// 	I2C_MPU6050.I2C_Mode=I2C_Mode_I2C;
// 	I2C_MPU6050.I2C_DutyCycle=I2C_DutyCycle_16_9;
// 	I2C_MPU6050.I2C_OwnAddress1=0;
// 	I2C_MPU6050.I2C_Ack=I2C_Ack_Enable;
// 	I2C_MPU6050.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
// 	I2C_Init(I2C1,&I2C_MPU6050);

// 	I2C_Cmd(I2C1,ENABLE);
// 	I2C_AcknowledgeConfig(I2C1,ENABLE); 
// 	return;
// }
 
// void I2C1_Write(uint8_t addr,uint8_t reg,uint8_t data)
// {
// 	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
// 	I2C_GenerateSTART(I2C1,ENABLE);
// 	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
// 	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Transmitter);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
// 	I2C_SendData(I2C1,reg);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
// 	I2C_SendData(I2C1,data);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
// 	I2C_GenerateSTOP(I2C1,ENABLE);
// 	// I2C_Delay();
// }

// uint8_t I2C1_Read(uint8_t addr,uint8_t reg)
// {
// 	uint8_t data;
// 	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
// 	I2C_GenerateSTART(I2C1,ENABLE);
// 	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
// 	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Transmitter);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
// 	I2C_Cmd(I2C1, ENABLE);
// 	I2C_SendData(I2C1,reg);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
// 	I2C_GenerateSTART(I2C1,ENABLE);
// 	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));


// 	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Receiver);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
// 	I2C_AcknowledgeConfig(I2C1,DISABLE);
// 	I2C_GenerateSTOP(I2C1,ENABLE);
// 	// I2C_SendData(I2C1,reg);
// 	//while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
// 	// I2C_SendData(I2C1,data);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
// 	data=I2C_ReceiveData(I2C1);
// 	I2C_AcknowledgeConfig(I2C1,ENABLE);
// 	// I2C_GenerateSTOP(I2C1,ENABLE);
// 	// I2C_Delay();
// 	return data;
// }

// void I2C1_MultiRead(uint8_t addr,uint8_t reg,uint8_t* buffer,uint8_t num)
// {
// 	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
// 	I2C_GenerateSTART(I2C1,ENABLE);
// 	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
// 	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Transmitter);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
// 	I2C_Cmd(I2C1, ENABLE);
// 	I2C_SendData(I2C1,reg);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
// 	I2C_GenerateSTART(I2C1,ENABLE);
// 	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
// 	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Receiver);
// 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
// 	I2C_AcknowledgeConfig(I2C1,ENABLE);
//  	while(num>0)
//  	{
// 		I2C_AcknowledgeConfig(I2C1,DISABLE);
// 		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
// 		*buffer=I2C_ReceiveData(I2C1);
// 		num--;
// 		buffer++;
// 	}
// 	I2C_AcknowledgeConfig(I2C1,DISABLE);
// 	I2C_GenerateSTOP(I2C1,ENABLE);
// 	// I2C_AcknowledgeConfig(I2C1,ENABLE);
// 	return;
// }

void MPU6050SetSampleRate(uint16_t hz)
{
	IIC_Write_1Byte(MPU_ADDR,MPU_SAMPLE_RATE_REG,1000/hz - 1);
}

uint8_t MPU6050Init()
{
	uint8_t res;
	IIC_Write_1Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0X80);		//Reset MPU6050
	I2C_Delay();
	IIC_Write_1Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0X00);
	IIC_Write_1Byte(MPU_ADDR,MPU_CFG_REG,0x03);				//DLPF = 5Hz 0x06
	MPU6050SetSampleRate(1000);							//Sample rate = 1000Hz
	IIC_Write_1Byte(MPU_ADDR,MPU_GYRO_CFG_REG,0x18);			//Full Scale Range = 2000
	IIC_Write_1Byte(MPU_ADDR,MPU_ACCEL_CFG_REG,0x18);		//Full Scale Range = 16g
	IIC_Write_1Byte(MPU_ADDR,MPU_USER_CTRL_REG,0x00);		//Disable Master mode
	IIC_Write_1Byte(MPU_ADDR,MPU_INTBP_CFG_REG,0x02);		//Enable Bypass mode
	
	IIC_Read_1Byte(MPU_ADDR,MPU_DEVICE_ID_REG,&res);		//Read MPU6050's address
	if(res=MPU_ADDR)
	{
		IIC_Write_1Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0X01);
	}
	else
	{
		return -1;
	}

	return 0;

}

void MPU6050GetGyro(Gyro *gyro)
{
	uint8_t data_1,data_2;
	IIC_Read_1Byte(MPU_ADDR,MPU_GYRO_XOUTH_REG,&data_1);
	IIC_Read_1Byte(MPU_ADDR,MPU_GYRO_XOUTL_REG,&data_2);
	gyro->x_data = (float)((int16_t)(data_1<<8|data_2))*GYRO_FSR/32768;
	IIC_Read_1Byte(MPU_ADDR,MPU_GYRO_YOUTH_REG,&data_1);
	IIC_Read_1Byte(MPU_ADDR,MPU_GYRO_YOUTL_REG,&data_2);
	gyro->y_data = (float)((int16_t)(data_1<<8|data_2))*GYRO_FSR/32768;
	IIC_Read_1Byte(MPU_ADDR,MPU_GYRO_ZOUTH_REG,&data_1);
	IIC_Read_1Byte(MPU_ADDR,MPU_GYRO_ZOUTL_REG,&data_2);
	gyro->z_data = (float)((int16_t)(data_1<<8|data_2))*GYRO_FSR/32768;
}
void MPU6050GetAcc(Acc *acc)
{
	uint8_t data_1,data_2;
	IIC_Read_1Byte(MPU_ADDR,MPU_ACCEL_XOUTH_REG,&data_1);
	IIC_Read_1Byte(MPU_ADDR,MPU_ACCEL_XOUTL_REG,&data_2);
	acc->x_data = (float)((int16_t)(data_1<<8|data_2))*ACC_FSR/32768;
	IIC_Read_1Byte(MPU_ADDR,MPU_ACCEL_YOUTH_REG,&data_1);
	IIC_Read_1Byte(MPU_ADDR,MPU_ACCEL_YOUTL_REG,&data_2);
	acc->y_data = (float)((int16_t)(data_1<<8|data_2))*ACC_FSR/32768;
	IIC_Read_1Byte(MPU_ADDR,MPU_ACCEL_ZOUTH_REG,&data_1);
	IIC_Read_1Byte(MPU_ADDR,MPU_ACCEL_ZOUTL_REG,&data_2);
	acc->z_data = (float)((int16_t)(data_1<<8|data_2))*ACC_FSR/32768;

}
