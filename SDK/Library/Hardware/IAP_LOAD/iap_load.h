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
#ifndef IAP_LOAD_H_
#define IAP_LOAD_H_

/* needed include files ----------------------------------------------------- */
#include "stdint.h"

/* macro definition --------------------------------------------------------- */
#define FLASH_APP_ADDR		0x0800D000

/* typedef ------------------------------------------------------------------ */
typedef  void (*iapfun)(void);

/* global function declare -------------------------------------------------- */

void iap_load_app(uint32_t app_addr);
#endif

/**************************** END OF FILE *************************************/
