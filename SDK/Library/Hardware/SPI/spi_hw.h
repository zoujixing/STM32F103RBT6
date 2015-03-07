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
#ifndef SPI_HW_H_
#define SPI_HW_H_

/* needed include files ----------------------------------------------------- */
#include "stdio.h"
#include "stm32f10x.h"

//SPI_BaudRatePrescaler_2   2分频   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_4   4分频   (SPI 18M@sys 72M)
//SPI_BaudRatePrescaler_8   8分频   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16分频  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_32  32分频  (SPI 2.25M@sys 72M)
//SPI_BaudRatePrescaler_64  64分频  (SPI 1.125M@sys 72M)
//SPI_BaudRatePrescaler_128 128分频 (SPI 562.5K@sys 72M)
//SPI_BaudRatePrescaler_256 256分频 (SPI 281.25K@sys 72M)

/* macro definition --------------------------------------------------------- */
#define SPI_SPEED_2 	0
#define SPI_SPEED_4 	1
#define SPI_SPEED_8 	2
#define SPI_SPEED_16 	3
#define SPI_SPEED_32 	4
#define SPI_SPEED_64 	5
#define SPI_SPEED_128 	6
#define SPI_SPEED_256	7

/* typedef ------------------------------------------------------------------ */


/* global function declare -------------------------------------------------- */

extern void SPI_HW_Init(SPI_InitTypeDef SPI_InitStructure);
extern uint8_t SPI_HW_WRByte(uint8_t dat);
extern void SPI_HW_SetSpeed(uint8_t speed);
#endif

/**************************** END OF FILE *************************************/

