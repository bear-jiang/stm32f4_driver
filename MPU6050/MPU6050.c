#include <MPU6050.h>


void delay()
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++)
		{

		}
	}
	return;
}


void I2C1_Init()
{
	I2C_InitTypeDef I2C_MPU6050;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

	I2C_StructInit(&I2C_MPU6050);
	I2C_MPU6050.I2C_ClockSpeed=100000;
	I2C_MPU6050.I2C_Mode=I2C_Mode_I2C;
	I2C_MPU6050.I2C_DutyCycle=I2C_DutyCycle_16_9;
	I2C_MPU6050.I2C_OwnAddress1=0;
	I2C_MPU6050.I2C_Ack=I2C_Ack_Enable;
	I2C_MPU6050.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1,&I2C_MPU6050);

	I2C_Cmd(I2C1,ENABLE);
	I2C_AcknowledgeConfig(I2C1,ENABLE); 
	return;
}

void MPU6050Write(uint8_t addr,uint8_t reg,uint8_t data)
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C1,reg);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1,data);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C1,ENABLE);
}

uint8_t MPU6050Read(uint8_t addr,uint8_t reg)
{
	uint8_t data;
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_Cmd(I2C1, ENABLE);
	I2C_SendData(I2C1,reg);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));


	I2C_Send7bitAddress(I2C1,addr<<1,I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	I2C_AcknowledgeConfig(I2C1,DISABLE);
	I2C_GenerateSTOP(I2C1,ENABLE);
	// I2C_SendData(I2C1,reg);
	//while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	// I2C_SendData(I2C1,data);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data=I2C_ReceiveData(I2C1);
	I2C_AcknowledgeConfig(I2C1,ENABLE);
	// I2C_GenerateSTOP(I2C1,ENABLE);
	return data;
}

void MPU6050SetSampleRate(uint16_t hz)
{
	MPU6050Write(MPU_ADDR,MPU_SAMPLE_RATE_REG,1000/hz - 1);
}

void MPU6050Init()
{
	// MPU6050Write(MPU6050_RA_SMPLRT_DIV,0x80);
	MPU6050Write(MPU_ADDR,MPU_PWR_MGMT1_REG,0X80);
	MPU6050Write(MPU_ADDR,MPU_PWR_MGMT1_REG,0X01);
	delay();
	MPU6050Write(MPU_ADDR,MPU_CFG_REG,0x03);
	MPU6050SetSampleRate(1000);
	MPU6050Write(MPU_ADDR,MPU_GYRO_CFG_REG,0x18);
	MPU6050Write(MPU_ADDR,MPU_ACCEL_CFG_REG,0x08);

	return;

}

