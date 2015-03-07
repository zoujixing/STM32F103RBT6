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
* 函数名：
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
uint16_t Temp_Get()
{	
	uint8_t index;
	uint16_t value, max_value, min_value;
	uint32_t total_value;
	
	value =  ADC1_GetValue(ADC_Channel_TempSensor);
	max_value = value;
	min_value = value;
	total_value = value;
	for(index=0; index<19; index++)
	{
		value = ADC1_GetValue(ADC_Channel_TempSensor);
		if(value > max_value)
			max_value = value;
		if(value < min_value)
			min_value = value;
		total_value += value;	
		
		Delayms(20);
	}
	
	return ((total_value - max_value - min_value) / 18);
}
/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
int main(void)
{	
	float temperature;
	
	SystemInit();
	Delay_init(72);
	NVIC_Configuration();
	
	ADC1_PinInit(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	ADC1_Init();
	TFTLCD_Init();
	TFTLCD_PrintString(20, 20, (uint8_t *)"The Temperature is...");
	while(1)
	{	
		value =  Temp_Get();
		TFTLCD_PrintUint16(20,40, value, DEC);
		temperature = (float)value*(3.3/4096);
		temperature=(1.43-temperature)/0.0043+25;
		
		TFTLCD_PrintUint16(20,60, (uint8_t)temperature, DEC);
		temperature -= (uint8_t)temperature;
		TFTLCD_PrintString(36, 60, (uint8_t *)".");
		TFTLCD_PrintUint16(40,60, temperature*100, DEC);
		Delayms(1000);
	}
}

/**************************** END OF FILE *************************************/

