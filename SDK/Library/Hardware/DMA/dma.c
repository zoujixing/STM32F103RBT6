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
#include "dma.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void DMA_IRQConfig(DMA_Channel_TypeDef *DMA_CHx, uint8_t IRQn, uint32_t irq_mode)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	DMA_Cmd(DMA_CHx, DISABLE );      
    NVIC_InitStructure.NVIC_IRQChannel = IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);		

	DMA_ITConfig(DMA_CHx, irq_mode, ENABLE);	
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void DMA_Config(DMA_Struct_t DMA_InitStruct)
{	
	//Enable DMA1
	if(DMA_InitStruct.DMA_Type == DMA_1)
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	
	else if(DMA_InitStruct.DMA_Type == DMA_2)
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);	
	else
		return;
	//Clear setting
	DMA_DeInit(DMA_InitStruct.DMA_CHx);
	//Initialize 
	DMA_Init(DMA_InitStruct.DMA_CHx, &DMA_InitStruct.DMA_Config_s); 

}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void DMA_Enable(DMA_Channel_TypeDef *DMA_CHx)
{
 	DMA_Cmd(DMA_CHx, ENABLE);  	
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void DMA_Disable(DMA_Channel_TypeDef *DMA_CHx)
{
 	DMA_Cmd(DMA_CHx, DISABLE);  	
}

/**************************** END OF FILE *************************************/

