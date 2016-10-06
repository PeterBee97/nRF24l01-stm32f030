#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include "PWM.h"
#include "24l01.h"
#include "spi.h"
#define DATA_LENGTH 18
#define PLAYER_DATA_LENGTH 4
uint8_t data[32]={0x2b,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};//,buf[5];
uint8_t player_data[32]={0x00,0x00,0x0D,0x0A};
volatile uint8_t select=0;
uint8_t in_game=0,j=0;
int main(void)
{
	uint8_t i;
	delay_init();
	LED_Init();
	USART1_Init();
	NRF24L01_Init();
	//NRF24L01_TX_Mode();
	NRF24L01_RX_Mode();
	LED_ON;	delay_ms(400);	LED_OFF;	delay_ms(400);//start signal
	select=(((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)^1)<<1 | GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)^1)+3)%4;
	for (i=0;i<select;i++) {LED_ON;	delay_ms(50);	LED_OFF;	delay_ms(150);} //blink to confirm ID
	delay_ms(500);
	//NRF24L01_Read_Buf(TX_ADDR,buf,5);
	//NRF24L01_Read_Buf(RX_ADDR_P0,buf,5);
	//NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x00);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
//	NRF24L01_Write_Reg(WRITE_REG_NRF+CONFIG,0x7e);
	//delay_ms(100);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
while(1)
	{
		select=(((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)^1)<<1 | GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)^1)+3)%4;
		//if (NRF24L01_TxPacket(data)==TX_OK) success=1;
		while(1) 
		{
			//NRF24L01_CE_CLR;delay_us(10);
			NRF24L01_RX_Mode();
			//NRF24L01_Read_Buf(RX_ADDR_P0,buf,5);
			NRF24L01_CE_SET;delay_us(500);//ÐþÑ§CE
			if (NRF24L01_RxPacket(data)==0) {delay_ms(1);break;}	
			LED_OFF;
		}
		NRF24L01_TX_Mode();
	
		//NRF24L01_Read_Buf(TX_ADDR,buf,5);
		delay_ms(1);
		if (NRF24L01_TxPacket(player_data)==TX_OK) 
		{
			if (in_game || !j) LED_ON;
			else LED_OFF;
			j++;j%=5;
		}
		for (i=0;i<DATA_LENGTH;i++)
			{
					USART_SendData(USART1,data[i]);
					while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
			}
		delay_ms(1);
		if ((data[0]&3)!=0x01)
		{	
			STOP_CAR;
			in_game=0;
		}
		else
		{	
			RUN_CAR;
			in_game=1;
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
