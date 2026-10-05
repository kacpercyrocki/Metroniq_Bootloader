/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
     PC9   ------> RCC_MCO_2
*/
void MX_GPIO_Init(void)
{


	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */

	  HAL_GPIO_WritePin(LAN_RST_GPIO_Port, LAN_RST_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(C2_CS_GPIO_Port, C2_CS_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(C1_CS_GPIO_Port, C1_CS_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(SYNC_GPIO_Port, SYNC_Pin, GPIO_PIN_SET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOE, REL1_Pin|REL2_Pin, GPIO_PIN_RESET);
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(V_CS_GPIO_Port, V_CS_Pin, GPIO_PIN_SET);

	  /*Configure GPIO pins : C2_CS_Pin LAN_RST_Pin SYNC_Pin C1_CS_Pin
	                           MEM_RST_Pin */
	  GPIO_InitStruct.Pin = SYNC_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(SYNC_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = C2_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(C2_CS_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = C1_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(C1_CS_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LAN_RST_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LAN_RST_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : C1_DRDY_Pin SW_RST_Pin V_DRDY_Pin */
	  GPIO_InitStruct.Pin = C2_DRDY_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(C2_DRDY_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = C1_DRDY_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(C1_DRDY_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = V_DRDY_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(V_DRDY_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = SW_RST_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(SW_RST_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : REL1_Pin REL2_Pin V_CS_Pin WIFI_BOOT_Pin */
	  GPIO_InitStruct.Pin = V_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(V_CS_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = REL1_Pin|REL2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = ISO_EN_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(ISO_EN_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : PC9 */
	  GPIO_InitStruct.Pin = GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pins : SPI_CS_Pin CHIP_EN_Pin */
	  /* EXTI interrupt init*/
	  HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
	  HAL_NVIC_DisableIRQ(EXTI2_IRQn);

	  HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
	  HAL_NVIC_DisableIRQ(EXTI3_IRQn);

	  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
	  HAL_NVIC_DisableIRQ(EXTI4_IRQn);

	  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
	  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);

	  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
	  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
