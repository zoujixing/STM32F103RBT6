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
* 函数名：主函数
* 功  能：PA0 WKUP唤醒初始化
* 参  数：
* 返  回：	
*******************************************************************************/
uint8_t Check_WKUP(void) 
{
	uint8_t t=0;
	uint8_t tx=0;//记录松开的次数
	
	GPIOD_Pin_Output(2)=0; //亮灯DS0 
	while(1)
	{
		if( GPIOA_Pin_Input(0) )//已经按下了
		{
			t++;
			tx=0;
		}else 
		{
			tx++; //超过300ms内没有WKUP信号
			if(tx>3)
			{
				GPIOD_Pin_Output(2)=1;
				return 0;//错误的按键,按下次数不够
			}
		}
		Delay_us(30000);
		if(t>=100)//按下超过3秒钟
		{
			GPIOD_Pin_Output(2)=0;	  //点亮DS0 
			return 1; //按下3s以上了
		}
	}
} 
/*******************************************************************************
* 函数名：主函数
* 功  能：PA0 WKUP唤醒初始化
* 参  数：
* 返  回：	
*******************************************************************************/
void WKUP_Init(void)
{	
    GPIO_InitTypeDef  GPIO_InitStructure;  		  
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    //使用外部中断方式
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//设置按键所有的外部线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//设外外部中断模式:EXTI线路为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
   	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	//if(Check_WKUP() == 0) 
		//SLEEP_EnterStandby();    //不是开机,进入待机模式  
}
/*******************************************************************************
* 函数名：主函数
* 功  能：PA0 WKUP唤醒初始化
* 参  数：
* 返  回：	
*******************************************************************************/
void EXTI0_IRQHandler(void)
{ 		    		    				     		    
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	  
	{	 
		//EXTI->PR=1<<0;	
		//若长按3s，进入待机模式
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

