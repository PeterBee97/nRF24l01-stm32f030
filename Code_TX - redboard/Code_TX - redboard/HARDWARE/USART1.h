
#ifndef _USART1_H
#define _USART1_H

#include "stm32f0xx.h"
#include <stdio.h>
#define DATA_LENGTH 18

void USART1_Init(void);
extern uint8_t host_data[DATA_LENGTH];
#endif
