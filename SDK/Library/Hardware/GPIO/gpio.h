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
#ifndef _GPIO_H_
#define _GPIO_H_

/* needed include files ----------------------------------------------------- */
#include "stm32f10x.h"

/* macro definition --------------------------------------------------------- */

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作
#define GPIOA_Pin_Output(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define GPIOA_Pin_Input(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define GPIOB_Pin_Output(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define GPIOB_Pin_Input(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define GPIOC_Pin_Output(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define GPIOC_Pin_Input(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define GPIOD_Pin_Output(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define GPIOD_Pin_Input(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define GPIOE_Pin_Output(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define GPIOE_Pin_Input(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define GPIOF_Pin_Output(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define GPIOF_Pin_Input(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define GPIOG_Pin_Output(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define GPIOG_Pin_Input(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

typedef enum
{
	LOW = 0,
	HIGH
	
}Polarity_t;

/* typedef ------------------------------------------------------------------ */


/* global function declare -------------------------------------------------- */

void GPIO_ClockEnable(uint32_t port);
void GPIO_ConfigOutput(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode);
void GPIO_ConfigInput(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, GPIOMode_TypeDef mode);

#endif

/**************************** END OF FILE *************************************/

