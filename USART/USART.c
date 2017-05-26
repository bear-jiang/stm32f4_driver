#include "USART.h"
#include <string.h>
#include <stdio.h>
#define LENGTH 100
static uint8_t _USART1_DMA_RX_BUF[LENGTH];
uint8_t _USART1_DMA_TX_BUF[100];

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
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
/************************config usart1 dma recieve**********************/
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
/************************config usart1 dma send**********************/
    DMA_DeInit(DMA2_Stream7);
    DMA_StructInit(&dma);
    dma.DMA_Channel = DMA_Channel_4;
    dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
    dma.DMA_Memory0BaseAddr = (uint32_t)&_USART1_DMA_TX_BUF[0];
    dma.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    dma.DMA_BufferSize = 0;
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma.DMA_Mode = DMA_Mode_Normal;
    dma.DMA_Priority = DMA_Priority_Medium;
    dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream7, &dma);
/************************config DMA2 Stream7 interrupt**********************/
    // NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9; 
    // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    // NVIC_Init(&NVIC_InitStructure); 
    // DMA_ITConfig(DMA2_Stream7,DMA_IT_TCIF7,ENABLE);

/************************config usart1_rx interrupt**********************/
    nvic.NVIC_IRQChannel = USART1_IRQn;                          
    nvic.NVIC_IRQChannelPreemptionPriority = 0;   //pre-emption priority 
    nvic.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
    nvic.NVIC_IRQChannelCmd = ENABLE;			
    NVIC_Init(&nvic);	
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);       

    USART_Cmd(USART1, ENABLE);
    // BSP_IntVectSet(BSP_INT_ID_USART1,USART1_IRQHandler);
    // BSP_IntPrioSet(BSP_INT_ID_USART1,10);
}

void USART1_DMA_SendBuf(uint8_t *p,uint8_t size)
{
    int i=0;
    memcpy(_USART1_DMA_TX_BUF,p,size);
    DMA2_Stream7->NDTR = (u16)size; 
    DMA_Cmd(DMA2_Stream7, ENABLE);
    while(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7) == RESET);
    DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
    DMA_Cmd(DMA2_Stream7, DISABLE);

}

void ValueProtocalPrint(char* p,uint8_t size,uint8_t id)
{
    static uint8_t count = 0;
    uint8_t buffer[50];
    uint8_t i = 0;
    buffer[0] = 0xfe;
    buffer[1] = size;
    buffer[2] = count;
    buffer[3] = id;
    for(i=0;i<size;i++)
    {
        buffer[4+i] = *(p+i);
    }
    buffer[4+size]=0x0d;
    buffer[4+size+1]=0x0a;
    USART1_DMA_SendBuf(buffer,size+6);
    count++;
}

int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
    USART_SendData(USART1, (uint8_t)ch);
    return ch;
}

void USART1_Send(uint8_t data)
{
    USART_SendData(USART1,data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}



uint32_t thisRxLenth = 0;

void USART1_IRQHandler(void)                	//´®¿Ú1ÖÐ¶Ï·þÎñ³ÌÐò
{

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
}


