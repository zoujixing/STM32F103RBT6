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
#include "w25x16.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */

SPI_InitTypeDef SPI_DefaultInit;

uint16_t id;
uint8_t buffer1[12] = {1,2,3,4,5,6,7,8,9,0,1,2};
uint8_t buffer2[12];

/* local function prototypes ------------------------------------------------ */
/*******************************************************************************
* 函数名：主函数
* 功  能：	
* 参  数：
* 返  回：	
*******************************************************************************/
void SPI_Parameter()
{
	//FullDuplex
	SPI_DefaultInit.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//Mast Mode
	SPI_DefaultInit.SPI_Mode = SPI_Mode_Master;
	//8bits
	SPI_DefaultInit.SPI_DataSize = SPI_DataSize_8b;
	//
	SPI_DefaultInit.SPI_CPOL = SPI_CPOL_High;
	SPI_DefaultInit.SPI_CPHA = SPI_CPHA_2Edge;
	//
	SPI_DefaultInit.SPI_NSS = SPI_NSS_Soft;
	//
	SPI_DefaultInit.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	//Set MSB
	SPI_DefaultInit.SPI_FirstBit = SPI_FirstBit_MSB;
	//
	SPI_DefaultInit.SPI_CRCPolynomial = 7;	
}
	
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
	//Initialize SPI and W25x16, after it , must delay time
	SPI_Parameter();
	SPI_HW_Init(SPI_DefaultInit);
	W25X_Init();
	Delayms(50);
	
	id = W25X_ReadID();
	USART1_PrintChar(id >> 8);
	USART1_PrintChar(id);
	Delayms(50);
	USART1_PrintString("erase chip \r\n");
	W25X_EraseChip();
	USART1_PrintString("erase over");
	
	W25X_WritePage(245, buffer1, 12);
	USART1_PrintString("Write over");
	while(1)
	{	
		W25X_ReadPage(245, buffer2, 12);
		USART1_PrintBuff(buffer2, 12);
		USART1_PrintChar( W25X_ReadByte(0) );
		Delayms(2000);
	}
}

/**************************** END OF FILE *************************************/

