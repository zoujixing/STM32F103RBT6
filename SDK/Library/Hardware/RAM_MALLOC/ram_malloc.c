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
#include "ram_malloc.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */

__align(4) uint8_t  memory_base[MEMORY_MAX_SIZE];		
__align(4) uint32_t memory_block[MEMORY_BLOCK_NUM];		/*if set 1, this block is used*/

memory_dev_t memory_dev =  
{
	0,					/*memory_ready*/
	memory_block,		/*memory_block_map*/
	memory_base,		/*memory_base_map*/
};

/* local function prototypes ------------------------------------------------ */

/*******************************************************************************
* @brief 					:	
* @note 					:	
* @param[in]  des			: point of purpose address 
* @param[in]  src			: point of source address 
* @param[in]  num			: num of data to be copied
* @param[out] none 			:	
* @return 	  none			:
*******************************************************************************/
void MEMORY_Copy(void *des, void *src, uint32_t num)
{
	uint8_t *xdes, *xsrc;
	
	xdes = des;
	xsrc = src;
	while(num--)
		*xdes++ = *xsrc++;
}
/*******************************************************************************
* @brief 					:	
* @note 					:	
* @param[in]  des			: point of purpose address 
* @param[in]  dat			: the dat to be set
* @param[in]  num			: num of data to be set
* @param[out] none 			:	
* @return 	  none			:
*******************************************************************************/
void MEMORY_Set(void *des, uint8_t dat, uint32_t num)
{
	uint8_t *xdes;
	
	xdes = des;
	while(num--)
		*xdes++ = dat;
}
/*******************************************************************************
* @brief 					:	initialize MEMORY
* @note 					:	if memory_ready is 0xA0, means MEMORY is initialized
*								if memory_block_map is 1, means this block is used
* @param[in]  none			:
* @param[out] none 			:
* @return 	  none			:
*******************************************************************************/
void MEMORY_Init()
{
	MEMORY_Set(memory_dev.memory_base_map, 0, MEMORY_MAX_SIZE);
	MEMORY_Set(memory_dev.memory_block_map, 0, MEMORY_BLOCK_NUM);
	memory_dev.memory_ready = 0xA0;
}

/*******************************************************************************
* @brief 					:	Get utilization rate of MEMORY
* @note 					:	Percentage format
* @param[in]  none			:
* @param[out] none 			:
* @return 	  				:	utilization rate
*******************************************************************************/
uint8_t MEMORY_GetUtilizationRate()
{
	uint32_t index, used;
	
	used = 0;
	for(index=0; index<MEMORY_BLOCK_NUM; index++)
	{
		if(memory_dev.memory_block_map[index])
		{
			used++;
		}
	}
	
	return (used*100/MEMORY_BLOCK_NUM);
}

/*******************************************************************************
* @brief 					:	fine a free RAM for size
* @note 					:	
* @param[in]  size			:	size of apply memory
* @param[out] none 			:
* @return 0xFFFFFFFF		:	apply fail
*		  else      		:	point of the RAM 
*******************************************************************************/
uint32_t MEMORY_FindFree(uint32_t size)
{
	uint32_t block_size;
	uint32_t free_block_size;
	int32_t  offset;
	uint32_t index;
	/*Check whether memory_dev is ready*/
	if(memory_dev.memory_ready != 0xA0)
	{
		MEMORY_Init();
	}
	/*Check whether the size is zero*/
	if(0 == size)
	{
		return 0xFFFFFFFF;
	}
	/*Calculate request blocks*/
	block_size = size / MEMORY_BLOCK_SIZE;
	if(size % MEMORY_BLOCK_SIZE)
	{
		block_size++;
	}
	/*Fine a continuous and available RAM*/
	free_block_size = 0;
	for(offset=MEMORY_BLOCK_NUM-1; offset>=0; offset--)
	{	
		if(memory_dev.memory_block_map[offset] == 0)
		{
			free_block_size++;
		}
		else
		{
			free_block_size = 0;
		}
		/*If fine a available blocks, return offset address*/
		if(free_block_size == block_size)
		{
			for(index=0; index<block_size; index++)
			{
				memory_dev.memory_block_map[offset+index] = block_size;
			}
			return (offset*MEMORY_BLOCK_SIZE);
		}
	}
	//no enough space
	return 0xFFFFFFFF;
}

/*******************************************************************************
* @brief 					:	free the used block
* @note 					:	
* @param[in]  offset		:	offset from base address
* @param[out] none 			:
* @return 	  0x00			:	success
*		  	  0x01      	:	fail 
*******************************************************************************/
uint8_t MEMORY_FreeBlock(uint32_t offset)
{
	uint32_t start_block;
	uint32_t block_number;
	uint32_t index;
	/*Check whether memory_dev is ready*/
	if(memory_dev.memory_ready != 0xA0)
	{	
		MEMORY_Init();
		return 0x01;
	}
	/**/
	if(offset < MEMORY_MAX_SIZE)
	{	
		start_block = offset / MEMORY_BLOCK_SIZE;
		block_number = memory_dev.memory_block_map[start_block];
		for(index=0; index<block_number; index++)
		{	
			memory_dev.memory_block_map[start_block+index] = 0x00;
		}
		return 0x00;
	}
	return 0x01;
}
/*******************************************************************************
* @brief 					:	Request a space
* @note 					:	
* @param[in]  				:	size of request space
* @param[out] none 			:
* @return 					:	request fail
*		  		      		:	point of the first address  
*******************************************************************************/
void *MEMORY_Malloc(uint32_t size)
{
	uint32_t offset;
	
	offset = MEMORY_FindFree(size);
	if(offset == 0xFFFFFFFF)
		return NULL;
	else
		return ( (void *)( (uint32_t)memory_dev.memory_base_map + offset) );
}

/*******************************************************************************
* @brief 					:	free the used ram, 
* @note 					:	
* @param[in]  address		:	the ram address
* @param[out] none 			:
* @return 	  none			:	
*******************************************************************************/
void MEMORY_Free(void *ptr)
{
	uint32_t offset;
	
	if(ptr == NULL)
	{
		return;
	}
	else
	{
		offset = (uint32_t)ptr - (uint32_t)memory_dev.memory_base_map;
		MEMORY_FreeBlock(offset);
	}	
}

/*******************************************************************************
* @brief 					:	Reallocate memory
* @note 					:	
* @param[in]  *ptr			:	Pointer to be allocated memory
*			  size			:	size of allocated memory
* @param[out] none 			:
* @return 	  pointer		:	Pointer of new memory
*******************************************************************************/
void *MEMORY_ReMalloc(void *ptr, uint32_t size)
{
	uint32_t offset;
	
	offset = MEMORY_FindFree(size);
	if(offset == 0xFFFFFFFF)
	{
		return NULL;
	}
	else
	{
		MEMORY_Copy( (void *)(memory_dev.memory_base_map + offset), ptr, size);
		MEMORY_Free(ptr);
		return ( (void *)(memory_dev.memory_base_map + offset) );
	}
}

/**************************** END OF FILE *************************************/
