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
#include "wwdg.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */

static uint8_t wwdg_pre_count=0x7F;
/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void WWDG_Init(uint32_t prescale, uint8_t pre_count, uint8_t window_dat)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); 

	WWDG_SetPrescaler(prescale);
	WWDG_SetWindowValue(window_dat);
	WWDG_Enable(pre_count);	              
	wwdg_pre_count = pre_count;
	WWDG_ClearFlag();

	
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);

	WWDG_EnableIT(); 
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(wwdg_pre_count);	  //禁止此句，将复位
	WWDG_ClearFlag();	  
	//可在此设置LED翻转标志
	GPIOA_Pin_Output(8) = ~GPIOA_Pin_Output(8);
}
/**************************** END OF FILE *************************************/
