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
#include "TFTLCD.h"
#include "adc.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */
uint16_t value;

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
	
	ADC1_PinInit(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	ADC1_Init();
	TFTLCD_Init();
	TFTLCD_PrintString(20, 20, (uint8_t *)"The ADC Value is...");
	while(1)
	{	
		TFTLCD_PrintString(20, 40, (uint8_t *)"Channel_0 :");
		value =  ADC1_GetValue(ADC_Channel_0);
		TFTLCD_PrintUint16(20,60, value, DEC);
		
		TFTLCD_PrintString(20, 80, (uint8_t *)"Channel_1 :");
		value =  ADC1_GetValue(ADC_Channel_1);
		TFTLCD_PrintUint16(20,100, value, DEC);		
		Delayms(1000);
	}
}

/**************************** END OF FILE *************************************/

