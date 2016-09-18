#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include "PWM.h"
#include "24l01.h"
#include "spi.h"
uint8_t data[8],reg_addr,reg_data,sta,fifo_sta,buf[5];

int main(void)
{
	uint8_t success;
	delay_init();
	LED_Init();
	USART1_Init();
	NRF24L01_Init();
	//NRF24L01_TX_Mode();
	NRF24L01_RX_Mode();
	//delay_ms(1);
	//delay_us(130);
	//NRF24L01_Read_Buf(TX_ADDR,buf,5);
	//NRF24L01_Read_Buf(RX_ADDR_P0,buf,5);
	//NRF24L01_Read_Buf(RX_ADDR_P1,buf,5);
	//NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x00);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
//	NRF24L01_Write_Reg(WRITE_REG_NRF+CONFIG,0x7e);
//	delay_ms(1);
//	reg_data=NRF24L01_Read_Reg(0);sta=NRF24L01_Read_Reg(STATUS);
  while(1){
		
		success=0;
		reg_data=NRF24L01_Read_Reg(9);sta=NRF24L01_Read_Reg(STATUS);
		//if (NRF24L01_TxPacket(data)==TX_OK) success=1;
		while(1) 
		{
			//NRF24L01_CE_CLR;delay_us(10);
			NRF24L01_CE_SET;delay_us(500);//ÐþÑ§CE
			if (NRF24L01_RxPacket(data)==0) break;	
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
		//if (!NRF24L01_RxPacket(data)) success=1;
		//reg_data=NRF24L01_Read_Reg(0);
		//sta=NRF24L01_Read_Reg(STATUS);fifo_sta=NRF24L01_Read_Reg(NRF_FIFO_STATUS);
		/*if (!NRF24L01_RxPacket(data)) {
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
			delay_ms(100);
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}*/
	//	if (success) GPIO_SetBits(GPIOA,GPIO_Pin_1);
	//	else GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		
	//	if (success) delay_ms(100);
	//	if (success) GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		//else GPIO_SetBits(GPIOA,GPIO_Pin_1);
		//if (success) delay_ms(1000);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		reg_data=NRF24L01_Read_Reg(9);
		//delay_ms(1000);
		/*for (reg_addr=0;reg_addr<0x1E;reg_addr++)
			reg_data=NRF24L01_Read_Reg(reg_addr);*/
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
