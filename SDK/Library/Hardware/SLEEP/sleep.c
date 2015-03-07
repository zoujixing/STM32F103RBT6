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
#include "sleep.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void SLEEP_EnterStandby(void)
{	
	uint32_t RCC_APB2Periph;
	
	RCC_APB2Periph = RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC| \
					 RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF| \
					 RCC_APB2Periph_GPIOG;
	//关闭IO口
	RCC_APB2PeriphResetCmd(RCC_APB2Periph,DISABLE);
	NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP,ENABLE);	 
	//使能PWR和BKP外设时钟    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	
	//使能唤醒管脚功能
	PWR_WakeUpPinCmd(ENABLE);  
	//进入待命（STANDBY）模式 	
	PWR_EnterSTANDBYMode();	  
}


/**************************** END OF FILE *************************************/
