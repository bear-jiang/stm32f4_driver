#ifndef _USART_H__
#define _USART_H__
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"
#include "misc.h"
#include <stdio.h>
#include <stdarg.h>
void USART1_Init(u32 bound);
void USART1_Send(uint8_t data);
void USART1_IRQHandler(void);
void ValueProtocalPrint(char* p,uint8_t size,uint8_t id);
extern uint32_t thisRxLenth;
#endif
