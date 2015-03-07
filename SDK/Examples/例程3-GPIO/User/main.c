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
#include "GPIO.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* ��������������
* ��  �ܣ�	
* ��  ����
* ��  �أ�	
*******************************************************************************/
int main(void)
{	
	SystemInit();
	Delay_init(72);
	NVIC_Configuration();
	GPIO_ClockEnable(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD);
	GPIO_ConfigOutput(GPIOA, GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
	GPIO_ConfigOutput(GPIOD, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
	while(1)
	{	
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		Delayms(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		Delayms(500);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		Delayms(500);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
		Delayms(500);			
	}
}

/**************************** END OF FILE *************************************/

