#include "USART.h"
#include <string.h>
#include <stdio.h>
#define LENGTH 1000
static uint8_t _USART1_DMA_RX_BUF[LENGTH];


void USART1_Init(u32 baud_rate)
{
    GPIO_InitTypeDef gpio;
    USART_InitTypeDef usart;
    NVIC_InitTypeDef nvic;
    DMA_InitTypeDef dma;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &gpio);

    USART_DeInit(USART1);
    USART_StructInit(&usart);
    usart.USART_BaudRate = baud_rate;
    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
    usart.USART_Parity = USART_Parity_No;
    usart.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &usart);


    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

    DMA_DeInit(DMA2_Stream2);
    DMA_StructInit(&dma);
    dma.DMA_Channel = DMA_Channel_4;
    dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
    dma.DMA_Memory0BaseAddr = (uint32_t)&_USART1_DMA_RX_BUF[0];
    dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
    dma.DMA_BufferSize = sizeof(_USART1_DMA_RX_BUF);
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma.DMA_Mode = DMA_Mode_Circular;
    dma.DMA_Priority = DMA_Priority_Medium;
    dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream2, &dma);

    DMA_Cmd(DMA2_Stream2, ENABLE);

    nvic.NVIC_IRQChannel = USART1_IRQn;                          
    nvic.NVIC_IRQChannelPreemptionPriority = 0;   //pre-emption priority 
    nvic.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
    nvic.NVIC_IRQChannelCmd = ENABLE;			
    NVIC_Init(&nvic);	

    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);        //usart rx idle interrupt  enabled
    USART_Cmd(USART1, ENABLE);
    // BSP_IntVectSet(BSP_INT_ID_USART1,USART1_IRQHandler);
    // BSP_IntPrioSet(BSP_INT_ID_USART1,10);
}

int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
    USART_SendData(USART1, (uint8_t)ch);
    return ch;
}

void USART1_Send(int8_t data)
{
    USART_SendData(USART1,data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

// void usart1_send_string(int8_t *p, ...)
// {
//     uint8_t *q=p;
//     va_list ap;
//     va_start(ap,p);
//     while(*q!='\0')
//     {
//         if(*q=='%')
//         {
//             switch(*(q+1))
//             {
//                 case 'd':
//                 {
//                     int a=(int)va_arg(ap, int);
//                     int c=10000;
//                     if(a<0)
//                     {
//                         usart1_send('-');
//                         a=-a;
//                     }
//                     while(a/c==0)
//                     {
//                         c/=10;
//                     }
//                     do
//                     {
//                         usart1_send(a/c);
//                         a%=c;
//                         c/=10;
//                     }
//                     while(c!=0);
//                     q+=2;
//                     break;
//                 }
//                 case 'f':break;
//             }
//             continue;
//         }
//         usart1_send(*q);
//         q++;
//     }
//     va_end(ap);
// }

uint32_t thisRxLenth = 0;

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
    TIM_Cmd(TIM6, DISABLE);

    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        //clear the idle pending flag 
        (void)USART1->SR;
        (void)USART1->DR;

        if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
        {
            DMA_Cmd(DMA2_Stream2, DISABLE);
            thisRxLenth = LENGTH - DMA_GetCurrDataCounter(DMA2_Stream2);
            USART1_Send(0xee);

            DMA_Cmd(DMA2_Stream2, ENABLE);
        }
    }     
    TIM_Cmd(TIM6, ENABLE);  
}


