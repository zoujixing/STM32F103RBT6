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
#include "SD.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */
static uint8_t  SD_Type=0;

SPI_InitTypeDef SPI_DefaultInit;

/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* @brief spi parameter
* @note 
* @param[in] none
* @param[out] none
* @return none
*******************************************************************************/
static void SPI_Parameter()
{
	/*FullDuplex*/
	SPI_DefaultInit.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	/*Mast Mode*/
	SPI_DefaultInit.SPI_Mode = SPI_Mode_Master;
	/*8bits*/
	SPI_DefaultInit.SPI_DataSize = SPI_DataSize_8b;
	
	SPI_DefaultInit.SPI_CPOL = SPI_CPOL_High;
	SPI_DefaultInit.SPI_CPHA = SPI_CPHA_2Edge;
	
	SPI_DefaultInit.SPI_NSS = SPI_NSS_Soft;
	
	SPI_DefaultInit.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	/*Set MSB*/
	SPI_DefaultInit.SPI_FirstBit = SPI_FirstBit_MSB;
	
	SPI_DefaultInit.SPI_CRCPolynomial = 7;	
}
/*******************************************************************************
* @brief set spi speed
* @note 
* @param[in] SpeedSet:SPI baudrateprescaler
* @param[out] none
* @return none
*******************************************************************************/
void SD_Setsp(u8 SpeedSet)
{
	SPI_DefaultInit.SPI_BaudRatePrescaler = SpeedSet ;
  	SPI_Init(SPI1, &SPI_DefaultInit);
	SPI_Cmd(SPI1,ENABLE);	
}
/*******************************************************************************
* @brief initialize CS pin
* @note 
* @param[in] none
* @param[out] none
* @return none
*******************************************************************************/
static void SD_CS_Init(void)
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
* @brief spi initialize
* @note 
* @param[in] none
* @param[out] none
* @return none
*******************************************************************************/
static void SD_SPIInit(void)
{
	SD_CS_Init();
	SPI_Parameter();
	SPI_HW_Init(SPI_DefaultInit);
	/*set low speed mode*/	
	SPI_HW_SetSpeed(SPI_SPEED_256);
	SD_CS_PIN = 1;
}
/*******************************************************************************
* @brief wait for SD ready
* @note 
* @param[in] none
* @param[out] none
* @return 0:SUCCESS
*  		  1:FAIL
*******************************************************************************/
uint8_t SD_WaitReady(void)
{
	uint32_t t=0;
	do
	{
		if(SPI_HW_WRByte(0xFF)==0xFF)
			return 0;
		t++;		  	
	}while(t<0xFF);
	
	return 1;	
}
/*******************************************************************************
* @brief disable SD 
* @note 
* @param[in] none
* @param[out] none
* @return none
*******************************************************************************/
void SD_Disable(void)
{
	SD_CS_PIN = 1;
	/*support extra 8 clock*/
	SPI_HW_WRByte(0xFF);
}
/*******************************************************************************
* @brief Enable SD 
* @note 
* @param[in] none
* @param[out] none
* @return 0:SUCCESS
*		  1:FAIL
*******************************************************************************/
uint8_t SD_Enable(void)
{
	SD_CS_PIN = 0;
	/*wait for SD ready*/
	if(SD_WaitReady()==0)
	{	
		return 0;
	}
	SD_Disable();
	
	return 1;
}
/*******************************************************************************
* @brief Get SD command response data
* @note 
* @param[in] none
* @param[out] none
* @return 0:SUCCESS
*		  1:FAIL
*******************************************************************************/
uint8_t SD_GetCammandRsp(void)
{
	uint8_t ret, retry;
	
	retry = 0x1F;
	do
	{
		ret=SPI_HW_WRByte(0xFF);
	}while((ret&0x80) && retry--);	 

    return ret;
}
/*******************************************************************************
* @brief send command to sd
* @note under SPI mode, when send Command0, should need send crc 0x95
* @param[in] cmd:command number
* @param[in] param:parameters
* @param[in] crc:
* @param[out] none
* @return 0:SUCCESS
*		  1:FAIL
*******************************************************************************/
void SD_SendCommand(uint8_t cmd, uint32_t param, uint8_t crc)
{	
	SPI_HW_WRByte(cmd|0x40);
	SPI_HW_WRByte(param>>24);
	SPI_HW_WRByte(param>>16);
	SPI_HW_WRByte(param>>8);
	SPI_HW_WRByte(param);
	SPI_HW_WRByte(crc);
}
/*******************************************************************************
* @brief check the response data
* @note if spi_read_byte EQU response, return SUCCESS
* @param[in] response:what I want get
* @param[out] none
* @return 0:SUCCESS
*		  1:FAIL
*******************************************************************************/
uint8_t SD_GetResponse(uint8_t response)
{
	uint16_t time=0xFFFF;
	while ((SPI_HW_WRByte(0XFF)!=response)&&time)
	{
		time--;
	}
	if (time==0)
		return MSD_RESPONSE_FAILURE;
	else 
		return MSD_RESPONSE_NO_ERROR;
}
/*******************************************************************************
* @brief read pkt from sd
* @note 
* @param[in] len:the length of data that should be read
* @param[out] pbuf:data
* @return 0:SUCCESS
*		  1:FAIL
*******************************************************************************/
static uint8_t SD_ReadPacket(uint8_t *pbuf, uint16_t len)
{
	/*wait for 0xFE*/
	if(SD_GetResponse(0xFE))
		return 1;
	
	while(len--)
	{
		*pbuf = SPI_HW_WRByte(0xFF);
		pbuf++;
	}
	SPI_HW_WRByte(0xFF);
	SPI_HW_WRByte(0xFF);
	
	return 0;
}
/*******************************************************************************
* @brief send pkt to sd
* @note 
* @param[in] cmd:write mode
* @param[in] pbuf:data to be write
* @return 0:SUCCESS
*		  1:FAIL
*		  2:response error
*******************************************************************************/
static uint8_t SD_SendPacket(uint8_t *pbuf, uint8_t cmd)
{	
	uint8_t rx_status;
	uint16_t index;
	/*wait sd ready*/
	if(SD_WaitReady())
		return 1;
	
	SPI_HW_WRByte(cmd);
	/*stop cmd:0xFD*/
	if(cmd != 0xFD)
	{
		for(index=0;index<512;index++)
			SPI_HW_WRByte(pbuf[index]); 
		/*ignore crc*/
	    SPI_HW_WRByte(0xFF);
	    SPI_HW_WRByte(0xFF);
		/*get response*/
		rx_status=SPI_HW_WRByte(0xFF);
		if((rx_status&0x1F)!=0x05)
		{	/*response error*/
			return 2;	
		}
	}
	
	return 0;
}
/*******************************************************************************
* @brief get SD CID
* @note 
* @param[in] none
* @param[out] pbuf:CID data
* @return 0:SUCCESS
*		  1:FAIL
*******************************************************************************/
uint8_t SD_GetCID(uint8_t *pbuf)
{
	uint8_t ret;
	
	/*send cmd10, read CID*/
	SD_SendCommand(CMD10, 0x00, 0x00);
	ret = SD_GetCammandRsp();
	if(ret == 0x00)
	{	/*read 16 data*/
		ret = SD_ReadPacket(pbuf, 16);
	}
	
	SD_Disable();
	if(ret)
		return 1;
	else 
		return 0;	
}
/*******************************************************************************
* @brief get sd CSD
* @note 
* @param[in] pbuf:CSD data
* @param[out] none
* @return 0:SUCCESS
*		  1:FAIL
*******************************************************************************/
uint8_t SD_GetCSD(uint8_t *pbuf)
{
	uint8_t ret;
	
	SD_Disable();
	if(SD_Enable())
		return 0xFF;	
	
	/*send cmd9, read CSD*/
	SD_SendCommand(CMD9, 0x00, 0x00);
	ret = SD_GetCammandRsp();
	if(ret == 0x00)
	{	/*read 16 data*/
		ret = SD_ReadPacket(pbuf, 16);
	}
	
	SD_Disable();
	if(ret)
		return 1;
	else 
		return 0;		
}
/*******************************************************************************
* @brief get sector number
* @note 
* @param[in] none
* @param[out] none
* @return the number of sector
*******************************************************************************/
uint32_t SD_GetSectorNum(void)
{
	uint8_t csd[16];
	uint8_t index;
	uint16_t csize;
	uint32_t num;
	
	if(SD_GetCSD(csd)!=0)
		return 0;
	
	/*if SDHC, Calculate it by follow:*/
    if((csd[0]&0xC0)==0x40)	 
	{	/*SD type: V2.0*/
		csize = csd[9] + ((u16)csd[8] << 8) + 1;
		num = (u32)csize << 10;  
    }
	else
    {	/*SD type: V1.xx*/
		index = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
		csize = (csd[8] >> 6) + ((u16)csd[7] << 2) + ((u16)(csd[6] & 3) << 10) + 1;
		num= (u32)csize << (index - 9);
    }
	
    return num;	
}
/*******************************************************************************
* @brief SD Initialize
* @note 
* @param[in] none
* @param[out] none
* @return 0:SUCCESS
*		  else:FAIL
*******************************************************************************/
uint8_t SD_Initialize(void)
{	
	uint8_t index, ret, buf[4];
	uint16_t time;
	
	SD_SPIInit();
	
	SD_Disable();
	if(SD_Enable())
		return 0xFF;
	
	SPI_HW_SetSpeed(SPI_SPEED_256);
	/*send 74 clock at least*/
	for(index=0; index<10; index++)
		SPI_HW_WRByte(0xFF);

	time = 20;
	SD_Type = 0;
	do
	{	/*SD IDE status*/
		SD_SendCommand(CMD0, 0, 0x95);
		ret = SD_GetCammandRsp();
	}while((ret != 0x01) && time--);
	if(ret == 0x01)
	{	//SD V2.0
		SD_SendCommand(CMD8, 0x1AA, 0x87);
		ret = SD_GetCammandRsp();
		//if(SD_SendCommand(CMD8, 0x1AA, 0x87) == 1)
		if(ret == 0x01)
		{	
			//Get trailing return value of R7 resp
			for(index=0; index<4; index++)
				buf[index] = SPI_HW_WRByte(0xFF);
			/*check is it support 2.7~3.6*/
			if( buf[2]==0x01 && buf[3] == 0xAA)
			{	
				time = 0XFFFE;
				do
				{	/*send cmd55, cmd41*/
					SD_SendCommand(CMD55, 0, 0x01);	
					ret = SD_GetCammandRsp();
					SD_SendCommand(CMD41, 0x40000000, 0x01);
					ret = SD_GetCammandRsp();
				}while(ret && time--);
				/*check SD2.0 version */
				SD_SendCommand(CMD58, 0, 0x01);
				ret= SD_GetCammandRsp();
				if(time && ret == 0)
				{	
					/*get OCR*/
					for(index=0; index<4; index++)
						buf[index] = SPI_HW_WRByte(0xFF);
					/*check CCS*/
					if(buf[0]&0x40)
						SD_Type = SD_TYPE_V2HC;   
					else 
						SD_Type = SD_TYPE_V2;   
				}
			}
		}
		else
		{	/*SD V1.x/MMC V3*/
			/*send cmd55 cmd41*/
			SD_SendCommand(CMD55, 0, 0x01);
			ret = SD_GetCammandRsp();			
			SD_SendCommand(CMD41 ,0, 0x01);	
			ret= SD_GetCammandRsp();
			if(ret <= 1)
			{
				SD_Type = SD_TYPE_V1;
				time = 0xFFFE;
				do 
				{	/*wait exit IDLE mode*/
					SD_SendCommand(CMD55, 0, 0x01);	
					ret = SD_GetCammandRsp();
					SD_SendCommand(CMD41,0,0x01);
					ret= SD_GetCammandRsp();
				}while(ret && time--);
			}
			else
			{	/*MMC*/
				SD_Type = SD_TYPE_MMC;
				time = 0xFFFE;
				do
				{	/*wait exit IDLE mode*/									    
					SD_SendCommand(CMD1, 0, 0x01);
					ret= SD_GetCammandRsp();
				}while(ret && time--);  
			}
			/*error sd type*/
			SD_SendCommand(CMD16, 512, 0x01);
			ret= SD_GetCammandRsp();
			if(time == 0 || ret != 0)
				SD_Type = SD_TYPE_ERR;
		}	
	}
	/*initialize end*/
	SD_Disable();
	/*High speed*/
	SPI_HW_SetSpeed(SPI_SPEED_4);
	
	if(SD_Type)
		return 0;
	else if(ret)
		return ret; 
	/*other error*/
	return 0xAA;
}
/*******************************************************************************
* @brief SD read sector 
* @note 
* @param[in] sector: sector number
* @param[in] num: number of sectors to be read
* @param[out] pbuf: buffer that store data
* @return 0:SUCCESS
*		  else:FAIL
*******************************************************************************/
uint8_t SD_ReadDisk(uint8_t *pbuf, uint32_t sector, uint8_t num)
{
	uint8_t ret;
	
	SD_Disable();
	if(SD_Enable())
		return 0xFF;
	
	if(SD_Type != SD_TYPE_V2HC)
		sector <<= 9;
	
	if(num == 1)
	{	/*read cmd17*/
		SD_SendCommand(CMD17, sector, 0x01);
		ret= SD_GetCammandRsp();
		if(ret == 0)
		{	/*send cmd17 OK, read 512 bytes*/
			ret = SD_ReadPacket(pbuf, 512);
		}
	}
	else
	{	/*continus read cmd*/
		SD_SendCommand(CMD18, sector, 0x01);
		ret= SD_GetCammandRsp();
		do
		{	/*read 512 bytes*/
			ret = SD_ReadPacket(pbuf, 512);
			pbuf += 512;  
		}while(--num && ret==0); 
		/*stop cmd12*/
		SD_SendCommand(CMD12, 0, 0x01);	
		ret= SD_GetCammandRsp();
		ret= SD_GetCammandRsp();
	}   

	SD_Disable();
	
	return ret;
}
/*******************************************************************************
* @brief SD write sector 
* @note 
* @param[in] sector: sector number
* @param[in] num: number of sectors to be read
* @param[in] pbuf: data point
* @return 0:SUCCESS
*		  else:FAIL
*******************************************************************************/
uint8_t SD_WriteDisk(uint8_t *pbuf, uint32_t sector, uint8_t num)
{
	uint8_t ret;
	
	SD_Disable();
	if(SD_Enable())
		return 0xFF;

	if(SD_Type != SD_TYPE_V2HC)
		sector <<= 9;
	
	if(num == 1)
	{	/*write cmd24*/
		SD_SendCommand(CMD24, sector, 0x01);
		ret= SD_GetCammandRsp();
		if(ret == 0)
		{	/*write 512*/	   
			ret=SD_SendPacket(pbuf, 0xFE);
		}
	}
	else
	{
		if(SD_Type != SD_TYPE_MMC)
		{
			SD_SendCommand(CMD55, 0, 0x01);	
			ret = SD_GetCammandRsp();
			SD_SendCommand(CMD23, num, 0x01);
			ret = SD_GetCammandRsp();
		}
		/*Continuous read command*/
 		SD_SendCommand(CMD25, sector, 0x01);
		ret= SD_GetCammandRsp();
		if(ret == 0)
		{
			do
			{	/*write 512 bytes */
				ret = SD_SendPacket(pbuf,0xFC);
				pbuf += 512;  
			}while(--num && ret==0);
			/*Last sector, write cmd 0xFD*/
			ret = SD_SendPacket(0, 0xFD);
		}
	}   
	SD_Disable();
	
	return ret;
}



/**************************** END OF FILE *************************************/

