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
#include "delay.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */
unsigned long int SysTick_Count;

/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void SysTick_Handler(void)
{	
	SysTick_Count += 0x1000000UL;
	SysTick_Count &= 0xFFFFFFFFFFFFUL;
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void Delay_init(uint8_t SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	SysTick->LOAD = 0xFFFFFF;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= 0x03;
}

/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
uint32_t micros()
{
	uint32_t _SysTick_Count;
	uint32_t _SysTick_val;
	
	_SysTick_Count = SysTick_Count;
	_SysTick_val = SysTick->VAL;
	
	return ( (0x1000000 - _SysTick_val + _SysTick_Count)/9 );
}

/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
uint32_t millis()
{
	uint32_t start_time;
	
	start_time = micros();
	
	return (start_time/1000);
}
/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void Delayms(uint16_t ms)
{
	uint32_t start_time, end_time;

	start_time = millis();
	end_time = start_time;
	while( (end_time - start_time) < ms || end_time < start_time )
	{
		end_time = millis();
	}	
}

/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void Delayus(uint16_t us)
{
	uint32_t start_time, end_time;

	start_time = micros();
	end_time = start_time;
	while( (end_time - start_time) < us || end_time < start_time )
	{
		end_time = micros();
	}
}

/*******************************************************************************
* 函数名：	
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
__asm int Delay_us(uint32_t usec)
{
     ALIGN
     PUSH.W {r1}  
     MOV r1,#18  
     MUL r0,r1  
     SUB r0,#3  
loop
     SUBS r0,#1   
     BNE loop  
     POP {r1}   
     BX lr    
}
/**************************** END OF FILE *************************************/












	
	
































