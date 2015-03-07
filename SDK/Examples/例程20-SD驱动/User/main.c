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
#include "gpio.h"
#include "spi_hw.h"
#include "SD.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */

uint8_t dat;
uint16_t n;
uint32_t sector_num;

uint8_t buf[1024];
uint8_t buf1[512] = {1,2,3,4,5,6,7};
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
	
	Delayms(5000);
	while( SD_Initialize() != 0 )
	{
		USART1_PrintString("SD Initialize Fail \r\n");
	}
	USART1_PrintString("SD Initialize OK \r\n");
	sector_num = SD_GetSectorNum();
	USART1_PrintString("The SD sector num is:    ");
	USART1_PrintChar(sector_num>>24);
	USART1_PrintChar(sector_num>>16);
	USART1_PrintChar(sector_num>>8);
	USART1_PrintChar(sector_num>>0);
	USART1_PrintString("\r\n");
	USART1_PrintString("The SD size is:    ");
	sector_num >>= 12;
	USART1_PrintChar(sector_num>>24);
	USART1_PrintChar(sector_num>>16);
	USART1_PrintChar(sector_num>>8);
	USART1_PrintChar(sector_num>>0);
	
	if( 0 == SD_WriteDisk(buf1, 1, 1) )
	{
		USART1_PrintString("Write OK \r\n");
	}
	while(1)
	{	
		Delayms(4000);
		if(0 == SD_ReadDisk(buf,0,2))
		{
			for(n=0; n<1024; n++)
			{
				USART1_PrintChar(buf[n]);
			}
		}
	}
}

/**************************** END OF FILE *************************************/

