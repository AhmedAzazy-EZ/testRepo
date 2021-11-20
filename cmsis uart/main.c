#include <stm32f446xx.h>
#include "Driver_USART.h"

volatile uint32_t flag = 0;

static void usart1_callback(uint32_t event);

extern ARM_DRIVER_USART Driver_USART1;
ARM_DRIVER_USART * _usart1 = &Driver_USART1;
// Receive data
uint8_t txBuffer[15] = "Ahmed Azazy\n";
int main()
{
	
volatile	uint32_t args = ARM_USART_MODE_ASYNCHRONOUS | ARM_USART_DATA_BITS_8 |
									ARM_USART_PARITY_NONE  | ARM_USART_STOP_BITS_1  |
									ARM_USART_FLOW_CONTROL_NONE | ARM_USART_CONTROL_TX;
	
	_usart1->Initialize(usart1_callback);
	_usart1->PowerControl(ARM_POWER_FULL);
	_usart1->Control(ARM_USART_MODE_ASYNCHRONOUS | 
														ARM_USART_DATA_BITS_8 |
														ARM_USART_PARITY_NONE |
														ARM_USART_STOP_BITS_1 |
														ARM_USART_FLOW_CONTROL_NONE, 9600);	
	_usart1->Control(ARM_USART_CONTROL_TX, 1);
	_usart1->Send(txBuffer , 15);
	
 while(1);
}
/***********************************************************************************
* callback function
*************************************************************************************/
static void usart1_callback(uint32_t event)
{
 if (0 != (event & ARM_USART_EVENT_SEND_COMPLETE ))
 {
		flag++;
 }
 else
 {
 /* Processing for communication error is written */
 }
}
