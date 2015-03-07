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
#include "flash.h"
#include "TFTLCD.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */

uint8_t write_buf[20] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0};
uint8_t read_buf[20];
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
	
	Delayms(2000);
	TFTLCD_PrintString(20, 20 , (uint8_t *)"FLASH START");
	TFTLCD_PrintString(20, 40 , (uint8_t *)"FLASH Erase");
	FLASH_PageErase(0x8006000);
	TFTLCD_PrintString(20, 60 , (uint8_t *)"FLASH Write");
	FLASH_PageWrite(0x8006000, write_buf, 20);

	while(1)
	{	
		TFTLCD_PrintString(20, 80 , (uint8_t *)"The ReadOut Buf is ...");
		Flash_PageRead(0x8006000, read_buf, 20);
		USART1_PrintBuff(read_buf, 20);
		
		Delayms(2000);
	}
}

/**************************** END OF FILE *************************************/

