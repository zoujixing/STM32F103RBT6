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
#include "w25x16.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */
/*******************************************************************************
* �� �� ��:	
* ��    ��:	config CS IO
* ��    ����none
* ��    ��:	none
*******************************************************************************/
void W25X_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Read ID
* ��    ����none
* ��    ��:	Device ID
*******************************************************************************/
uint16_t W25X_ReadID(void)
{ 		  
	uint16_t dev_id = 0;
	//Get ID command
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_ManufactDeviceID);    
	SPI_HW_WRByte(0x00); 	    
	SPI_HW_WRByte(0x00); 	    
	SPI_HW_WRByte(0x00); 	
	//SPI_HW_WRByte(0x00); 
	dev_id|=SPI_HW_WRByte(0xFF)<<8;  
	dev_id|=SPI_HW_WRByte(0xFF);	 
	SPI_W25X16_CS = 1;	    
	return dev_id;	
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Read JEDEC ID
* ��    ����none
* ��    ��:	24-bits, the High 8bit invalid
*******************************************************************************/
uint32_t W25X_ReadJEDECID(void)
{
	uint32_t id = 0;
	//Get Jedec ID 
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_JedecDeviceID);    	 			   
	id|=SPI_HW_WRByte(0xFF)<<16;  
	id|=SPI_HW_WRByte(0xFF)<<8;	 
	id|=SPI_HW_WRByte(0xFF);
	SPI_W25X16_CS = 1;	
	return id;		
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Read status regist
* ��    ����none
* ��    ��:	8-bits current status
*******************************************************************************/
uint8_t W25X_ReadStateReg(void)
{	
	uint8_t status=0;
	
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_ReadStatusReg);
	status = SPI_HW_WRByte(0xFF);
	SPI_W25X16_CS = 1;
	
	return status;
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	write status regist
* ��    ����8-bits data to be written
* ��    ��:	none
*******************************************************************************/
void W25X_WriteStateReg(uint8_t dat)
{	
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_WriteStatusReg);
	SPI_HW_WRByte(dat);
	SPI_W25X16_CS = 1;	
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	write for busy clean
* ��    ����none
* ��    ��:	none
*******************************************************************************/
void W25X_WaitBusy(void)   
{   
	while( ( W25X_ReadStateReg()&0x01 ) == 0x01 );   
}  
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Enable Write data to flash
* ��    ����none
* ��    ��:	none
*******************************************************************************/
void W25X_WriteEnale(void)
{
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_WriteEnable);
	SPI_W25X16_CS = 1;
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Disable Write data to flash
* ��    ����none
* ��    ��:	none
*******************************************************************************/
void W25X_WriteDisbale(void)
{
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_WriteDisable);
	SPI_W25X16_CS = 1;	
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Erase whole chip, W25X16:25s 
* ��    ����none
* ��    ��:	none
*******************************************************************************/
void W25X_EraseChip(void)
{
	W25X_WriteEnale();
	W25X_WaitBusy();
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_ChipErase);
	SPI_W25X16_CS = 1;	
	W25X_WaitBusy();
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Erase sector
* ��    ����sec_num: 0~511
* ��    ��:	none
*******************************************************************************/
void W25X_EraseSector(uint32_t sec_num)
{
	uint32_t sec_addr;
	
	if(sec_num >= 512)
		return;	
	sec_addr = sec_num*4096;
	W25X_WriteEnale();
	W25X_WaitBusy();
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_SectorErase);
	SPI_HW_WRByte((uint8_t)sec_addr>>16);
	SPI_HW_WRByte((uint8_t)sec_addr>>8);
	SPI_HW_WRByte((uint8_t)sec_addr>>0);
	SPI_W25X16_CS = 1;	
	W25X_WaitBusy();	
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Erase Block
* ��    ����sec_num: 0~31
* ��    ��:	none
*******************************************************************************/
void W25X_EraseBlock(uint32_t block_num)
{
	uint32_t block_addr;
	
	if(block_num >= 32)
		return;
	block_addr = block_num*65536;
	W25X_WriteEnale();
	W25X_WaitBusy();
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_BlockErase);
	SPI_HW_WRByte((uint8_t)block_addr>>16);
	SPI_HW_WRByte((uint8_t)block_addr>>8);
	SPI_HW_WRByte((uint8_t)block_addr>>0);
	SPI_W25X16_CS = 1;	
	W25X_WaitBusy();	
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Write byte to flash
* ��    ����addr----flash address, 24-bit valid
			dat----data to be written
* ��    ��:	none
*******************************************************************************/
void W25X_WriteByte(uint32_t addr, uint8_t dat)
{
	W25X_WriteEnale();
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_PageProgram);
	SPI_HW_WRByte((uint8_t)addr>>16);
	SPI_HW_WRByte((uint8_t)addr>>8);
	SPI_HW_WRByte((uint8_t)addr>>0);
	SPI_HW_WRByte(dat);
	SPI_W25X16_CS = 1;
	
	W25X_WaitBusy();   
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	Read byte from flash
* ��    ����addr----flash address, 24-bit valid
* ��    ��:	data read from flash
*******************************************************************************/
uint8_t W25X_ReadByte(uint32_t addr)
{
	uint8_t dat;
	
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_ReadData);
	SPI_HW_WRByte((uint8_t)addr>>16);
	SPI_HW_WRByte((uint8_t)addr>>8);
	SPI_HW_WRByte((uint8_t)addr>>0);	
	dat = SPI_HW_WRByte(0xFF);
	SPI_W25X16_CS = 1;
	
	return dat;
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����addr:addr of write addr
*			*pbuf:the point of data buffer
*			len:len of buffer
* ��    ��:	none
*******************************************************************************/
void W25X_WritePage(uint32_t addr, uint8_t *pbuf, uint32_t len)
{
	uint16_t index, temp, write_len;
	
	temp = 256 - addr%256;
	if( len > temp)
	{
		write_len = temp;
	}
	else
	{
		write_len = len;
	}
	W25X_WriteEnale();
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_PageProgram);
	SPI_HW_WRByte((uint8_t)addr>>16);
	SPI_HW_WRByte((uint8_t)addr>>8);
	SPI_HW_WRByte((uint8_t)addr>>0);
	for(index=0; index<write_len; index++)
	{
		SPI_HW_WRByte( pbuf[index] );
	}
	SPI_W25X16_CS = 1;
	W25X_WaitBusy(); 
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����addr:addr of read addr
*			*pbuf:the point of data buffer
*			len:len of read
* ��    ��:	none
*******************************************************************************/
void W25X_ReadPage(uint32_t addr, uint8_t *pbuf, uint32_t len)
{
	uint16_t index;
	
	SPI_W25X16_CS = 0;
	SPI_HW_WRByte(W25X_ReadData);
	SPI_HW_WRByte((uint8_t)addr>>16);
	SPI_HW_WRByte((uint8_t)addr>>8);
	SPI_HW_WRByte((uint8_t)addr>>0);
	for(index=0; index<len; index++)
	{
		pbuf[index] = SPI_HW_WRByte(0xFF);
	}
	SPI_W25X16_CS = 1;
}




/**************************** END OF FILE *************************************/
