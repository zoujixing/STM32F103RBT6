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
#ifndef RTC_H_
#define RTC_H_

/* needed include files ----------------------------------------------------- */
#include "stm32f10x.h"
#include "delay.h"
#include <stdio.h> 
/* macro definition --------------------------------------------------------- */


/* typedef ------------------------------------------------------------------ */
typedef void(*rtc_irq_handle)();

/* global function declare -------------------------------------------------- */

uint8_t RTC_Init(uint32_t pre_value, uint32_t alarm_value, uint32_t count_value);
void RTC_InitIRQHandle(rtc_irq_handle sec_handle, rtc_irq_handle alrf_hanle, rtc_irq_handle ow_hanle);
void RTC_SetAlarmValue(uint32_t value);
void RTC_SetCountValue(uint32_t value);
#endif

/**************************** END OF FILE *************************************/
