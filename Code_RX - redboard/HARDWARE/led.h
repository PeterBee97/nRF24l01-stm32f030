#ifndef __LED_H
#define __LED_H

#include "stm32f0xx.h"

#define LED_ON                       GPIOB->BSRR = GPIO_Pin_1
#define LED_OFF                      GPIOB->BRR = GPIO_Pin_1 
#define LED_TURN                      GPIOB->ODR ^= GPIO_Pin_1
#define RUN_CAR                       GPIOA->BSRR = GPIO_Pin_0 
#define STOP_CAR                      GPIOA->BRR = GPIO_Pin_0
void LED_Init(void);

#endif
