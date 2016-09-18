#include "stm32f0xx.h"
#include "PWM.h"
#include "led.h"
void TIM3_PWM_Init(uint16_t period, uint16_t prescaler)
{ 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ�ܶ�ʱ��3ʱ��
    TIM_TimeBaseStructure.TIM_Period        = period;// �����Զ���װ����ֵ
    TIM_TimeBaseStructure.TIM_Prescaler     = prescaler;//����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//����ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    //��ʼ����ʱ��3
    
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;// PWM2ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;//�����
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
    TIM_Cmd(TIM3, ENABLE);                          //  ʹ�ܶ�ʱ��3
}
