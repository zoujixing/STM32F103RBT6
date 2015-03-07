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
#include "gpio.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ��:port: RCC_APB2Periph_GPIOx
* ��    ��:	
*******************************************************************************/
void GPIO_ClockEnable(uint32_t port)
{
	RCC_APB2PeriphClockCmd(port , ENABLE);
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ��: *GPIO: GPIOx 
*			GPIO_Pin:GPIO_Pin_x

* ��    ��:	
*******************************************************************************/
void GPIO_ConfigOutput(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = speed;
	GPIO_InitStructure.GPIO_Mode = mode;
	
	GPIO_Init(GPIO, &GPIO_InitStructure);
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ��:
* ��    ��:	
*******************************************************************************/
void GPIO_ConfigInput(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = mode;
	
	GPIO_Init(GPIO, &GPIO_InitStructure);	

}

/**************************** END OF FILE *************************************/

