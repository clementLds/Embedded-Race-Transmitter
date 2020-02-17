/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2020 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "uoled.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum { false, true } bool;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define signal_tempo 0x0001
#define signal_capture 0x0002
#define signal_debut 0x0003
#define signal_passage 0x0004
#define signal_lcd 0x0005
#define signal_envoi 0x0006

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;

osThreadId DecodageHandle;
osThreadId AfficheurHandle;
osThreadId GestionToursHandle;
osThreadId GestionRadioHandle;
osThreadId ReinitHandle;
osTimerId HorlogeHandle;
/* USER CODE BEGIN PV */
bool anomalie;
unsigned int nbTour1;
unsigned int nbTour2;
unsigned int endroit;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_UART4_Init(void);
void StartDecodage(void const * argument);
void StartAfficheur(void const * argument);
void StartGestionTours(void const * argument);
void StartGestionRadio(void const * argument);
void StartReinit(void const * argument);
void CallbackHorloge(void const * argument);

/* USER CODE BEGIN PFP */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
PUTCHAR_PROTOTYPE
{
HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	gfx_Cls();
	setbaudWait(115200,BAUD_115200);

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of Horloge */
  osTimerDef(Horloge, CallbackHorloge);
  HorlogeHandle = osTimerCreate(osTimer(Horloge), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
	osTimerStart(HorlogeHandle,1000);
	
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of Decodage */
  osThreadDef(Decodage, StartDecodage, osPriorityNormal, 0, 128);
  DecodageHandle = osThreadCreate(osThread(Decodage), NULL);

  /* definition and creation of Afficheur */
  osThreadDef(Afficheur, StartAfficheur, osPriorityNormal, 0, 128);
  AfficheurHandle = osThreadCreate(osThread(Afficheur), NULL);

  /* definition and creation of GestionTours */
  osThreadDef(GestionTours, StartGestionTours, osPriorityNormal, 0, 128);
  GestionToursHandle = osThreadCreate(osThread(GestionTours), NULL);

  /* definition and creation of GestionRadio */
  osThreadDef(GestionRadio, StartGestionRadio, osPriorityNormal, 0, 128);
  GestionRadioHandle = osThreadCreate(osThread(GestionRadio), NULL);

  /* definition and creation of Reinit */
  osThreadDef(Reinit, StartReinit, osPriorityNormal, 0, 128);
  ReinitHandle = osThreadCreate(osThread(Reinit), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDecodage */
/**
  * @brief  Function implementing the Decodage thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDecodage */
void StartDecodage(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartAfficheur */
/**
* @brief Function implementing the Afficheur thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAfficheur */
void StartAfficheur(void const * argument)
{
  /* USER CODE BEGIN StartAfficheur */
	gfx_RectangleFilled(0,0,19,19,BLACK);
	txt_BGcolour(BLACK) ;
	txt_FGcolour(WHITE) ;
	txt_MoveCursor(4,4);
	putCH('N');
	txt_MoveCursor(5,4);
	putCH('o');
	txt_MoveCursor(6,4);
	putCH('m');
	txt_MoveCursor(7,4);
	putCH('b');
	txt_MoveCursor(8,4);
	putCH('r');
	txt_MoveCursor(9,4);
	putCH('e');
	txt_MoveCursor(4,5);
	putCH('d');
	txt_MoveCursor(5,5);
	putCH('e');
	txt_MoveCursor(7,5);
	putCH('t');
	txt_MoveCursor(8,5);
	putCH('o');
	txt_MoveCursor(9,5);
	putCH('u');
	txt_MoveCursor(10,5);
	putCH('r');
	txt_MoveCursor(11,5);
	putCH('s');
	txt_MoveCursor(13,5);
	putCH(':');
	
  /* Infinite loop */
  for(;;)
  {
    osSignalWait(signal_lcd, osWaitForever);
		printf("Afficheur : \n\r");
		gfx_RectangleFilled(4,8,5,10,BLACK);
		txt_MoveCursor(4,8);
		if(nbTour1 < nbTour2){
			putINT(nbTour1/100);
			txt_MoveCursor(5,8);
			putINT(nbTour1%100/10);
			txt_MoveCursor(6,8);
			putINT(nbTour1%100%10);
		}else{
			putINT(nbTour2/100);
			txt_MoveCursor(5,8);
			putINT(nbTour2%100/10);
			txt_MoveCursor(6,8);
			putINT(nbTour2%100%10);
		}
  }
  /* USER CODE END StartAfficheur */
}

/* USER CODE BEGIN Header_StartGestionTours */
/**
* @brief Function implementing the GestionTours thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGestionTours */
void StartGestionTours(void const * argument)
{
  /* USER CODE BEGIN StartGestionTours */
	anomalie = false;
	
  /* Infinite loop */
  for(;;)
  {
    osSignalWait(signal_passage, osWaitForever);
		if(endroit==1){
			nbTour1++;
		}else{
			nbTour2++;
		}
		if(abs(nbTour1-nbTour2)<2){
			anomalie = false;
		}else{
			anomalie = true;
		}
	if(anomalie) {
		printf("GestionTours : anomalie = 1\n\r");
	}else{
		printf("GestionTours : anomalie = 0\n\r");
	}
	printf("nbTour1 = %d, nbTour2 = %d\n\r", nbTour1, nbTour2);
	osSignalSet(AfficheurHandle, signal_lcd);
	osSignalSet(GestionRadioHandle, signal_envoi);
  }
  /* USER CODE END StartGestionTours */
}

/* USER CODE BEGIN Header_StartGestionRadio */
/**
* @brief Function implementing the GestionRadio thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGestionRadio */
void StartGestionRadio(void const * argument)
{
  /* USER CODE BEGIN StartGestionRadio */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartGestionRadio */
}

/* USER CODE BEGIN Header_StartReinit */
/**
* @brief Function implementing the Reinit thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReinit */
void StartReinit(void const * argument)
{
  /* USER CODE BEGIN StartReinit */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartReinit */
}

/* CallbackHorloge function */
void CallbackHorloge(void const * argument)
{
  /* USER CODE BEGIN CallbackHorloge */
  printf("horloge : \n\r");
	int r = rand();
	endroit = r%2;
	osSignalSet (GestionToursHandle, signal_passage);
	nbTour1++;	
	
	
  /* USER CODE END CallbackHorloge */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
