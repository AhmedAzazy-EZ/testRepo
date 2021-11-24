#include <stm32f446xx.h>
#include "Driver_USART.h"

volatile uint32_t flag = 0;

static void usart1_callback(uint32_t event);

extern ARM_DRIVER_USART Driver_USART1;
ARM_DRIVER_USART * _usart1 = &Driver_USART1;
// Receive data
uint8_t txBuffer[15] = "Ahmed Azazy\n";
uint8_t rxBuffer[15];
int main()
{
	
	
	RCC->AHB1ENR|=(1<<0);
	GPIOA->MODER|=(1<<10);
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
_usart1->Control(ARM_USART_CONTROL_RX, 1);
	_usart1->Send(txBuffer , 15);

	_usart1->Receive(rxBuffer , 15);
	//-------------------------------------------------//

	//here we block the whole operation till we receive our 15 character
	//if you don't add this line , the code will continue and when 15 character 
	//are received the interrupt will get called which will
	//call the call back function

	/*actually each char receive will call an interrupt but the call back will be called
	only when 15 chars are received xD*/
	while(_usart1->GetRxCount()< 15);
	
	
 while(1)
 {
 
		GPIOA->ODR^=(1<<5);
	 for(volatile uint32_t i = 0 ; i < 800000 ;i++);
 }
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
 
 else if(event == ARM_USART_EVENT_RECEIVE_COMPLETE )
 {
	 //turn off on board led when 15 characters are received
	//	RCC->AHB1ENR&=~(1<<0);
 }
 else
 {
 /* Processing for communication error is written */
 }
}

