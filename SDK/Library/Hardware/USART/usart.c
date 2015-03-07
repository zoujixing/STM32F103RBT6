/*******************************************************************************
File Name	 	  :  
Author   	 	  :  
Software Revision :  

Description	 	  :  

Copyright (c) 2013 ZOZ technology 

The software is released by ZOZ technology.The software is mainly used for learning 
and testing.The software is provided "AS IS", without warranty of any kind, express 
or implied. Your use of this software is completely free of charge. You can use it 
without any limitation,e.g.,transplantation,delete,modify,copy,merge and spreadit. 
At the same time, using of this software means that you agree to bear any direct or 
indirect liability and loss brought by this software.

You can visit www.zozstudio.com to submit your qustions or get more available 
informations about this software.
*******************************************************************************/

/* include files ------------------------------------------------------------ */
#include "usart.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */
uint8_t RX_Buff[RX_BUFF_MAX];
uint8_t rx_head = 0, rx_tail = 0;

/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void USART1_Init(uint32_t bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
   
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
   
    USART_Cmd(USART1, ENABLE);

	rx_head = 0;
	rx_tail = 0;
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void USART1_PrintChar(uint8_t c)
{	
	USART1->SR &= ~0x00000040;	
	USART1->DR = c;  
	while( (USART1->SR&0X40) == 0 )
	{
		//do nothing
	}	
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void USART1_PrintfInt(uint32_t dat)
{
	const uint8_t ASCII[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	USART1_PrintChar('0');
	USART1_PrintChar('x');
	if(dat <= 0xFF)
	{
		USART1_PrintChar(ASCII[dat>>4&0x0F]);
		USART1_PrintChar(ASCII[dat&0x0F]);
	}
	else if(dat <= 0xFFFF)
	{
		USART1_PrintChar(ASCII[dat>>12&0x0F]);
		USART1_PrintChar(ASCII[dat>>8&0X0F]);			
		USART1_PrintChar(ASCII[dat>>4&0x0F]);
		USART1_PrintChar(ASCII[dat&0x0F]);		
	}
	else if(dat <= 0xFFFFFF)
	{
		USART1_PrintChar(ASCII[dat>>20&0x0F]);
		USART1_PrintChar(ASCII[dat>>16&0X0F]);			
		USART1_PrintChar(ASCII[dat>>12&0x0F]);
		USART1_PrintChar(ASCII[dat>>8&0X0F]);			
		USART1_PrintChar(ASCII[dat>>4&0x0F]);
		USART1_PrintChar(ASCII[dat&0x0F]);			
	}
	else if(dat <= 0xFFFFFFFF)
	{
		USART1_PrintChar(ASCII[dat>>28&0x0F]);
		USART1_PrintChar(ASCII[dat>>24&0X0F]);				
		USART1_PrintChar(ASCII[dat>>20&0x0F]);
		USART1_PrintChar(ASCII[dat>>16&0X0F]);			
		USART1_PrintChar(ASCII[dat>>12&0x0F]);
		USART1_PrintChar(ASCII[dat>>8&0X0F]);			
		USART1_PrintChar(ASCII[dat>>4&0x0F]);
		USART1_PrintChar(ASCII[dat&0x0F]);		
	}
	USART1_PrintChar('\r');	
	USART1_PrintChar('\n');	
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void USART1_PrintBuff(uint8_t *pbuf, uint16_t len)
{	
	uint16_t index;
	
	for(index=0; index<len; index++)
	{
		USART1_PrintChar(pbuf[index]);
	}
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void USART1_PrintString(char *pstring)
{
	while(*pstring != '\0')
	{
		USART1_PrintChar(*pstring);
		pstring++;
	}
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
uint8_t USART1_RxAvailable()
{
	return (( RX_BUFF_MAX + rx_head - rx_tail) % RX_BUFF_MAX );
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
uint8_t USART1_ReadRxChar()
{
	uint8_t rx_data;
	
	rx_data = RX_Buff[rx_tail++];
	if( rx_tail >= RX_BUFF_MAX )
	{
		rx_tail = 0;
	}
	
	return rx_data;
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
uint8_t USART1_ReadRxBUF(uint8_t *pbuf, uint8_t len)
{
	uint8_t buf_len, index;
	
	buf_len = ( RX_BUFF_MAX + rx_head - rx_tail) % RX_BUFF_MAX;
	if(len > buf_len)
	{
		len = buf_len;
	}
	
	for(index=0; index<len; index++)
	{
		pbuf[index] = RX_Buff[rx_tail++];
		if(rx_tail >= RX_BUFF_MAX)
		{
			rx_tail = 0;
		}
	}
	
	return len;
}

/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	uint8_t rx_data;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		rx_data = USART_ReceiveData(USART1);//(USART1->DR);	
		RX_Buff[rx_head++] =  rx_data;
		if(rx_head >= RX_BUFF_MAX)
		{
			rx_head = 0;
		}
    } 
} 
