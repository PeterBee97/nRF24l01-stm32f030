#ifndef _PWM_H
#define _PWM_H
#include "stm32f0xx.h"
typedef    unsigned short int     INT16U;
typedef    unsigned char          INT8U;
void TIM3_PWM_Init(INT16U period, INT16U prescaler);
#endif
