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
#include "TFTLCD.h"
#include "FONT.h"
/* import extern variables  ------------------------------------------------- */


/* global variables --------------------------------------------------------- */

  
/* local variables ---------------------------------------------------------- */
//画笔颜色,背景颜色,默认背景白色，默认画笔黑色
static uint16_t POINT_COLOR = BLACK, BACK_COLOR = WHITE;  
//字体大小
static uint8_t Display_SIZE = 16;
//显示模式
static uint8_t Display_MODE = 0;
/* local function prototypes ------------------------------------------------ */



/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_OpenBackLight()
{
	LCD_LED = 1;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_CloseBackLight()
{
	LCD_LED = 0;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_SetDisplayMode(uint8_t mode)
{
	if(mode == MODE_0 || mode == MODE_1)
		Display_MODE = mode;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_SetDisplaySize(uint8_t size)
{	
	if(size == SIZE_12 || size == SIZE_16)
		Display_SIZE = size;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_SetColor(uint16_t point_color, uint16_t back_clor)
{
	POINT_COLOR = point_color;
	BACK_COLOR = back_clor;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_WriteData(uint16_t dat)
{	
	LCD_RS = 1;//0:Write REG 1:Write data
	LCD_CS = 0;
	DATAOUT(dat);
	LCD_WR = 0; 
	LCD_WR = 1; 
	LCD_CS = 1;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
uint16_t TFTLCD_ReadData()
{	
	uint16_t read_data;
	
 	GPIOB->CRL = 0X88888888; //PB0-7  上拉输入
	GPIOB->CRH = 0X88888888; //PB8-15 上拉输入
	GPIOB->ODR = 0X0000;     //全部输出0
	
	LCD_RS = 1;
	LCD_CS = 0;
	//读取数据(读寄存器时,并不需要读2次)
	LCD_RD = 0;					   
	LCD_RD = 1;
	read_data = DATAIN;  
	LCD_CS=1; 

	GPIOB->CRL=0X33333333; //PB0-7  上拉输出
	GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	GPIOB->ODR=0XFFFF;    //全部输出高		
	
	return read_data;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_WriteReg(uint16_t dat)
{	
	LCD_RS = 0;//0:Write REG 1:Write data
	LCD_CS = 0;
	DATAOUT(dat);
	LCD_WR = 0; 
	LCD_WR = 1; 
	LCD_CS = 1;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_WriteRegData(uint16_t reg, uint16_t dat)
{
	TFTLCD_WriteReg(reg);
	TFTLCD_WriteData(dat);
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
uint16_t TFTLCD_ReadReg(uint16_t dat)
{	
	uint16_t read_data;
	
	TFTLCD_WriteReg(dat);
	read_data = TFTLCD_ReadData();
	
	return read_data;
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_OpenDisplay()
{
	TFTLCD_WriteRegData(R7,0x0173); 
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_CloseDisplay()
{
	TFTLCD_WriteRegData(R7, 0x0);
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数:
*			mode----扫描模式
* 返    回:	
*******************************************************************************/
void TFTLCD_SetScanMode(uint8_t mode)
{
	uint16_t regval=0;
	uint8_t dir_reg=0;
	
#if USE_HORIZONTAL
	switch(mode) //方向转换
	{
		case 0:mode=6;break;
		case 1:mode=7;break;
		case 2:mode=4;break;
		case 3:mode=5;break;
		case 4:mode=1;break;
		case 5:mode=0;break;
		case 6:mode=3;break;
		case 7:mode=2;break;	     
	}		
#endif	
	switch(mode)
	{
			case L2R_U2D://从左到右,从上到下
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://从左到右,从下到上
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://从右到左,从上到下
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://从右到左,从下到上
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://从上到下,从左到右
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://从上到下,从右到左
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://从下到上,从左到右
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://从下到上,从右到左
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 	
			default:
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;	
	}
	//
	dir_reg = 0x0003;
	regval|=1<<12;  
	TFTLCD_WriteReg(dir_reg);
	TFTLCD_WriteData(regval);
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_CoordinatesSet(uint16_t x, uint16_t y)
{
	
#if USE_HORIZONTAL==1 
	x=319-x;
	//TFTLCD_WriteReg(R32);
	//TFTLCD_WriteData(y);
	TFTLCD_WriteRegData(R32, y);
	//TFTLCD_WriteReg(R33);
	//TFTLCD_WriteData(x);
	TFTLCD_WriteRegData(R33, x);
#else 
	//TFTLCD_WriteReg(R32);
	//TFTLCD_WriteData(x);
	TFTLCD_WriteRegData(R32, x);
	//TFTLCD_WriteReg(R33);
	//TFTLCD_WriteData(y);
	TFTLCD_WriteRegData(R33, y);
#endif
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_DrawPoint(uint16_t x, uint16_t y , uint16_t point_color)
{	
	TFTLCD_CoordinatesSet(x, y);
	TFTLCD_WriteReg(R34);
	TFTLCD_WriteData(point_color);
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_Clear(uint16_t colour)
{	
	uint32_t index;
	
	TFTLCD_CoordinatesSet(0, 0);
	TFTLCD_WriteReg(R34);

	for(index=0; index<76800; index++)
	{   
		TFTLCD_WriteData(colour);
	}
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_PrintChar(uint16_t x, uint16_t y, uint8_t c )
{	
	uint8_t _index, _temp, _jdex;
	uint16_t x0 = x;
	//计算偏移
	c = c - ' ';
	//判断越界
	if(x > MAX_CHAR_POSX || y > MAX_CHAR_POSY)
		return;
		
	if(Display_MODE == 0)
	{
		for(_index=0; _index<Display_SIZE; _index++)
		{
			if(Display_SIZE == 12)
				_temp = asc2_1206[c][_index];
			else
				_temp = asc2_1608[c][_index];
			
			for(_jdex=0; _jdex<Display_SIZE/2; _jdex++)
			{   
				if(_temp&0x01)
					TFTLCD_DrawPoint(x, y , POINT_COLOR);
				else
					TFTLCD_DrawPoint(x, y , BACK_COLOR);;
				
				_temp >>= 1;
				x++;
			}
			x = x0;
			y++;
		}
	}
	else //非叠加方式
	{	
		for(_index=0; _index<Display_SIZE; _index++)
		{
			if(Display_SIZE == 12)
				_temp = asc2_1206[c][_index];
			else
				_temp = asc2_1608[c][_index];
				
			for(_jdex=0; _jdex<Display_SIZE/2; _jdex++)	
			{
				if(_temp&0x01)
					TFTLCD_DrawPoint(x + _jdex, y + _index, POINT_COLOR);
				
				_temp >>= 1;
			}
		}
	}
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_PrintString(uint16_t x, uint16_t y , uint8_t *pstr)
{
	while(*pstr != '\0')
	{
		if(x > MAX_CHAR_POSX)
		{
			x = 0;
			if(Display_SIZE == 16)
				y += 16;
			else if(Display_SIZE == 12)
				y += 12;
		}
		if(y > MAX_CHAR_POSY)
		{
			x = y = 0;
			return;
		}
		TFTLCD_PrintChar(x, y ,*pstr);
		if(Display_SIZE == 16)
			x += 8;
		else if(Display_SIZE == 12)
			x += 6;
		pstr++;
	}

}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_PrintUint16(uint16_t x, uint16_t y, uint16_t num, uint8_t mode)
{
	uint8_t buf[6], _index;
	
	if(mode == DEC)
	{	
		if(num < 100)
		{
			buf[0] = num / 10 + '0';
			buf[1] = num % 10 + '0';
			buf[2] = '\0';
		}
		else if(num < 1000)
		{
			buf[0] = num / 100 + '0';
			buf[1] = num / 10 % 10 + '0';
			buf[2] = num %10 + '0';
			buf[3] = '\0';			
		}
		else if(num < 10000)
		{
			buf[0] = num /  1000 + '0';
			buf[1] = num / 100 % 10 + '0';
			buf[2] = num / 10 % 10 + '0';
			buf[3] = num % 10 + '0';
			buf[4] = '\0';			
		}
		else if(num <= 65535)
		{
			buf[0] = num / 10000 + '0';
			buf[1] = num / 1000 % 10 + '0';
			buf[2] = num / 100 % 10 + '0';
			buf[3] = num / 10 % 10 + '0';
			buf[4] = num % 10 + '0';
			buf[5] = '\0';				
		}
		TFTLCD_PrintString(x, y , buf);
	}
	else if(mode == HEX)
	{	
		if(num < 256)
		{
			buf[0] = num / 16;
			buf[1] = num % 16;
			buf[2] = '\0';
			for(_index=0; _index<2; _index++)
			{
				if(buf[_index] < 10)
					buf[_index] += '0';
				else
					buf[_index] += 55;
			}
		}
		else if(num <= 65535 )
		{
			buf[0] = num / (16*16*16);
			buf[1] = num / (16*16) % 16;
			buf[2] = num / 16 % 16;
			buf[3] = num % 16;
			buf[4] = '\0';
			for(_index=0; _index<4; _index++)
			{
				if(buf[_index] < 10)
					buf[_index] += '0';
				else
					buf[_index] += 55;
			}			
		}
		TFTLCD_PrintString(x, y , buf);
	}
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_ClearRow(uint16_t y)
{
	TFTLCD_PrintString(0, y, (uint8_t *)"                                       ");
}
/*******************************************************************************
* 函 数 名:	
* 功    能:	
* 参    数：
* 返    回:	
*******************************************************************************/
void TFTLCD_Init( void )
{	
	//uint16_t DeviceCode;
	//uint8_t H;
	//uint8_t L;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ENABLE THE CLOCK SOURE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); 
	//Disable the SWJ_JTAGD 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	//configure the control IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;	   //GPIO_Pin_10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	GPIO_SetBits(GPIOC,GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6);
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	//configure the data port
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); //GPIOB
	GPIO_SetBits(GPIOB,GPIO_Pin_All);
	
	Delayms(50); // delay 50 ms 
	TFTLCD_WriteReg(0x0000);
	TFTLCD_WriteData(0x0001);
	Delayms(50); // delay 50 ms 	
	
	//DeviceCode = TFTLCD_ReadReg(0x0000);
	//H = DeviceCode / 256;
	//L = DeviceCode % 256;
	//USART1_PrintChar(DeviceCode);
	//USART1_PrintChar(H);
	//USART1_PrintChar(L);
	
	TFTLCD_WriteRegData(0x00e7,0x0010);      
	TFTLCD_WriteRegData(0x0000,0x0001);//开启内部时钟
	TFTLCD_WriteRegData(0x0001,0x0100);     
	TFTLCD_WriteRegData(0x0002,0x0700);//电源开启                    
	//LCD_WriteReg(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
	//DRIVE TABLE(寄存器 03H)
	//BIT3=AM BIT4:5=ID0:1
	//AM ID0 ID1   FUNCATION
	// 0  0   0	   R->L D->U
	// 1  0   0	   D->U	R->L
	// 0  1   0	   L->R D->U
	// 1  1   0    D->U	L->R
	// 0  0   1	   R->L U->D
	// 1  0   1    U->D	R->L
	// 0  1   1    L->R U->D 正常就用这个.
	// 1  1   1	   U->D	L->R
	TFTLCD_WriteRegData(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
	TFTLCD_WriteRegData(0x0004,0x0000);                                   
	TFTLCD_WriteRegData(0x0008,0x0207);	           
	TFTLCD_WriteRegData(0x0009,0x0000);         
	TFTLCD_WriteRegData(0x000a,0x0000);//display setting         
	TFTLCD_WriteRegData(0x000c,0x0001);//display setting          
	TFTLCD_WriteRegData(0x000d,0x0000);//0f3c          
	TFTLCD_WriteRegData(0x000f,0x0000);
	//电源配置
	TFTLCD_WriteRegData(0x0010,0x0000);   
	TFTLCD_WriteRegData(0x0011,0x0007);
	TFTLCD_WriteRegData(0x0012,0x0000);                                                                 
	TFTLCD_WriteRegData(0x0013,0x0000);                 
	Delayms(50); 
	TFTLCD_WriteRegData(0x0010,0x1590);   
	TFTLCD_WriteRegData(0x0011,0x0227);
	Delayms(50); 
	TFTLCD_WriteRegData(0x0012,0x009c);                  
	Delayms(50); 
	TFTLCD_WriteRegData(0x0013,0x1900);   
	TFTLCD_WriteRegData(0x0029,0x0023);
	TFTLCD_WriteRegData(0x002b,0x000e);
	Delayms(50); 
	TFTLCD_WriteRegData(0x0020,0x0000);                                                            
	TFTLCD_WriteRegData(0x0021,0x013f);           
	Delayms(50); 
	//伽马校正
	TFTLCD_WriteRegData(0x0030,0x0007); 
	TFTLCD_WriteRegData(0x0031,0x0707);   
	TFTLCD_WriteRegData(0x0032,0x0006);
	TFTLCD_WriteRegData(0x0035,0x0704);
	TFTLCD_WriteRegData(0x0036,0x1f04); 
	TFTLCD_WriteRegData(0x0037,0x0004);
	TFTLCD_WriteRegData(0x0038,0x0000);        
	TFTLCD_WriteRegData(0x0039,0x0706);     
	TFTLCD_WriteRegData(0x003c,0x0701);
	TFTLCD_WriteRegData(0x003d,0x000f);
	Delayms(50); 
	TFTLCD_WriteRegData(0x0050,0x0000); //水平GRAM起始位置 
	TFTLCD_WriteRegData(0x0051,0x00ef); //水平GRAM终止位置                    
	TFTLCD_WriteRegData(0x0052,0x0000); //垂直GRAM起始位置                    
	TFTLCD_WriteRegData(0x0053,0x013f); //垂直GRAM终止位置  
	
	TFTLCD_WriteRegData(0x0060,0xa700);        
	TFTLCD_WriteRegData(0x0061,0x0001); 
	TFTLCD_WriteRegData(0x006a,0x0000);
	TFTLCD_WriteRegData(0x0080,0x0000);
	TFTLCD_WriteRegData(0x0081,0x0000);
	TFTLCD_WriteRegData(0x0082,0x0000);
	TFTLCD_WriteRegData(0x0083,0x0000);
	TFTLCD_WriteRegData(0x0084,0x0000);
	TFTLCD_WriteRegData(0x0085,0x0000);
  
	TFTLCD_WriteRegData(0x0090,0x0010);     
	TFTLCD_WriteRegData(0x0092,0x0000);  
	TFTLCD_WriteRegData(0x0093,0x0003);
	TFTLCD_WriteRegData(0x0095,0x0110);
	TFTLCD_WriteRegData(0x0097,0x0000);        
	TFTLCD_WriteRegData(0x0098,0x0000);  
	//开启显示设置    
	TFTLCD_WriteRegData(0x0007,0x0133);   
	TFTLCD_WriteRegData(0x0020,0x0000);                                                            
	TFTLCD_WriteRegData(0x0021,0x013f);	
	//设置扫描方式和背景颜色
	TFTLCD_SetScanMode(DEF_SCAM_MODE);
	TFTLCD_Clear(BACK_COLOR);
	//点亮背光
	LCD_LED = 1;
}


/**************************** END OF FILE *************************************/

