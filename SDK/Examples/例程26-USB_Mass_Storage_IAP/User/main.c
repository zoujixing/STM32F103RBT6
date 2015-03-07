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
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"

#include "gpio.h"
#include "iap_load.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */

/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
int main(void)
{	
	GPIO_ClockEnable(RCC_APB2Periph_GPIOC);
	
	GPIO_ConfigInput(GPIOC, GPIO_Pin_7, GPIO_Mode_IPU);
	GPIO_ConfigOutput(GPIOC, GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
	
	GPIOC_Pin_Output(9) = 0;
	
	if(0x01 == GPIOC_Pin_Input(7) )
	{
		GPIOC_Pin_Output(9) = 1;
		if(((*(uint32_t*)(FLASH_APP_ADDR+4))&0xFF000000)==0x08000000)
		{
			iap_load_app(FLASH_APP_ADDR);
		}
	}
	
	NVIC_Configuration();
	
	Set_System();
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
	
	while(1)
	{
		
	}
}

/**************************** END OF FILE *************************************/

