#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include "PWM.h"
#include "24l01.h"
#include "spi.h"
uint8_t host_data[32]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x0d,0x0a},recv_data[2][32]={{0x00,0x01,0x02,0x0d,0x0a},{0x01,0x02,0x03,0x0d,0x0a}};
uint8_t player_data[2][32]={{0xf1,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x0d,0x0a},{0xf5,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x0d,0x0a}};
volatile uint8_t select=0;

int main(void)
{
	uint8_t i=0,j;
	delay_init();
	LED_Init();
	USART1_Init();
	NRF24L01_Init();
	NRF24L01_TX_Mode();
	//NRF24L01_RX_Mode();
	//NRF24L01_Read_Buf(TX_ADDR,buf,5);
	//NRF24L01_Read_Buf(RX_ADDR_P0,buf,5);
	//NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x00);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
//	NRF24L01_Write_Reg(WRITE_REG_NRF+CONFIG,0x7e);
	delay_ms(100);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
  while(1)
	{
		for (select=0;select<2;select++)
		{
			j=0;
			//while(1)
			{
				NRF24L01_TX_Mode();
				//NRF24L01_Read_Buf(TX_ADDR,buf,5);
				i++;i%=10;j++;
				if (!i) LED_TURN;
				if (j==100)break;
			//reg_data=NRF24L01_Read_Reg(0);sta =NRF24L01_Read_Reg(STATUS);
				if (NRF24L01_TxPacket(player_data[select])==TX_OK);// break;
			}//if (!NRF24L01_RxPacket(data)) success=1;
			delay_us(500);
			//reg_data=NRF24L01_Read_Reg(0);
			//sta=NRF24L01_Read_Reg(STATUS);fifo_sta=NRF24L01_Read_Reg(NRF_FIFO_STATUS);
			/*if (!NRF24L01_RxPacket(data)) {
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
				delay_ms(100);
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
			}*/
			LED_ON;
			NRF24L01_RX_Mode();
			delay_ms(10);
			//if (success) delay_ms(100);
			//while(1)
				if (!NRF24L01_RxPacket(recv_data[select])) 
				{
					LED_ON;
					USART_SendData(USART1,select);
					for (i=0;i<4;i++)
					{
						USART_SendData(USART1,recv_data[select][i]);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
					}
				}
			else LED_OFF;
			delay_ms(30);
			}
		//for (reg_addr=0;reg_addr<0x1E;reg_addr++)
		//	reg_data=NRF24L01_Read_Reg(reg_addr);
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
