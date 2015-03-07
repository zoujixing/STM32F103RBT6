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

IRQ_Handler irq_handler;

uint8_t RX_Buff[RX_BUFF_MAX];
uint8_t rx_head = 0, rx_tail = 0;

/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void USART1_IRQHandlerRegist( IRQ_Handler handler)
{
	if(handler != NULL)
	{
		irq_handler = handler;
	}
}
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
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
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
  
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 
  
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
	
	if( irq_handler!= NULL )
	{
		irq_handler();
	}
} 
