/*
 *  SD_Application.c
 *
 *  Created on: NOV 18, 2021
 *      Author: Ahmed Azazy
 */
 
 
/***************** NOTE ******************

* This file is application specific

***************************************/

#include "SD_Application.h"



uint8 EEPROM_TxBuffer[50];
uint8 EEPROM_RxBuffer[50];


extern FIL USERFile;

#if (SD_CARD == 1)


/***************** APP_SD_global vars ******************/

_SD_t _SD;

/****************************************************/
void APP_SD_init(_SD_t * P_SD)
{
	InitSDcard();
	strcpy(P_SD->_SD_fileName , SD_FILE_NAME);
	P_SD->_SD_file = &USERFile;
	P_SD->bufferMaxSize = SD_BUFFER_MAX_SIZE;
	P_SD->_SD_TxBuffer = EEPROM_TxBuffer;
	P_SD->_SD_RxBuffer = EEPROM_RxBuffer;
	P_SD->readIndex = 0;
	P_SD->writeIndex = 0;
}

Std_ReturnType APP_SD_Read_Index(_SD_t * P_SD)
{

	Std_ReturnType return_type = E_NOT_OK;
	uint32 read_len=0;
	uint32 current_position=0;
	
	//get file size
	uint32 fileSize = f_size(P_SD->_SD_file);
	UINT Num_of_readBytes = 0;
	
	
	//check if the file is not corectly opened OR the file size is less than 50
	if(f_open(P_SD->_SD_file , P_SD->_SD_fileName , FA_READ | FA_OPEN_ALWAYS | FA_WRITE) != FR_OK
		|| (fileSize < 50))
	{
		f_close(P_SD->_SD_file);
		return return_type;
	}
	
	//set the read/write pointer the the readIndex
	f_lseek(P_SD->_SD_file , P_SD->readIndex);
			
	/****************************************
	Read 50 character
	store in _SD_RxBuffer
	*****************************************/
	f_read(P_SD->_SD_file , P_SD->_SD_RxBuffer , 50 , &Num_of_readBytes);
	
	//check if reached end of file
	if(Num_of_readBytes < 50)
	{
		f_close(P_SD->_SD_file);
		return return_type;
	}
	
	
	//update the readIndex
	P_SD->readIndex += 50;
	
	f_close(P_SD->_SD_file);
	return_type = E_OK;
	return return_type;  // success	
}



Std_ReturnType APP_SD_write_Indexe(_SD_t * P_SD)
{

		Std_ReturnType return_type = E_NOT_OK;
		UINT Num_of_WrittenBytes = 0;
		//check if the file is not corectly opened
		if(f_open(P_SD->_SD_file , P_SD->_SD_fileName , FA_READ | FA_OPEN_ALWAYS | FA_WRITE) != FR_OK)
	{
		f_close(P_SD->_SD_file);
		return return_type;
	}
		
	//set the read/write pointer the writeIndex
	f_lseek(P_SD->_SD_file , P_SD->writeIndex);
		
	/****************************************
	write 50 character
	load from _SD_TxBuffer
	*****************************************/
	f_write(P_SD->_SD_file , P_SD->_SD_TxBuffer , 50 , &Num_of_WrittenBytes);
	
	//update the writeIndex
	P_SD->writeIndex += 50;
	
	f_close(P_SD->_SD_file);
	return_type = E_OK;
	return return_type;  // success		
}


Std_ReturnType SD_nwrite(_SD_t * P_SD , uint32 size)
{
		Std_ReturnType return_type = E_NOT_OK;
		UINT Num_of_WrittenBytes = 0;
		//check if the file is not corectly opened
		if(f_open(P_SD->_SD_file , P_SD->_SD_fileName , FA_READ | FA_OPEN_ALWAYS | FA_WRITE) != FR_OK)
	{
		f_close(P_SD->_SD_file);
		return return_type;
	}

	//check if the size is bigger than the MAX_BUFFER_SIZE
	if(size > P_SD->bufferMaxSize )
	{
		f_close(P_SD->_SD_file);
		return return_type;
	}
	
	//set the read/write pointer the writeIndex
	f_lseek(P_SD->_SD_file , P_SD->writeIndex);
		
	/****************************************
	write N_size character
	load from _SD_TxBuffer
	*****************************************/
	f_write(P_SD->_SD_file , P_SD->_SD_TxBuffer , size , &Num_of_WrittenBytes);
	
	//update the writeIndex
	P_SD->writeIndex += size;
	
	f_close(P_SD->_SD_file);
	return_type = E_OK;
	return return_type;  // success	
	
}

Std_ReturnType SD_nRead(_SD_t * P_SD , uint32 size)
{

	Std_ReturnType return_type = E_NOT_OK;
	uint32 read_len=0;
	uint32 current_position=0;
	
	//get file size
	uint32 fileSize = f_size(P_SD->_SD_file);
	UINT Num_of_readBytes = 0;
	
	
	//check if the file is not corectly opened OR the file size is less than 50
	if(f_open(P_SD->_SD_file , P_SD->_SD_fileName , FA_READ | FA_OPEN_ALWAYS | FA_WRITE) != FR_OK
		|| (fileSize < size))
	{
		f_close(P_SD->_SD_file);
		return return_type;
	}
	
	//check if the size is bigger than the MAX_BUFFER_SIZE
	if(size > P_SD->bufferMaxSize )
	{
		f_close(P_SD->_SD_file);
		return return_type;
	}
			
	
	//set the read/write pointer the the readIndex
	f_lseek(P_SD->_SD_file , P_SD->readIndex);
			
	/****************************************
	Read N_size character
	store in _SD_RxBuffer
	*****************************************/
	f_read(P_SD->_SD_file , P_SD->_SD_RxBuffer , size , &Num_of_readBytes);
	
	//check if reached end of file
	if(Num_of_readBytes < size)
	{	
		f_close(P_SD->_SD_file);
		//you have to print an informing message
		return E_NOT_OK;
	}
	
	
	//update the readIndex
	P_SD->readIndex += size;
	
	f_close(P_SD->_SD_file);
	return_type = E_OK;
	return return_type;  // success		
}

#endif



