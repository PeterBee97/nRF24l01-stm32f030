#ifndef __LED_H
#define __LED_H

#include "stm32f0xx.h"

#define LED_ON                       GPIOB->BSRR = 0x02
#define LED_OFF                        GPIOB->BRR = 0x02 
#define LED_TURN                      GPIOB->ODR ^= 0x02

void LED_Init(void);

#endif
