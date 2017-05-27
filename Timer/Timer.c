#include "Timer.h"
void TIM6_Init(void (*func)(void))
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    
    nvic.NVIC_IRQChannel = TIM6_DAC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    tim.TIM_Prescaler = 84-1;        //84M internal clock
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 5000;  //1ms,1000Hz
    TIM_TimeBaseInit(TIM6,&tim);

    TIM_Cmd(TIM6, ENABLE);   
    if(func==0)
    {
        TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);
    }
    else
    {
        (*func)();
    }
}

void TIM6_Start(void)
{
    TIM_Cmd(TIM6, ENABLE);   
    TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);   
}

void TIM6_DAC_IRQHandler(void)  
{
    
    if (TIM_GetITStatus(TIM6,TIM_IT_Update)!= RESET) 
    {
        static uint16_t count=0;
        TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
        TIM_ClearFlag(TIM6, TIM_FLAG_Update);
        
        // USART1_Send(0x0c);
    }
}
