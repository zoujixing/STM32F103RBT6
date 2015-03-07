
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
#ifndef __USART_H
#define __USART_H

/* needed include files ----------------------------------------------------- */
#include "stdio.h"
#include "stm32f10x.h"
/* macro definition --------------------------------------------------------- */


/* typedef ------------------------------------------------------------------ */
#define RX_BUFF_MAX 36

/* global function declare -------------------------------------------------- */

void USART1_Init(uint32_t bound);
void USART1_PrintChar(uint8_t c);
void USART1_PrintfInt(uint32_t dat);
void USART1_PrintBuff(uint8_t *pbuf, uint16_t len);
void USART1_PrintString(char *pstring);

uint8_t USART1_RxAvailable(void);
uint8_t USART1_ReadRxChar(void);
uint8_t USART1_ReadRxBUF(uint8_t *pbuf, uint8_t len);

#endif

