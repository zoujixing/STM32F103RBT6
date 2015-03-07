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
#include "ram_malloc.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
int main(void)
{	
	uint8_t rate;
	uint32_t *p1, *p2;
	
	Delay_init(72);
	NVIC_Configuration();
	USART1_Init(9600);
	
	Delayms(5000);
	USART1_PrintString("Start \r\n");
	MEMORY_Init();
	p1 = MEMORY_Malloc(1000);
	p2 = MEMORY_Malloc(1000);
	rate = MEMORY_GetUtilizationRate();
	
	USART1_PrintString("Point is:");
	USART1_PrintfInt((uint32_t)p1);
	USART1_PrintfInt((uint32_t)p2);
	USART1_PrintString("Rate is:");
	USART1_PrintfInt(rate);
	
	MEMORY_Free(p1);
	MEMORY_Free(p2);
	rate = MEMORY_GetUtilizationRate();
	USART1_PrintString("Rate is:");
	USART1_PrintfInt(rate);	

	while(1)
	{	
		
	}
}

/**************************** END OF FILE *************************************/

