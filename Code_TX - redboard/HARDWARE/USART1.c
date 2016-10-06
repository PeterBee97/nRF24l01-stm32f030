//=============================================================================
//文件名称：usart1.c
//功能概要：串口1驱动文件
//版权所有：源地工作室www.vcc-gnd.com
//淘宝网店：http://vcc-gnd.taobao.com
//更新时间：2014-01-04
//=============================================================================

#include "USART1.h"
#include "LED.h"
#include "delay.h"
extern uint8_t select;
uint8_t i=0,j;
extern uint8_t host_data[32],player_data[2][32];
uint8_t temp_data[18];
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{  
	while(!((USART1->ISR)&(1<<7))){}
  USART1->TDR=ch;
  return (ch);
}
#endif 
void update_player_data()
{
	player_data[0][0]=0xF0 | (host_data[0]&0x03);
	player_data[1][0]=0xF4 | (host_data[0]&0x03);
	player_data[0][1]=(host_data[1]&0x03) | (host_data[0]&0xFC);
	player_data[1][1]=host_data[1];
	player_data[0][2]=player_data[1][4]=host_data[2];//player1 X
	player_data[0][3]=player_data[1][5]=host_data[3];//player1 Y
	player_data[0][4]=player_data[1][2]=host_data[4];//player2 X
	player_data[0][5]=player_data[1][3]=host_data[5];//player2 Y
	player_data[0][6]=player_data[1][6]=host_data[6];//target X
	player_data[0][7]=player_data[1][7]=host_data[7];//target Y
	player_data[0][8]=player_data[1][8]=host_data[8];//drone X
	player_data[0][9]=player_data[1][9]=host_data[9];//drone Y
	player_data[0][10]=player_data[1][11]=host_data[10];//player1 HP
	player_data[0][11]=player_data[1][10]=host_data[11];//player2 HP
	player_data[0][12]=player_data[1][12]=host_data[12];//tool X
	player_data[0][13]=player_data[1][13]=host_data[13];//tool Y
	player_data[0][14]=player_data[1][14]=host_data[14];//time LSB
	player_data[0][15]=player_data[1][15]=host_data[15];//tool Type & time MSB
}
void save_byte(uint16_t data)
{
	temp_data[i++]=data;
	if (i==18) i=0; 
	if (temp_data[i]==0x0A)
		if (temp_data[(i+17)%18]==0x0D)
		{
			for (j=0;j<18;j++)
				host_data[j]=temp_data[(i+j+1)%18];
				update_player_data();
			LED_OFF;
		}
}
/* USART初始化 */
void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  //使能GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//使能USART的时钟
	/* USART1的端口配置 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);//配置PA9成第二功能引脚	TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);//配置PA10成第二功能引脚  RX	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	/* USART1的基本配置 */
	USART_InitStructure.USART_BaudRate = 115200;              //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);		
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           //使能接收中断
	USART_Cmd(USART1, ENABLE);                             //使能USART1
	
	/* USART1的NVIC中断配置 */
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x02;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
				
}

//=============================================================================
//文件名称：
//功能概要：USART1中断函数
//参数说明：无
//函数返回：无
//=============================================================================
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		save_byte(USART_ReceiveData(USART1));
	}
			
}
