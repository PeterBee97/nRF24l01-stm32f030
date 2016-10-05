#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include "PWM.h"
#include "24l01.h"
#include "spi.h"
#define DATA_LENGTH 32
#define PLAYER_DATA_LENGTH 4
uint8_t data[8]={0x2b,0x23,0x45,0x67,0x89,0xab,0xcd,0xef},reg_addr,reg_data,sta,fifo_sta,buf[5];
uint8_t player_data;
volatile uint8_t select=0;
int main(void)
{
	uint8_t success;
	delay_init();
	LED_Init();
	USART1_Init();
	NRF24L01_Init();
	//NRF24L01_TX_Mode();
	NRF24L01_RX_Mode();
	LED_ON;	delay_ms(50);	LED_OFF;	delay_ms(150);
	LED_ON;	delay_ms(50);	LED_OFF;	delay_ms(150);
	LED_ON;	delay_ms(50);	LED_OFF;	delay_ms(150);//blink 3 times on start
	//NRF24L01_Read_Buf(TX_ADDR,buf,5);
	//NRF24L01_Read_Buf(RX_ADDR_P0,buf,5);
	//NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x00);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
//	NRF24L01_Write_Reg(WRITE_REG_NRF+CONFIG,0x7e);
	//delay_ms(100);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
while(1)
	{
		//if (NRF24L01_TxPacket(data)==TX_OK) success=1;
		while(1) 
		{
			//NRF24L01_CE_CLR;delay_us(10);
			NRF24L01_RX_Mode();
			NRF24L01_CE_SET;delay_us(500);//ÐþÑ§CE
			if (NRF24L01_RxPacket(data,DATA_LENGTH)==0) break;	
			LED_OFF;
		}
		NRF24L01_TX_Mode();
		if (NRF24L01_TxPacket(data,DATA_LENGTH)==TX_OK) {success=1;LED_ON;}
		delay_ms(10);
		USART_SendData(USART1,data[0]);
		if (data[0]==0x2b) GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		else
		{	
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
			LED_ON;
		}
	}
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
