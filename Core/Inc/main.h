/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LEDDriver.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct Settings_t
{
	uint8_t Channel1_Name[32];
	uint8_t Channel2_Name[32];
	uint8_t Channel3_Name[32];
	uint8_t Channel4_Name[32];
	uint8_t Channel5_Name[32];
	uint8_t Channel6_Name[32];
	uint8_t Channel7_Name[32];
	uint8_t Channel8_Name[32];
	uint8_t Channel9_Name[32];
	uint8_t Channel10_Name[32];
	uint8_t Channel11_Name[32];
	uint8_t Channel12_Name[32];
	uint8_t Channel13_Name[32];
	uint8_t Channel14_Name[32];
	uint8_t Channel15_Name[32];
	uint8_t Channel16_Name[32];

	uint8_t PhaseAssignment[16];
	uint32_t ActiveEnergy[16];
	uint32_t ReactiveEnergy[16];
	uint32_t TotalActiveEnergy;
	uint32_t TotalReactiveEnergy;

	uint8_t DHCP_Enable;
	uint8_t StaticIP[4];
	uint8_t StaticMask[4];
	uint8_t StaticGateway[4];

	uint8_t NewFWAvailable;
	uint32_t NewFWSize;
}Settings_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define MAIN_FW_ADDRESS 0x08020000
#define FW_MAX_SIZE   (0x40000 * 4)
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void I2C_TransmitData(uint16_t address, uint8_t* buffer, uint8_t count);
void I2C_ReceiveData(uint16_t address, uint8_t* buffer, uint8_t count);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define C2_DRDY_Pin GPIO_PIN_11
#define C2_DRDY_GPIO_Port GPIOC
#define C2_DRDY_EXTI_IRQn EXTI15_10_IRQn
#define C2_CS_Pin GPIO_PIN_12
#define C2_CS_GPIO_Port GPIOC
#define LAN_RST_Pin GPIO_PIN_15
#define LAN_RST_GPIO_Port GPIOB
#define SYNC_Pin GPIO_PIN_0
#define SYNC_GPIO_Port GPIOD
#define C1_CS_Pin GPIO_PIN_1
#define C1_CS_GPIO_Port GPIOD
#define C1_DRDY_Pin GPIO_PIN_2
#define C1_DRDY_GPIO_Port GPIOD
#define C1_DRDY_EXTI_IRQn EXTI2_IRQn
#define SW_RST_Pin GPIO_PIN_3
#define SW_RST_GPIO_Port GPIOD
#define SW_RST_EXTI_IRQn EXTI3_IRQn
#define REL1_Pin GPIO_PIN_3
#define REL1_GPIO_Port GPIOE
#define REL2_Pin GPIO_PIN_4
#define REL2_GPIO_Port GPIOE
#define V_DRDY_Pin GPIO_PIN_15
#define V_DRDY_GPIO_Port GPIOA
#define V_DRDY_EXTI_IRQn EXTI15_10_IRQn
#define V_CS_Pin GPIO_PIN_10
#define V_CS_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */
#define ISO_EN_Pin GPIO_PIN_5
#define ISO_EN_Port GPIOB

#define WIFI_EN_Pin GPIO_PIN_4
#define WIFI_EN_Port GPIOD
#define WIFI_IO9_Pin GPIO_PIN_7
#define WIFI_IO9_Port GPIOD

#define VDET_Pin GPIO_PIN_4
#define VDET_Port GPIOB
#define VDET_IRQn	EXTI4_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
