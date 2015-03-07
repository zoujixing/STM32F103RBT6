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
//#include "TFTLCD.h"
#include "usart.h"

#include "TFTLCD.h"
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
	SystemInit();
	USART1_Init(9600);
	Delay_init(72);
	NVIC_Configuration();
	
	TFTLCD_Init();
	TFTLCD_SetColor(RED, WHITE);
	TFTLCD_SetDisplaySize(12);

	while(1)
	{	Delayms(1000);
		TFTLCD_PrintChar(30,0, 'b');
		Delayms(1000);
		TFTLCD_PrintChar(30,20, 'A');
		Delayms(1000);
		TFTLCD_SetDisplaySize(16);
		TFTLCD_PrintChar(30,40, 'A');
		Delayms(1000);	
		TFTLCD_PrintString(30, 60, (uint8_t*)"ZOZSTUDIO501111111111111111111111111111111111111111111111111");
		Delayms(1000);	
		TFTLCD_PrintUint16(30, 80, 1, DEC);
		TFTLCD_PrintUint16(30, 100, 65534, HEX);
	}
}

/**************************** END OF FILE *************************************/

