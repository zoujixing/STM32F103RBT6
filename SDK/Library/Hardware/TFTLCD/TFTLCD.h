/*******************************************************************************
File Name	 	  :  
Author   	 	  :  
Software Revision :  2013-12-21

Description	      :  

Copyright (c) 2013 ZOZ technology 

The software is released by ZOZ technology.The software is mainly used for learning 
and testing.The software is provided "AS IS", without warranty of any kind, express 
or implied. Your use of this software is completely free of charge. You can use it 
without any limitation,e.g.,transplantation,delete,modify,copy,merge and spread it. 
At the same time, using of this software means that you agree to bear any direct or 
indirect liability and loss brought by this software.

You can visit www.zozstudio.com to submit your qustions or get more available 
informations about this software.
*******************************************************************************/

/* prevent from redefinition ------------------------------------------------ */
#ifndef TFTLCD_H_
#define TFTLCD_H_

/* needed include files ----------------------------------------------------- */
#include "stm32f10x.h"
#include "delay.h"


/* macro definition --------------------------------------------------------- */

#define USE_HORIZONTAL  0	//定义是否使用横屏 		0,不使用.1,使用.

#if USE_HORIZONTAL==1
#define MAX_CHAR_POSX 312
#define MAX_CHAR_POSY 232 
#else     
#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 312
#endif 

#define GPIO_BIT_ADDR(addr, bitnum)  *(volatile unsigned long *)( (addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2) )
//信号线定义
#define LCD_RD	GPIO_BIT_ADDR(0x4001100C, 6) //GPIOC_6 read
#define LCD_WR	GPIO_BIT_ADDR(0x4001100C, 7) //GPIOC_7 write
#define LCD_RS	GPIO_BIT_ADDR(0x4001100C, 8) //command/data
#define LCD_CS	GPIO_BIT_ADDR(0x4001100C, 9) //CE

#define LCD_LED	GPIO_BIT_ADDR(0x4001100C, 10)
//数据端口
#define DATAOUT(x) GPIOB->ODR=x; //DATA OUTPUT
#define DATAIN     GPIOB->IDR;   //DATA INPUT
//扫描方式
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上
#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左
#define DEF_SCAM_MODE  L2R_U2D

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

//显示开关寄存器
#define R7   0x07
//坐标设置寄存器
#define R32  0x20  
#define R33  0x21	
//写GRAM寄存器
#define R34	 0x22

//Number Display Mode
#define DEC 0
#define HEX 1
//display size
#define SIZE_12 12
#define SIZE_16 16
//display mode
#define MODE_0 0
#define MODE_1 1

/* typedef ------------------------------------------------------------------ */


/* global function declare -------------------------------------------------- */
void TFTLCD_Init( void );

void TFTLCD_OpenDisplay( void );
void TFTLCD_CloseDisplay( void );
void TFTLCD_OpenBackLight( void );
void TFTLCD_CloseBackLight( void );
	
void TFTLCD_CoordinatesSet(uint16_t x, uint16_t y);
void TFTLCD_DrawPoint(uint16_t x, uint16_t y , uint16_t point_color);

void TFTLCD_SetScanMode(uint8_t mode);
void TFTLCD_SetColor(uint16_t point_color, uint16_t back_clor);
void TFTLCD_SetDisplaySize(uint8_t size);
void TFTLCD_SetDisplayMode(uint8_t mode);

void TFTLCD_Clear(uint16_t colour);
void TFTLCD_ClearRow(uint16_t y);
void TFTLCD_PrintChar(uint16_t x, uint16_t y, uint8_t c );
void TFTLCD_PrintString(uint16_t x, uint16_t y , uint8_t *pstr);
void TFTLCD_PrintUint16(uint16_t x, uint16_t y, uint16_t num, uint8_t mode);
#endif

/**************************** END OF FILE *************************************/

