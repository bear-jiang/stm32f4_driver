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
void USART1_Send(int8_t data);
// void usart1_send_string(int8_t *p, ...);
void USART1_IRQHandler(void);
extern uint32_t thisRxLenth;
#endif
