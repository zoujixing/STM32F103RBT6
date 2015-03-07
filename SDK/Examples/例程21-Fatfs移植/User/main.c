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
#include "usart.h"
#include "gpio.h"
#include "spi_hw.h"
#include "SD.h"

#include "ff.h"
#include "integer.h"
#include "diskio.h"
#include "string.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */

uint32_t res;
FATFS fs_sd;
FIL	  fil_sd;

uint8_t read_buf[50]; 
uint8_t write_buf[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
uint32_t read_len, write_len, n;

/* local function prototypes ------------------------------------------------ */

/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
int main(void)
{	
	SystemInit();
	Delay_init(72);
	NVIC_Configuration();
	USART1_Init(9600);
	
	Delayms(5000);
	USART1_PrintString("start \r\n");	
	
	res = f_mount(&fs_sd, "1:", 0); 
	if(res == 0)
	{
		USART1_PrintString("f_mount ok \r\n");	
	}
	
	res = f_open(&fil_sd, "1:First1.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	if(res == FR_OK)
	{
		USART1_PrintString("File creat OK \r\n");
	}
	else
	{
		USART1_PrintString("File creat Fail \r\n");
	}
	
	res = f_lseek(&fil_sd, f_size(&fil_sd));
	
	res = f_puts("This is first test \r\n" ,&fil_sd);
	
	res = f_lseek(&fil_sd, f_size(&fil_sd));
	
	res = f_write(&fil_sd, write_buf, 20, &write_len);
	if(res != FR_OK)
	{
		USART1_PrintString("f_write FAIL \r\n");
	}
	else
	{
		USART1_PrintString("f_write buf len33 \r\n ");
		USART1_PrintChar(write_len);
	}
	
	res = f_lseek(&fil_sd, 0);
	
	res = f_read(&fil_sd, read_buf, 50, &read_len);
	if(res != FR_OK)
	{
		USART1_PrintString("File read FAIL \r\n");
	}
	else
	{
		USART1_PrintString("File read OK11 \r\n");
		for(n=0; n<read_len; n++)
			USART1_PrintChar(read_buf[n]);
		//USART1_PrintChar(read_len);
		USART1_PrintString("File read OK22 \r\n");
	}
	
	res = f_close(&fil_sd);
	if(res == FR_OK)
	{
		USART1_PrintString("File Close OK \r\n");
	}
	else
	{
		USART1_PrintString("File Close Fail \r\n");
	}
	
	res = f_mount(NULL, "1", 0); 
	if(res == 0)
	{
		USART1_PrintString("fmount stop ok \r\n");
	}

	while(1)
	{	
		
	}
}

