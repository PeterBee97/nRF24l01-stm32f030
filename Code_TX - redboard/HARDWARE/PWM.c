#include "stm32f0xx.h"
#include "PWM.h"
#include "led.h"
void TIM3_PWM_Init(uint16_t period, uint16_t prescaler)
{ 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能定时器3时钟
    TIM_TimeBaseStructure.TIM_Period        = period;// 设置自动重装周期值
    TIM_TimeBaseStructure.TIM_Prescaler     = prescaler;//设置预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    //初始化定时器3
    
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;// PWM2模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;//输出高
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能预装载寄存器
    TIM_Cmd(TIM3, ENABLE);                          //  使能定时器3
}
