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
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
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
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
*******************************************************************************/
void ADC1_Init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
	//��ʼ��ADC��IO
	ADC1_PinInit(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	//72M/6=12,ADC���ʱ�䲻�ܳ���14M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   
	
	ADC_DeInit(ADC1);
	//��������ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	//����ת��
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	//��ʹ���ⲿ����
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	//˳����й���ת����ADCͨ������Ŀ
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);	
 
	ADC_TempSensorVrefintCmd(ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);	
	//����ָ����ADC1��У׼�Ĵ���
	ADC_ResetCalibration(ADC1);	
	//��ȡADC1����У׼�Ĵ�����״̬,�ȴ�����״̬����
	while(ADC_GetResetCalibrationStatus(ADC1));	
	//��ʼָ��ADC1��У׼״̬
	ADC_StartCalibration(ADC1);		
	//��ȡָ��ADC1��У׼����,����״̬��ȴ�
	while(ADC_GetCalibrationStatus(ADC1));		
	//ʹ��ָ����ADC1�����ת����������
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
}
/*******************************************************************************
* �� �� ��:	
* ��    ��:	
* ��    ����
* ��    ��:	
*******************************************************************************/
uint16_t ADC1_GetValue(uint8_t channel)
{
	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  		
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );		    
	//ʹ��ָ����ADC1�����ת����������	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	 //�ȴ�ת������
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	//�������һ��ADC1�������ת�����
	return ADC_GetConversionValue(ADC1);	
}

/**************************** END OF FILE *************************************/
