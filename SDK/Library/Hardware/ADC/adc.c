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
#include "adc.h"

/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */


/* local function prototypes ------------------------------------------------ */


/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void ADC1_PinInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  
                       
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOx, &GPIO_InitStructure);	
	
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void ADC1_Init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
	//初始化ADC的IO
	ADC1_PinInit(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	//72M/6=12,ADC最大时间不能超过14M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   
	
	ADC_DeInit(ADC1);
	//独立工作模式
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	//单次转换
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	//不使用外部触发
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	//顺序进行规则转换的ADC通道的数目
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);	
 
	ADC_TempSensorVrefintCmd(ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);	
	//重置指定的ADC1的校准寄存器
	ADC_ResetCalibration(ADC1);	
	//获取ADC1重置校准寄存器的状态,等待设置状态结束
	while(ADC_GetResetCalibrationStatus(ADC1));	
	//开始指定ADC1的校准状态
	ADC_StartCalibration(ADC1);		
	//获取指定ADC1的校准程序,设置状态则等待
	while(ADC_GetCalibrationStatus(ADC1));		
	//使能指定的ADC1的软件转换启动功能
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
uint16_t ADC1_GetValue(uint8_t channel)
{
	//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
	//ADC1,ADC通道3,规则采样顺序值为1,采样时间为239.5周期	  		
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );		    
	//使能指定的ADC1的软件转换启动功能	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	 //等待转换结束
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	//返回最近一次ADC1规则组的转换结果
	return ADC_GetConversionValue(ADC1);	
}

/**************************** END OF FILE *************************************/
