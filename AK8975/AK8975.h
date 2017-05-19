#ifndef _AK8975__H_
#define _AK8975__H_
#include <MPU6050/MPU6050.h>

#define AK8975_ADDRESS         0x0c	// 0x18

#define AK8975_WIA     0x00
#define AK8975_ST1     0x02
#define AK8975_HXL     0x03
#define AK8975_HXH     0x04
#define AK8975_HYL     0x05
#define AK8975_HYH     0x06
#define AK8975_HZL     0x07
#define AK8975_HZH     0x08
#define AK8975_CNTL    0x0A

typedef struct{
	int16_t x_data;
	int16_t y_data;
	int16_t z_data;
}Mag;
extern Mag mag;
void AK8975Enable();
void GetMag(Mag* mag);
uint8_t AK8975Init();


#endif
