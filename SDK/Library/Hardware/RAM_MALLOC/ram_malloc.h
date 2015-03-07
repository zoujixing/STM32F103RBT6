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
#ifndef RAM_MALLOC_H_
#define RAM_MALLOC_H_

/* needed include files ----------------------------------------------------- */
#include "stdint.h"
#include "stdio.h"

/* macro definition --------------------------------------------------------- */

#define MEMORY_MAX_SIZE		10*1024
#define MEMORY_BLOCK_SIZE	32
#define MEMORY_BLOCK_NUM	(MEMORY_MAX_SIZE/MEMORY_BLOCK_SIZE)

/* typedef ------------------------------------------------------------------ */

typedef struct{
	
	uint8_t 	memory_ready;
	uint32_t 	*memory_block_map;
	uint8_t 	*memory_base_map;
	
}memory_dev_t;

/* global function declare -------------------------------------------------- */

void 	MEMORY_Init							(void);
void 	*MEMORY_Malloc						(uint32_t size);
void 	MEMORY_Free							(void *ptr);
void 	*MEMORY_ReMalloc					(void *ptr, uint32_t size);
 
uint8_t MEMORY_GetUtilizationRate			(void);

#endif

/**************************** END OF FILE *************************************/
