
#ifndef _USART1_H
#define _USART1_H

#include "stm32f0xx.h"
#include <stdio.h>
#define PLAYER_DATA_LENGTH 4
extern uint8_t player_data[32];
void USART1_Init(void);

#endif
