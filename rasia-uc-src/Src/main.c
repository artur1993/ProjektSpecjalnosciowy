/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "stdlib.h"
#define ADDRESS 0xc1
#define START 0x12
#define READ 0x00

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
int use1[7] = {1, 1, 1, 1, 1, 0, 0};
int use2[7] = {1, 1, 1, 1, 1, 0, 0};
int use3[7] = {1, 1, 1, 1, 1, 0, 0};

GPIO_TypeDef * gpio1[7] = {GPIOC, GPIOA, GPIOA, GPIOA, GPIOB, GPIOC, GPIOC};
GPIO_TypeDef * gpio2[7] = {GPIOA, GPIOA, GPIOC, GPIOB, GPIOB, GPIOA, GPIOA};
GPIO_TypeDef * gpio3[6] = {GPIOB, GPIOB, GPIOC, GPIOC, GPIOC, GPIOB};

uint16_t pin1[7] = {GPIO_PIN_2, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_0};
uint16_t pin2[7] = {GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_7, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_2, GPIO_PIN_3};
uint16_t pin3[6] = {GPIO_PIN_15, GPIO_PIN_14, GPIO_PIN_12, GPIO_PIN_11, GPIO_PIN_10, GPIO_PIN_8};

uint8_t data_received[5];
uint8_t data_sent[82];
uint8_t coef_max[160];
uint8_t data_max[80];
uint8_t start = 0x00;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C3_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void send_data(){
	int i = 0;
	for(i = 0; i < 82; i++){
		data_sent[i] = 0;
	}
	data_sent[0] = 0xD1;
	data_sent[81] += data_sent[0];
	for(i = 1; i < 81; i++){
		data_sent[i] = data_max[i-1];
		data_sent[81] += data_sent[i];
	}
	HAL_UART_Transmit(&huart1, data_sent, 82, 10);
}


void send_coef(){
	int i = 0;
	for(i = 0; i < 82; i++){
		data_sent[i] = 0;
	}
	data_sent[0] = 0xC1;
	data_sent[81] += data_sent[0];
	for(i = 1; i < 81; i++){
		data_sent[i] = coef_max[i-1];
		data_sent[81] += data_sent[i];
	}
	HAL_UART_Transmit(&huart1, data_sent, 82, 10);
	for(i = 0; i < 82; i++){
		data_sent[i] = 0;
	}
	data_sent[0] = 0xC2;
	data_sent[81] += data_sent[0];
	for(i = 1; i < 81; i++){
		data_sent[i] = coef_max[i-1+80];
		data_sent[81] += data_sent[i];
	}
	HAL_UART_Transmit(&huart1, data_sent, 82, 10);
}


void reset_all(){
	int i = 0;
	for(i = 0; i < 80; i++){
		data_max[i] = 0;
	}
	for(i = 0; i < 160; i++){
		coef_max[i] = 0;
	}
	for(i = 0; i < 7; i++){
		if(use1[i]){
			HAL_GPIO_WritePin(gpio1[i],pin1[i],GPIO_PIN_SET);
		}
		if(use2[i]){
			HAL_GPIO_WritePin(gpio2[i],pin2[i],GPIO_PIN_SET);
		}
		if(use3[i]){
			HAL_GPIO_WritePin(gpio3[i],pin3[i],GPIO_PIN_SET);
		}
		HAL_Delay(10);
		if(use1[i]){
			HAL_GPIO_WritePin(gpio1[i],pin1[i],GPIO_PIN_RESET);
		}
		if(use2[i]){
			HAL_GPIO_WritePin(gpio2[i],pin2[i],GPIO_PIN_RESET);
		}
		if(use3[i]){
			HAL_GPIO_WritePin(gpio3[i],pin3[i],GPIO_PIN_RESET);
		}
	}
}


