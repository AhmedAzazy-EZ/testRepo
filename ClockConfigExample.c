#include "stm32f4xx_hal.h"
#include "main.h"

void SystemClock_Config(void);

UART_HandleTypeDef _uart1;
uint8_t uart1_Txbuff[50] = "Ahmed Azazy\n\0Lol";
uint8_t uart1_Rxbuff[50];

GPIO_InitTypeDef gpio;

int main(void)
{
  HAL_Init();
	__GPIOA_CLK_ENABLE();
	__USART1_CLK_ENABLE();
	  SystemClock_Config();
	
		gpio.Pin = GPIO_PIN_9;
		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Alternate = GPIO_AF7_USART1;
		gpio.Pull = GPIO_NOPULL;
		gpio.Speed = GPIO_SPEED_FREQ_HIGH ;
		HAL_GPIO_Init(GPIOA, &gpio);
		
	
	_uart1.Instance = USART1;
	_uart1.Init.BaudRate = 9600;
	_uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	_uart1.Init.Mode = UART_MODE_TX;
	_uart1.Init.OverSampling = UART_OVERSAMPLING_16;
	_uart1.Init.Parity = UART_PARITY_NONE;
	_uart1.Init.StopBits = UART_STOPBITS_1 ;
	_uart1.Init.WordLength = UART_WORDLENGTH_8B;
	
	_uart1.pRxBuffPtr = uart1_Rxbuff;
	_uart1.pTxBuffPtr = uart1_Txbuff;
	_uart1.TxXferSize = 50;
	_uart1.RxXferSize = 50;
	HAL_UART_Init(&_uart1);
	
		RCC->AHB1ENR|=(1<<0);
		GPIOA->MODER|=(1<<10);
		SystemCoreClockUpdate();
		volatile uint32_t i = 0;
		while(1)
			{
				for(i=0;i< 8000000;i++){}
					GPIOA->ODR^=(1<<5);
					
					HAL_UART_Transmit(&_uart1, _uart1.pTxBuffPtr , _uart1.TxXferSize , 1000);
			}
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
