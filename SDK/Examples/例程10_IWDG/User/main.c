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
#include "iwdg.h"
#include "gpio.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */

int count=0;
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
	GPIO_ClockEnable(RCC_APB2Periph_GPIOA );
	GPIO_ConfigOutput(GPIOA, GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_IPU);
	GPIOA_Pin_Output(8) = 0;
	Delayms(500);
	GPIOA_Pin_Output(8) = 1;
	Delayms(500);
	GPIOA_Pin_Output(8) = 0;
	Delayms(500);	
	IWDG_Init(IWDG_Prescaler_64,625);
	while(1)
	{	
		IWDG_Feed();//屏蔽此举， 将不断复位
		Delayms(10);
	}
}

/**************************** END OF FILE *************************************/

