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
#include "rtc.h"
#include "TFTLCD.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */
uint8_t count=1, count2=1;

/* local function prototypes ------------------------------------------------ */
/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void sec_handle()
{
	uint32_t value_H, value_L;
	
	TFTLCD_PrintString(20, 40 , (uint8_t *)"the cont is...");
	value_H = RTC_GetCounter();
	value_L = (uint16_t)value_H;
	value_H = (uint16_t)(value_H>>16);
	TFTLCD_PrintUint16(20, 60, value_H, DEC);
	TFTLCD_PrintUint16(60, 60, value_L, DEC);
}
/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void alarm_handle()
{
	TFTLCD_PrintString(20, 80 , (uint8_t *)"the alarm is...");
	TFTLCD_PrintUint16(20, 100, count, DEC);
	count++;
	if(count != 3)
		RTC_SetCountValue(0);
	if(count == 3)
		RTC_SetCountValue(0xFFFFFFF0);
	
	RTC_SetAlarmValue(40);
}
/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void ow_handle()
{	
	count2 = 1;
	TFTLCD_PrintString(20, 120 , (uint8_t *)"the ow is...");
	TFTLCD_PrintUint16(20, 140, count2, DEC);
	TFTLCD_ClearRow(60);
	
	count2++;
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
	USART1_Init(9600);
	Delay_init(72);
	NVIC_Configuration();
	
	TFTLCD_Init();
	TFTLCD_SetColor(RED, WHITE);
	TFTLCD_SetDisplaySize(12);
	
	RTC_InitIRQHandle(sec_handle, alarm_handle, ow_handle);
	RTC_Init(32768, 30, 10);
	
	TFTLCD_PrintString(20, 20 ,  (uint8_t *)"start...");
	while(1)
	{	
		
	}
}

/**************************** END OF FILE *************************************/

