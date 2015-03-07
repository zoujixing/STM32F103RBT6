/*******************************************************************************
File Name	 	  :  
Author   	 	  :  
Software Revision :  2013-12-21

Description	      :  

Copyright (c) 2013 ZOZ technology 

The software is released by ZOZ technology.The software is mainly used for learning 
and testing.The software is provided "AS IS", without warranty of any kind, express 
or implied. Your use of this software is completely free of charge. You can use it 
without any limitation,e.g.,transplantation,delete,modify,copy,merge and spread it. 
At the same time, using of this software means that you agree to bear any direct or 
indirect liability and loss brought by this software.

You can visit www.zozstudio.com to submit your qustions or get more available 
informations about this software.
*******************************************************************************/

/* prevent from redefinition ------------------------------------------------ */
#ifndef _PWM_H_
#define _PWM_H_

/* needed include files ----------------------------------------------------- */
#include "stm32f10x.h"

/* macro definition --------------------------------------------------------- */


/* typedef ------------------------------------------------------------------ */


/* global function declare -------------------------------------------------- */

void PWM_Init(uint16_t prescaler, uint16_t period);
void PWM_ChannelInit( uint8_t channel, uint8_t Polarity);
void PWM_Start( uint8_t channel, uint8_t duty_cycle );
#endif

/**************************** END OF FILE *************************************/

