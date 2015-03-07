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
#include "rtc.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */
rtc_irq_handle sec_irq_handle;
rtc_irq_handle alrf_irq_hanle;
rtc_irq_handle ow_irq_hanle;

/* local function prototypes ------------------------------------------------ */

/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
*******************************************************************************/
void RTC_IRQHandler(void)
{	
	//�����ж�	    
	if( RTC_GetITStatus(RTC_IT_SEC) != RESET )
	{							
		if( sec_irq_handle != NULL)
		{
			sec_irq_handle();	
		}
		
		RTC_ClearITPendingBit(RTC_IT_SEC);
	}
	//�����ж�
	if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
	{
		if(alrf_irq_hanle != NULL)
		{
			alrf_irq_hanle();
		}
		RTC_ClearITPendingBit(RTC_IT_ALR);
	} 	
	//����ж�
	if(RTC_GetITStatus(RTC_IT_OW) != RESET)
	{
		if(ow_irq_hanle != NULL)
		{
			ow_irq_hanle();
		}
		RTC_ClearITPendingBit(RTC_IT_OW);
	}	   	
	RTC_WaitForLastTask();				 	   	 
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
*******************************************************************************/
void RTC_SetAlarmValue(uint32_t value)
{
	RTC_WaitForLastTask();	
	RTC_SetAlarm(value);
	RTC_WaitForLastTask();	
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
*******************************************************************************/
void RTC_SetCountValue(uint32_t value)
{
	RTC_WaitForLastTask();	
	RTC_SetCounter(value);	
	RTC_WaitForLastTask();	
}
/*******************************************************************************
* �� �� ��:	RTC_InitIRQHandle
* ��    ��:	�����жϻص�������������Ҫ��NULL
* ��    ����sec_handle�����жϻص�����
			alrf_hanle�������жϻص�����
			ow_hanle������жϻص�����
* ��    ��:	��
*******************************************************************************/
void RTC_InitIRQHandle(rtc_irq_handle sec_handle, rtc_irq_handle alrf_hanle, rtc_irq_handle ow_hanle)
{
	sec_irq_handle = sec_handle;
	alrf_irq_hanle = alrf_hanle;
	ow_irq_hanle = ow_hanle;
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
*******************************************************************************/
uint8_t RTC_Init(uint32_t pre_value, uint32_t alarm_value, uint32_t count_value)
{	
	uint8_t count;
    NVIC_InitTypeDef NVIC_InitStructure;
	//RTCȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);		

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR , ENABLE);	
	PWR_BackupAccessCmd(ENABLE);
	//�����ⲿ���پ���(LSE),ʹ��������پ���
	RCC_LSEConfig(RCC_LSE_ON);	
	//���ָ����RCC��־λ�������,�ȴ����پ������
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	
	{
		count++;
		Delayms(10);
	}
	if(count>=250)
		return 1;
	//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��   
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		 
	RCC_RTCCLKCmd(ENABLE);	
	//�ȴ����һ�ζ�RTC�Ĵ����Ķ��������
	RTC_WaitForSynchro();
	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	RTC_WaitForLastTask();	
	//���ñ���ʱ��
	RTC_SetAlarm(alarm_value);
	RTC_WaitForLastTask();	
	//�����ж�
	RTC_ITConfig( RTC_IT_SEC|RTC_IT_ALR|RTC_IT_OW, ENABLE);	
	RTC_WaitForLastTask();	
	//����RTCԤ��Ƶ��ֵ
	RTC_SetPrescaler(pre_value); 
	RTC_WaitForLastTask();	
	//���RCC�ĸ�λ��־λ
	RCC_ClearFlag();
	
 	RTC_WaitForLastTask();	
	RTC_SetCounter(count_value);	
	RTC_WaitForLastTask();	
	return 0;
}


/**************************** END OF FILE *************************************/
