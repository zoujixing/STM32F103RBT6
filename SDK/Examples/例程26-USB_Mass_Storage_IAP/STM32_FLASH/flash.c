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
#include "flash.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
uint32_t FLASH_PageErase(uint32_t page_address)
{	
	uint32_t err_code;
	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	err_code = FLASH_ErasePage(page_address);
	FLASH_Lock();
	
	return err_code;
}

/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
uint32_t FLASH_PageWrite(uint32_t page_address, uint8_t *buf, uint32_t len)
{	
	uint16_t program_value, index=0, jndex, page_num;
	uint32_t err_code, start_addr = page_address;
	
	if((len % 2) != 0)
	{
		return 1;
	}	
	
	page_num = len / FLASH_PAGE_SIZE;
	for(jndex=0; jndex<page_num; jndex++)
	{
		FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
		err_code = FLASH_ErasePage(page_address + FLASH_PAGE_SIZE*jndex);
	}
	
	while(len>0)
	{	
		program_value = buf[index+1];
		program_value = (program_value<<8) + buf[index];
		err_code = FLASH_ProgramHalfWord( start_addr, program_value);
		if(err_code !=FLASH_COMPLETE)
		{
			return 1;
		}
		start_addr += 2;
		index += 2;
		len -= 2;
		//FLASH_WaitForLastOperation(0x00002000);
	}

	return 0;
}

/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
uint32_t Flash_PageRead(uint32_t page_address, uint8_t *buf, uint32_t len)
{	
	uint32_t index;
	uint32_t start_addr = page_address;
	
	for(index=0; index<len; index++)
	{
		buf[index] = *(uint8_t *)(start_addr+index);
	}
	
	return 0;
}
/**************************** END OF FILE *************************************/
