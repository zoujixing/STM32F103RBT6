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
* �� �� ��:	void PWM_Init(uint16_t prescaler, uint16_t period)
* ��    ��:	TIM2��ʱ����ʼ��
* ��    ����prescaler----TIM2ʱ��Ԥ��Ƶ
* 			period----��ʱ��Ԥ��װֵ
* ��    ��:	��
*******************************************************************************/
void PWM_Init(uint16_t prescaler, uint16_t period)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE); 
	//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Period = period; 
	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ 36MHz
	TIM_TimeBaseStructure.TIM_Prescaler =prescaler; 
	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	//TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM2, ENABLE); 
	//ʹ��TIMx����
	//TIM_Cmd(TIM2, ENABLE);  
	//���涨ʱ��Ԥװ����ֵ
	base_period = period;	
}
/*******************************************************************************
* �� �� ��:	void PWM_ChannelInit( uint8_t channel, uint8_t polarity)
* ��    ��:	TIM2ͨ����ʼ��
* ��    ����channel----PWMͨ��
*			polarity----PWM����
* ��    ��:	��
*******************************************************************************/
void PWM_ChannelInit( uint8_t channel, uint8_t polarity)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_Cmd(TIM2, DISABLE);  
	
	if(1 == channel)
	{	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//�������:TIM����Ƚϼ��Ը�
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
		//ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  
	}
	else if(2 == channel)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//�������:TIM����Ƚϼ��Ը�
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);  
		//ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);		
	}
	else if(3 == channel)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//�������:TIM����Ƚϼ��Ը�
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
		TIM_OC3Init(TIM2, &TIM_OCInitStructure);  
		//ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);		
	}
	else if(4 == channel)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		//�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		//���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_Pulse = 0; 
		//�������:TIM����Ƚϼ��Ը�
		if( polarity == 0 )
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
		else
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
		TIM_OC4Init(TIM2, &TIM_OCInitStructure);  
		//ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);		
	}
	TIM_Cmd(TIM2, ENABLE);  
}
/*******************************************************************************
* �� �� ��:	void PWM_Start( uint8_t channel, uint8_t duty_cycle )
* ��    ��:	��ʼPWM���
* ��    ����channel----PWMͨ��
*			duty_cycle----PWMռ�ձȣ�0~100
* ��    ��:	
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

