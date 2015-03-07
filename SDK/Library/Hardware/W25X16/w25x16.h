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
#ifndef W25X16_H_
#define W25X16_H_

/* information for w25x16---------------------------------------------------- 

address:	0~0x1FFFFF
total size: 16M-bit = 2M bytes
page: 		8192 pages of 256 bytes, Up to 256 bytes can be programmed at a time 
sector:		16 pages
block: 		256 pages or 16 sectors

End-------------------------------------------------------------------------- */

/* needed include files ----------------------------------------------------- */
#include "spi_hw.h"
#include "gpio.h"
#include "usart.h"
/* macro definition --------------------------------------------------------- */

#define SPI_W25X16_CS	GPIOA_Pin_Output(2) 

//÷∏¡Ó±Ì
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

/* typedef ------------------------------------------------------------------ */


/* global function declare -------------------------------------------------- */
extern void W25X_Init(void);
extern uint16_t W25X_ReadID(void);
extern uint32_t W25X_ReadJEDECID(void);

extern uint8_t W25X_ReadStateReg(void);
extern void W25X_WriteStateReg(uint8_t dat);

extern void W25X_WriteEnale(void);
extern void W25X_WriteDisbale(void);

extern void W25X_EraseChip(void);
extern void W25X_EraseSector(uint32_t sec_num);
extern void W25X_EraseBlock(uint32_t block_num);

extern void W25X_WriteByte(uint32_t addr, uint8_t dat);
extern uint8_t W25X_ReadByte(uint32_t addr);

extern void W25X_WritePage(uint32_t addr, uint8_t *pbuf, uint32_t len);
extern void W25X_ReadPage(uint32_t addr, uint8_t *pbuf, uint32_t len);
#endif

/**************************** END OF FILE *************************************/
