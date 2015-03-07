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
#include "spi_hw.h"

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
static void SPI_PinConfig()
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	//Enable GPIOA and SPI module
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	//About the MISO, 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  					
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void SPI_HW_Init(SPI_InitTypeDef SPI_InitStructure)
{
	SPI_PinConfig();
	SPI_Cmd(SPI1, DISABLE);  
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
	
	SPI_HW_WRByte(0xff);
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
uint8_t SPI_HW_WRByte(uint8_t dat)
{	
	uint8_t timeout=0;
	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET )
	{
		timeout++;
		if(timeout>200)
			return 0;	
	}
	timeout = 0;
	SPI_I2S_SendData(SPI1, dat);

	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET )
	{
		timeout++;
		if(timeout>200)
			return 0;	
	}
	timeout = 0;
	return SPI_I2S_ReceiveData(SPI1);
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：see spi_hw.h
* 返    回:	none
*******************************************************************************/
void SPI_HW_SetSpeed(uint8_t speed)
{
	SPI1->CR1 &= 0xFFC7;
	switch(speed)
	{
		case SPI_SPEED_2   : SPI1->CR1|=0<<3;break;
		case SPI_SPEED_4   : SPI1->CR1|=1<<3;break;
		case SPI_SPEED_8   : SPI1->CR1|=2<<3;break;
		case SPI_SPEED_16  : SPI1->CR1|=3<<3;break;
		case SPI_SPEED_32  : SPI1->CR1|=4<<3;break;
		case SPI_SPEED_64  : SPI1->CR1|=5<<3;break;
		case SPI_SPEED_128 : SPI1->CR1|=6<<3;break;
		case SPI_SPEED_256 : SPI1->CR1|=7<<3;break;
		default : SPI1->CR1|=7<<3;break;
	}
	SPI1->CR1|=1<<6;
}

/**************************** END OF FILE *************************************/
