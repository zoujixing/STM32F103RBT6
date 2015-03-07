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

#include "flash.h"
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
  //uint16_t status = MAL_OK;

  switch (lun)
  {
    case 0:
		FLASH_Unlock();
		
      break;
 
    case 1:
 
      break;

    default:
      return MAL_FAIL;
  }
  return MAL_OK;
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
  uint32_t ret;

  switch (lun)
  {
    case 0:    	
		ret = FLASH_PageWrite((FLASH_START_ADDRESS+Memory_Offset), (uint8_t*)Writebuff,  Transfer_Length);
	
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
	uint32_t ret;

  switch (lun)
  {
    case 0:
		ret = Flash_PageRead((FLASH_START_ADDRESS+Memory_Offset), (uint8_t *)Readbuff, Transfer_Length);
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
		Mass_Block_Count[0] = FLASH_PAGE_COUNT;
		Mass_Block_Size[0]  = FLASH_PAGE_SIZE;
		Mass_Memory_Size[0] = FLASH_SIZE;
        return MAL_OK;
    case 1:
        return MAL_OK;
	default:
		return MAL_FAIL;
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

