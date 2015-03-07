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
#include "delay.h"
#include "system.h"
#include "usart.h"
#include "dma.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */

DMA_Struct_t DMA_struct;

static uint16_t index;
static uint8_t tx_buf[100];

/* local function prototypes ------------------------------------------------ */

/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
*******************************************************************************/
void DMA_ParametersSet()
{
	DMA_struct.DMA_Type = DMA_1;
	DMA_struct.DMA_CHx = DMA1_Channel4;
	//Set address
	DMA_struct.DMA_Config_s.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	DMA_struct.DMA_Config_s.DMA_MemoryBaseAddr = (uint32_t)tx_buf;
	//Set transmission direction
	DMA_struct.DMA_Config_s.DMA_DIR = DMA_DIR_PeripheralDST;
	//Set buffer size
	DMA_struct.DMA_Config_s.DMA_BufferSize = 100;
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
* ��������������
* ��  �ܣ�	
* ��  ����
* ��  �أ�	
*******************************************************************************/
int main(void)
{	
	SystemInit();
	Delay_init(72);
	NVIC_Configuration();
	USART1_Init(9600);
	
	for(index=0; index<100; index++)
		tx_buf[index] = index;
	
	while(1)
	{	
		Delayms(2000);
		USART1_PrintString("\r\n-------------- transform start --------------\r\n");
		DMA_ParametersSet();
		DMA_Config(DMA_struct);
		USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE); 
		DMA_Enable(DMA1_Channel4);
		while(1)
		{
			if(DMA_GetFlagStatus(DMA1_FLAG_TC4) == SET)//�ȴ�ͨ��4�������
			{
				DMA_ClearFlag(DMA1_FLAG_TC4);  //����������
				USART1_PrintString("\r\n -------------- transform completed -------------- \r\n");
				break; 
			}
		}
	}
}

/**************************** END OF FILE *************************************/