void read_coef_all(){
	int i = 0;
	for(i = 0; i < 160; i++){
		coef_max[i] = 0;
	}
	for(i = 0; i < 7; i++){
		if(use1[i]){
			HAL_GPIO_WritePin(gpio1[i],pin1[i],GPIO_PIN_SET);
		}
		if(use2[i]){
			HAL_GPIO_WritePin(gpio2[i],pin2[i],GPIO_PIN_SET);
		}
		if(use3[i]){
			HAL_GPIO_WritePin(gpio3[i],pin3[i],GPIO_PIN_SET);
		}
		HAL_Delay(10);
		if(use1[i]){
			HAL_I2C_Mem_Read(&hi2c1, (uint16_t)ADDRESS, 0x04, 1, &coef_max[i*8], 8, 10);
		}
		if(use2[i]){
			HAL_I2C_Mem_Read(&hi2c2, (uint16_t)ADDRESS, 0x04, 1, &coef_max[i*8 + 56], 8, 10);
		}
		if(use3[i]){
			HAL_I2C_Mem_Read(&hi2c3, (uint16_t)ADDRESS, 0x04, 1, &coef_max[i*8 + 112], 8, 10);
		}
		if(use1[i]){
			HAL_GPIO_WritePin(gpio1[i],pin1[i],GPIO_PIN_RESET);
		}
		if(use2[i]){
			HAL_GPIO_WritePin(gpio2[i],pin2[i],GPIO_PIN_RESET);
		}
		if(use3[i]){
			HAL_GPIO_WritePin(gpio3[i],pin3[i],GPIO_PIN_RESET);
		}
	}
}


void read_data_all(){
	int i = 0;
	for(i = 0; i < 80; i++){
		data_max[i] = 0;
	}
	for(i = 0; i < 7; i++){
		if(use1[i]){
			HAL_GPIO_WritePin(gpio1[i],pin1[i],GPIO_PIN_SET);
		}
		if(use2[i]){
			HAL_GPIO_WritePin(gpio2[i],pin2[i],GPIO_PIN_SET);
		}
		if(use3[i]){
			HAL_GPIO_WritePin(gpio3[i],pin3[i],GPIO_PIN_SET);
		}
		if(use1[i]){
			HAL_I2C_Mem_Write(&hi2c1, (uint16_t)0xc0, START, 1, &start, 1, 10);
		}
		if(use2[i]){
			HAL_I2C_Mem_Write(&hi2c2, (uint16_t)0xc0, START, 1, &start, 1, 10);
		}
		if(use3[i]){
			HAL_I2C_Mem_Write(&hi2c3, (uint16_t)0xc0, START, 1, &start, 1, 10);
		}
		HAL_Delay(10);
		if(use1[i]){
			HAL_I2C_Mem_Read(&hi2c1, (uint16_t)ADDRESS, 0x00, 1, &data_max[i*4], 8, 10);
		}
		if(use2[i]){
			HAL_I2C_Mem_Read(&hi2c2, (uint16_t)ADDRESS, 0x00, 1, &data_max[i*4 + 28], 8, 10);
		}
		if(use3[i]){
			HAL_I2C_Mem_Read(&hi2c3, (uint16_t)ADDRESS, 0x00, 1, &data_max[i*4 + 56], 8, 10);
		}
		if(use1[i]){
			HAL_GPIO_WritePin(gpio1[i],pin1[i],GPIO_PIN_RESET);
		}
		if(use2[i]){
			HAL_GPIO_WritePin(gpio2[i],pin2[i],GPIO_PIN_RESET);
		}
		if(use3[i]){
			HAL_GPIO_WritePin(gpio3[i],pin3[i],GPIO_PIN_RESET);
		}
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	send_coef();
	HAL_UART_Receive_DMA(&huart1, data_received, 1);
}
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_I2C3_Init();
  MX_I2C2_Init();
  MX_I2C1_Init();

  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_DMA(&huart1, data_received, 1);
  HAL_Delay(10);
  reset_all();
  read_coef_all();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  read_data_all();
	  send_data();
	  HAL_Delay(100);
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C2 init function */
static void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C3 init function */
static void MX_I2C3_Init(void)
{

  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 400000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|LD2_Pin|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC7 
                           PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 LD2_Pin PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|LD2_Pin|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB14 PB15 PB4 
                           PB5 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
