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
#ifndef DMA_H_
#define DMA_H_

/* needed include files ----------------------------------------------------- */
#include "stdio.h"
#include "stm32f10x.h"
/* macro definition --------------------------------------------------------- */


/* typedef ------------------------------------------------------------------ */

typedef enum{
	DMA_1 = 0,
	DMA_2 = 1
}DMA_Typedef;


typedef struct{
	
	DMA_Typedef 			DMA_Type;
	DMA_Channel_TypeDef 	*DMA_CHx;
	DMA_InitTypeDef 		DMA_Config_s;

}DMA_Struct_t;


/* global function declare -------------------------------------------------- */

extern void DMA_IRQConfig(DMA_Channel_TypeDef *DMA_CHx, uint8_t IRQn, uint32_t irq_mode);
extern void DMA_Config(DMA_Struct_t DMA_InitStruct);
extern void DMA_Enable(DMA_Channel_TypeDef *DMA_CHx);
extern void DMA_Disable(DMA_Channel_TypeDef *DMA_CHx);
#endif

/**************************** END OF FILE *************************************/
