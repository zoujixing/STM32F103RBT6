/**
  ******************************************************************************
  * @file    mass_mal.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Medium Access Layer interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "mass_mal.h"

#include "spi_hw.h"
#include "SD.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

#if defined(USE_STM3210E_EVAL) || defined(USE_STM32L152D_EVAL)
SD_CardInfo mSDCardInfo;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(uint8_t lun)
{
  uint16_t status = MAL_OK;

  switch (lun)
  {
    case 0:
		status = SD_Initialize();
      break;

    case 1:
 
      break;

    default:
      return MAL_FAIL;
  }
  if(status == 0x00)
	return MAL_OK;
  else
	return MAL_FAIL;  
}
/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{									
  uint8_t ret;
	uint16_t start_sector, sector_num;
  switch (lun)
  {
    case 0:    	
			sector_num   = Transfer_Length >> 9;
		  start_sector = Memory_Offset >> 9;
			ret = SD_WriteDisk((uint8_t *)Writebuff, start_sector, sector_num);
      break;

    case 1:

      break;

    default:
      return MAL_FAIL;
  }
	if(ret == 0x00)
		return MAL_OK;
	else
		return MAL_FAIL;
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
	uint8_t ret;
	uint16_t start_sector, sector_num;
  switch (lun)
  {
    case 0:
			sector_num   = Transfer_Length >> 9;
		  start_sector = Memory_Offset >> 9;
		  ret = SD_ReadDisk((uint8_t *)Readbuff, start_sector, sector_num);
      break;

    case 1:

      break;

    default:
      return MAL_FAIL;
  }
	if(ret == 0x00)
		return MAL_OK;
	else
		return MAL_FAIL;
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_GetStatus (uint8_t lun)
{
	switch(lun)
  {
    case 0:
				Mass_Block_Count[0] = SD_GetSectorNum();
				Mass_Block_Size[0]  = 512;
				Mass_Memory_Size[0] = Mass_Block_Count[0] * 512;
        return MAL_OK;
    case 1:
        return MAL_OK;
		default:
				return MAL_FAIL;
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

