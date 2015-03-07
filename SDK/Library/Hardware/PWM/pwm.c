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
#include "pwm.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */

uint16_t base_period = 1000;
/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函 数 名:	void PWM_Init(uint16_t prescaler, uint16_t period)
* 功    能:	TIM2定时器初始化
* 参    数：prescaler----TIM2时钟预分频
* 			period----定时器预重装值
* 返    回:	无
*******************************************************************************/
void PWM_Init(uint16_t prescaler, uint16_t period)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE); 
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Period = period; 
	//设置用来作为TIMx时钟频率除数的预分频值  不分频 36MHz
	TIM_TimeBaseStructure.TIM_Prescaler =prescaler; 
	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	//TIM向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	//使能TIMx在ARR上的预装载寄存器
	TIM_ARRPreloadConfig(TIM2, ENABLE); 
	//使能TIMx外设
	//TIM_Cmd(TIM2, ENABLE);  
	//保存定时器预装计数值
	base_period = period;	
}
/*******************************************************************************
* 函 数 名:	void PWM_ChannelInit( uint8_t channel, uint8_t polarity)
* 功    能:	TIM2通道初始化
* 参    数：channel----PWM通道
*			polarity----PWM极性
* 返    回:	无
*******************************************************************************/
void PWM_ChannelInit( uint8_t channel, uint8_t polarity)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_Cmd(TIM2, DISABLE);  
	
	if(1 == channel)
	{	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//比较输出使能
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//设置待装入捕获比较寄存器的脉冲值
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//输出极性:TIM输出比较极性高
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
		//使能TIMx在CCR2上的预装载寄存器
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  
	}
	else if(2 == channel)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//比较输出使能
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//设置待装入捕获比较寄存器的脉冲值
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//输出极性:TIM输出比较极性高
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);  
		//使能TIMx在CCR2上的预装载寄存器
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);		
	}
	else if(3 == channel)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//比较输出使能
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//设置待装入捕获比较寄存器的脉冲值
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//输出极性:TIM输出比较极性高
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC3Init(TIM2, &TIM_OCInitStructure);  
		//使能TIMx在CCR2上的预装载寄存器
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);		
	}
	else if(4 == channel)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//比较输出使能
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//设置待装入捕获比较寄存器的脉冲值
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//输出极性:TIM输出比较极性高
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC4Init(TIM2, &TIM_OCInitStructure);  
		//使能TIMx在CCR2上的预装载寄存器
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);		
	}
	TIM_Cmd(TIM2, ENABLE);  
}
/*******************************************************************************
* 函 数 名:	void PWM_Start( uint8_t channel, uint8_t duty_cycle )
* 功    能:	开始PWM输出
* 参    数：channel----PWM通道
*			duty_cycle----PWM占空比：0~100
* 返    回:	
*******************************************************************************/
void PWM_Start( uint8_t channel, uint8_t duty_cycle )
{
	uint32_t compare;
	
	compare = base_period * duty_cycle;
	compare = compare / 100;
	if( channel == 1 )
	{
		TIM_SetCompare1( TIM2, compare);
	}
	else if( channel == 2 )
	{
		TIM_SetCompare2( TIM2, compare);
	}	
	else if( channel == 3 )
	{
		TIM_SetCompare3( TIM2, compare);
	}
	else if( channel == 4 )
	{
		TIM_SetCompare4( TIM2, compare);
	}	
}
/**************************** END OF FILE *************************************/

