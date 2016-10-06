#ifndef __SPI_H
#define __SPI_H
#include "stm32f0xx.h"
#include "../STM32F03x_FWLib/inc/stm32f0xx_spi.h"
//#include "sys.h"
// SPI总线速度设置 	    
#define SPI_SPEED_2   			SPI_BaudRatePrescaler_2				//Fsck=Fpclk/2=36Mhz
#define SPI_SPEED_4   			SPI_BaudRatePrescaler_4				//Fsck=Fpclk/4=18Mhz
#define SPI_SPEED_8   			SPI_BaudRatePrescaler_8				//Fsck=Fpclk/8=9Mhz
#define SPI_SPEED_16  			SPI_BaudRatePrescaler_16			//Fsck=Fpclk/16=4.5Mhz
#define SPI_SPEED_32  			SPI_BaudRatePrescaler_32			//Fsck=Fpclk/32=2.25Mhz
#define SPI_SPEED_64  			SPI_BaudRatePrescaler_64			//Fsck=Fpclk/64=1.125Mhz
#define SPI_SPEED_128 			SPI_BaudRatePrescaler_128			//Fsck=Fpclk/128=562.5Khz
#define SPI_SPEED_256  			SPI_BaudRatePrescaler_256			//Fsck=Fpclk/256=281.25Khz
    													  
void SPI1_Init(void);			 //初始化SPI1口
void SPI1_SetSpeed(uint8_t SpeedSet); //设置SPI1速度   
uint8_t SPI1_ReadWriteByte(uint8_t TxData);//SPI1总线读写一个字节
		 
#endif

