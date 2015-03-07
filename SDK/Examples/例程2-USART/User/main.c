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

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */

uint8_t len, tx_len;
uint8_t buf[36];
/* local function prototypes ------------------------------------------------ */


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
	USART1_Init(9600);
	while(1)
	{	
		//Delayms(100);
		//UART1_PrintChar(0x55);
		//UART1_PrintBuff(buf, 6);
		//UART1_PrintString("string...");
		len = USART1_RxAvailable();
		if(  len > 0 ) 
		{
			tx_len = USART1_ReadRxBUF(buf, len);
			USART1_PrintBuff(buf, tx_len);
		}
	}
}

/**************************** END OF FILE *************************************/

