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
#include "GPIO.h"
#include "sleep.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

								
/* local variables ---------------------------------------------------------- */
uint8_t count=1;

/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* ��������������
* ��  �ܣ�PA0 WKUP���ѳ�ʼ��
* ��  ����
* ��  �أ�	
*******************************************************************************/
uint8_t Check_WKUP(void) 
{
	uint8_t t=0;
	uint8_t tx=0;//��¼�ɿ��Ĵ���
	
	GPIOD_Pin_Output(2)=0; //����DS0 
	while(1)
	{
		if( GPIOA_Pin_Input(0) )//�Ѿ�������
		{
			t++;
			tx=0;
		}else 
		{
			tx++; //����300ms��û��WKUP�ź�
			if(tx>3)
			{
				GPIOD_Pin_Output(2)=1;
				return 0;//����İ���,���´�������
			}
		}
		Delay_us(30000);
		if(t>=100)//���³���3����
		{
			GPIOD_Pin_Output(2)=0;	  //����DS0 
			return 1; //����3s������
		}
	}
} 
/*******************************************************************************
* ��������������
* ��  �ܣ�PA0 WKUP���ѳ�ʼ��
* ��  ����
* ��  �أ�	
*******************************************************************************/
void WKUP_Init(void)
{	
    GPIO_InitTypeDef  GPIO_InitStructure;  		  
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    //ʹ���ⲿ�жϷ�ʽ
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//���ð������е��ⲿ��·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
   	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	//if(Check_WKUP() == 0) 
		//SLEEP_EnterStandby();    //���ǿ���,�������ģʽ  
}
/*******************************************************************************
* ��������������
* ��  �ܣ�PA0 WKUP���ѳ�ʼ��
* ��  ����
* ��  �أ�	
*******************************************************************************/
void EXTI0_IRQHandler(void)
{ 		    		    				     		    
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	  
	{	 
		//EXTI->PR=1<<0;	
		//������3s���������ģʽ
		if(Check_WKUP())
		{		  
			SLEEP_EnterStandby();
		}
		else
		{
			if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)  
			{   
				PWR_ClearFlag(PWR_FLAG_WU);  
			} 
		}
		EXTI_ClearITPendingBit(EXTI_Line0); 	
	}	
} 
/*******************************************************************************
* ��������������
* ��  �ܣ�	
* ��  ����
* ��  �أ�	
*******************************************************************************/
int main(void)
{	
	SystemInit();
	Delay_init(72);
	NVIC_Configuration();
	GPIO_ClockEnable(RCC_APB2Periph_GPIOD);
	GPIO_ConfigOutput(GPIOD, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
	
	WKUP_Init();
	while(1)
	{	
		GPIOD_Pin_Output(2) = ~GPIOD_Pin_Output(2);
		Delay_us(100000);
		/*
		while(count++)
		{
			GPIOA_Pin_Output(8) = ~GPIOA_Pin_Output(8);
			Delayms(1000);
			if(count == 10)
			{
				count=0;
				SLEEP_EnterStandby();
			}
		}
		*/
	}
}

/**************************** END OF FILE *************************************/

