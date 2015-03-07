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
#include "gpio.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */
/*******************************************************************************
* 函数名：
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
    Delayms(20);    
  	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	  
	{	  
		GPIOA_Pin_Output(8) = ~GPIOA_Pin_Output(8);
	}
	EXTI_ClearITPendingBit(EXTI_Line0); 
}
/*******************************************************************************
* 函数名：
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  	Delayms(20);   			 
 
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
	 	GPIOD_Pin_Output(2) = ~GPIOD_Pin_Output(2);
	}
    else if (EXTI_GetITStatus(EXTI_Line15) != RESET)
	{
		GPIOD_Pin_Output(2) = ~GPIOD_Pin_Output(2);
		GPIOA_Pin_Output(8) = ~GPIOA_Pin_Output(8);
	}
	EXTI_ClearITPendingBit(EXTI_Line13);  
	EXTI_ClearITPendingBit(EXTI_Line15);  
}	
/*******************************************************************************
* 函数名：
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void EX_INTERRUPT_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;	
	//disable JTAG
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource13);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	
	//
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 
 	//
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	
	
	//
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 
  
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure);  	
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
	Delay_init(72);
	NVIC_Configuration();
	GPIO_ClockEnable(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD);
	GPIO_ConfigOutput(GPIOA, GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_IPU);
	GPIO_ConfigOutput(GPIOD, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_IPU);
	EX_INTERRUPT_Init();
	while(1)
	{	
		//do nothing
	}
}

/**************************** END OF FILE *************************************/

