/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include "sys_preproc.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern volatile uint8_t state_alrm;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define sw_tilt_Pin GPIO_PIN_0
#define sw_tilt_GPIO_Port GPIOA
#define ld_heartbeat_Pin GPIO_PIN_1
#define ld_heartbeat_GPIO_Port GPIOA
#define wakeup_Pin GPIO_PIN_2
#define wakeup_GPIO_Port GPIOA
#define wakeup_EXTI_IRQn EXTI2_IRQn
#define pwr_eeprom_Pin GPIO_PIN_3
#define pwr_eeprom_GPIO_Port GPIOA
#define write_eeprom_Pin GPIO_PIN_4
#define write_eeprom_GPIO_Port GPIOA
#define hold_eeprom_Pin GPIO_PIN_0
#define hold_eeprom_GPIO_Port GPIOB
#define pwr_aud_Pin GPIO_PIN_10
#define pwr_aud_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
