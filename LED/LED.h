#ifndef _LED_H__
#define _LED_H__
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#define LED_GREEN_ON() GPIO_SetBits(GPIOE,GPIO_Pin_3)
#define LED_GREEN_OFF() GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define LED_RED_ON() GPIO_SetBits(GPIOG,GPIO_Pin_14)
#define LED_RED_OFF() GPIO_ResetBits(GPIOG,GPIO_Pin_14)
void LED_TOGGLE();
void LED_Init();

#endif