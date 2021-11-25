/*
 *  SD_Application.h
 *
 *  Created on: NOV 18, 2021
 *      Author: Ahmed Azazy
 */
 
 
/*****************NOTE******************

* This file is application specific

***************************************/


#ifndef APP_SD_H_
#define APP_SD_H_


#include <stm32f10x.h>
#include "sdcard.h"


#define SD_CARD		1

#define SD_FILE_NAME ((char *)"test.txt")
	
#define SD_BUFFER_MAX_SIZE ((uint32_t)50)

typedef struct
{
	FIL  * _SD_file;
	uint8 * _SD_TxBuffer;
	uint8 * _SD_RxBuffer;
	char _SD_fileName[50];
	uint32_t bufferMaxSize;
	uint32 readIndex;
	uint32 writeIndex;
}_SD_t;




/****************Prototypes**************/

#ifdef __cplusplus
 extern "C" {
#endif
	 
void APP_SD_init(_SD_t * P_SD);
Std_ReturnType APP_SD_Read_Index(_SD_t * P_SD);
Std_ReturnType APP_SD_write_Indexe(_SD_t * P_SD);
Std_ReturnType SD_nwrite(_SD_t * P_SD , uint32 size);
Std_ReturnType SD_nRead(_SD_t * P_SD , uint32 size);

#ifdef __cplusplus
 }
 
#endif
#endif

