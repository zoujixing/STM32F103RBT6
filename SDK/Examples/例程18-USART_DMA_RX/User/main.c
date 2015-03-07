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
#include "stm32f10x.h"
#include <string.h>
#include "delay.h"
#include "system.h"
#include "usart.h"
#include "dma.h"

#define RX_BUF_MAX	16
#define RX_BUF_1	0
#define RX_BUF_2	1

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */
DMA_Struct_t DMA_struct;

static uint8_t rx_finish = 0;
static uint8_t buf_num=RX_BUF_1;

static uint8_t rx_buf[2][RX_BUF_MAX];
/* local function prototypes ------------------------------------------------ */
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void DMA_ParametersSet()
{	
	DMA_struct.DMA_Type = DMA_1;
	DMA_struct.DMA_CHx = DMA1_Channel5;
	//Set address
	DMA_struct.DMA_Config_s.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	
	DMA_struct.DMA_Config_s.DMA_MemoryBaseAddr = (uint32_t)( &(rx_buf[buf_num][0]) );
	buf_num++;
	if(buf_num >= 2)
		buf_num = 0;
	//Set transmission direction
	//Peripheral to memory
	DMA_struct.DMA_Config_s.DMA_DIR = DMA_DIR_PeripheralSRC;
	//Set buffer size
	DMA_struct.DMA_Config_s.DMA_BufferSize = RX_BUF_MAX;
	//address increase 
	DMA_struct.DMA_Config_s.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_struct.DMA_Config_s.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//Set data size
	DMA_struct.DMA_Config_s.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_struct.DMA_Config_s.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	//Set mode
	DMA_struct.DMA_Config_s.DMA_Mode = DMA_Mode_Normal;
	//Set priority
	DMA_struct.DMA_Config_s.DMA_Priority = DMA_Priority_Medium;
	//disable memory to memery
	DMA_struct.DMA_Config_s.DMA_M2M =  DMA_M2M_Disable;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
	if( DMA_GetITStatus(DMA1_IT_TC5) != RESET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TC5);
		DMA_DeInit(DMA1_Channel5);
		
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
	}
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void IRQHandler()
{	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		//clear RX_IRQ and set IDLE_IRQ
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
		//Initialize DMA for usart1 rx
		DMA_ParametersSet();
		DMA_Config(DMA_struct);
		DMA_IRQConfig(DMA1_Channel5, DMA1_Channel5_IRQn, DMA_IT_TC);
		DMA_Enable(DMA1_Channel5);
    } 
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  
	{	
		//finished
		USART_ClearITPendingBit(USART1, USART_IT_IDLE);
		DMA_Cmd(DMA1_Channel5, DISABLE);  
		
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);	
		rx_finish = 1;
    } 
}
/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
int main(void)
{	
	SystemInit();
	Delay_init(72);
	NVIC_Configuration();
	
	USART1_IRQHandlerRegist(IRQHandler);
	USART1_Init(9600);
	
	while(1)
	{	
		if(rx_finish == 1)
		{	
			rx_finish = 0;
			USART1_PrintBuff( &(rx_buf[0][0]), RX_BUF_MAX);
			USART1_PrintBuff( &(rx_buf[1][0]), RX_BUF_MAX);
			memset(&(rx_buf[0][0]), 0x00, RX_BUF_MAX );
			memset(&(rx_buf[1][0]), 0x00, RX_BUF_MAX );
		}
	}
}

/**************************** END OF FILE *************************************/

