#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include "PWM.h"
#include "24l01.h"
#include "spi.h"
#define DATA_LENGTH 18
#define PLAYER_DATA_LENGTH 4
uint8_t host_data[DATA_LENGTH]={0xF0,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0D,0x0A},start=0,reg_addr,reg_data,sta,fifo_sta,buf[5];
uint8_t player_data[2][DATA_LENGTH]={{0xF0,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0D,0x0A},{0xF0,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0D,0x0A}};
uint8_t recv_data[2][PLAYER_DATA_LENGTH]={{0x00,0x00,0x0d,0x0a},{0x00,0x00,0x0d,0x0a}};
uint8_t select=0;
int main(void)
{
	uint8_t i;
	delay_init();
	LED_Init();
	USART1_Init();
	NRF24L01_Init();
	NRF24L01_TX_Mode();

	delay_ms(100);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
  while(1){
		
		//reg_data=NRF24L01_Read_Reg(0);sta =NRF24L01_Read_Reg(STATUS);
		for (select=1;select<3;select++)
		{
			NRF24L01_TX_Mode();
			if (NRF24L01_TxPacket(player_data[select-1],DATA_LENGTH)==TX_OK)
			{
				LED_ON;
				NRF24L01_RX_Mode();
				NRF24L01_CE_SET;delay_us(500);//玄学CE
				while(NRF24L01_RxPacket(recv_data[select-1],PLAYER_DATA_LENGTH)){}; 
					if (host_data[select-1]&0x20)//选手有飞机控制权则持续发送选手最后一次发送的数据
						for (i=0;i<PLAYER_DATA_LENGTH;i++)
						{
							USART_SendData(USART1,recv_data[select-1][i]);
							while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
						}
			}
			else LED_OFF;
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
