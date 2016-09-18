#ifndef __LED_H
#define __LED_H

#include "stm32f0xx.h"

#define LED_ON                       GPIOB->BSRR = 0x02
#define LED_OFF                      GPIOB->BRR = 0x02 
#define LED_TURN                      GPIOB->ODR ^= 0x02
#define RUN_CAR                       GPIOA->BSRR = 0x01 
#define STOP_CAR                      GPIOA->BRR = 0x01 
void LED_Init(void);

#endif
