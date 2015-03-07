/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: USB drive control */
//#include "atadrive.h"	/* Example: ATA drive control */
#include "SD.h"		/* Example: MMC/SDC contorl */	

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA drive to drive number 0 */
#define MMC		1	/* Example: Map MMC/SD card to drive number 1 */
#define USB		2	/* Example: Map USB drive to drive number 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
//	DSTATUS stat;
//	int result;

//	switch (pdrv) {
//	case ATA :
//		// translate the reslut code here
//		stat = 0;
//		return stat;

//	case MMC :
//		// translate the reslut code here
//		stat = 0;
//		return stat;

//	case USB :
//		// translate the reslut code here
//		stat = 0;
//		return stat;
//	}
//	return STA_NOINIT;
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	uint8_t stat=1;
	
	switch (pdrv) 
	{
		case ATA :
			break;
		case MMC :
			stat=SD_Initialize(); 	  
			break;

		case USB :
			break;
	}
	if(stat)
		return STA_NOINIT;
	else
		return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	uint8_t res=1;

	if (!count)
		return RES_PARERR;
	
	switch (pdrv) 
	{
		case ATA :
			break;
		case MMC :
			res=SD_ReadDisk(buff,sector,count);
		case USB :
			break;
	}
	if(res==0x00)
		return RES_OK;	 
    else 
		return RES_ERROR;	   
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	uint8_t res=1;
	uint8_t retry = 0x1F;
	if (!count)
		return RES_PARERR;
	switch (pdrv) 
	{
		case ATA :
			break;
		case MMC :
			while(retry)
			{
				res=SD_WriteDisk((u8*)buff,sector,count);
				if(res==0)
					break;
				retry--;
			}
			break;
		case USB :
			break;
	}
    if(res == 0x00)
		return RES_OK;	 
    else 
		return RES_ERROR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_ERROR;
	
	switch (pdrv) 
	{
		case ATA :
			break;
		case MMC :
			switch(cmd)
			{
				case CTRL_SYNC:	    
					res = RES_OK;
					break;	 
				case GET_SECTOR_SIZE:
					*(WORD*)buff = 512;
					res = RES_OK;
					break;	 
				case GET_BLOCK_SIZE:
					*(WORD*)buff = 8;
					res = RES_OK;
					break;	 
				case GET_SECTOR_COUNT:
					res = RES_OK;
					break;
				default:
					res = RES_PARERR;
					break;
			}
			break;
		case USB :
			break;
	}
	
	return res;
}
#endif

//获得时间
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{				 
	return 0;
}			 
////动态分配内存
//void *ff_memalloc (UINT size)			
//{
//	return (void*)mymalloc(SRAMIN,size);
//}
////释放内存
//void ff_memfree (void* mf)		 
//{
//	myfree(SRAMIN,mf);
//}




