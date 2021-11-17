#include <stm32f446xx.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/************_HAL_uart1_global variables************/
USART_HandleTypeDef _uart1;
uint8_t _USART1_TxBuffer[50] = "Ahmed Azazy\r\n";
/***************************************************/


/*********HAL_uart definition of low level********/

/*************************************************/

/**********GPIOA global Variables*****************/
GPIO_InitTypeDef _GPIOA;

int main(void)
{
	HAL_Init();
	if(HAL_InitTick(0) != HAL_OK)
	{
		//stuck here
		while(1);
	}
	__USART1_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	
	
	_GPIOA.Pin=	GPIO_PIN_9;
	_GPIOA.Mode = GPIO_MODE_AF_PP  ;
	_GPIOA.Pull = GPIO_NOPULL;
	_GPIOA.Alternate = GPIO_AF7_USART1;
	_GPIOA.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA , &_GPIOA);

	

	
	
	_uart1.Instance = USART1;
	_uart1.Init.BaudRate = 9600;
	_uart1.Init.WordLength = 0x0000;
	_uart1.Init.StopBits = USART_STOPBITS_1;
	_uart1.Init.Parity = USART_PARITY_NONE ;
	_uart1.Init.Mode = USART_MODE_TX | USART_MODE_RX;
	_uart1.pTxBuffPtr = _USART1_TxBuffer;
	_uart1.TxXferSize = 50;
	_uart1.TxXferCount = 12;
	HAL_USART_Init(&_uart1);


	
	
	while(1)
	{
		
		if(HAL_USART_Transmit(&_uart1,_USART1_TxBuffer, (uint16_t) 13, 100) ==
						HAL_TIMEOUT)
			{		
				HAL_USART_Transmit(&_uart1,"Failed", (uint16_t) 12, HAL_MAX_DELAY);
			}
			
			for(int i = 0 ; i < 800000 ; i++);
	
	}

}


void SysTick_Handler()
{
	
}
