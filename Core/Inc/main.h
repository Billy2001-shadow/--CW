/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define POWER1_Pin GPIO_PIN_2
#define POWER1_GPIO_Port GPIOH
#define POWER2_Pin GPIO_PIN_3
#define POWER2_GPIO_Port GPIOH
#define POWER3_Pin GPIO_PIN_4
#define POWER3_GPIO_Port GPIOH
#define LED8_Pin GPIO_PIN_8
#define LED8_GPIO_Port GPIOG
#define POWER4_Pin GPIO_PIN_5
#define POWER4_GPIO_Port GPIOH
#define LED7_Pin GPIO_PIN_7
#define LED7_GPIO_Port GPIOG
#define LED6_Pin GPIO_PIN_6
#define LED6_GPIO_Port GPIOG
#define SPI5_NSS_Pin GPIO_PIN_6
#define SPI5_NSS_GPIO_Port GPIOF
#define LED5_Pin GPIO_PIN_5
#define LED5_GPIO_Port GPIOG
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOG
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOG
#define Encoder_Direction_Pin GPIO_PIN_5
#define Encoder_Direction_GPIO_Port GPIOA
#define Encoder_Direction_EXTI_IRQn EXTI9_5_IRQn
#define GREEN_LED_Pin GPIO_PIN_14
#define GREEN_LED_GPIO_Port GPIOF
/* USER CODE BEGIN Private defines */            //CW---CW
#define KEY_PRESSED_OFFSET_W ((uint16_t)1 << 0)
#define KEY_PRESSED_OFFSET_S ((uint16_t)1 << 1)
#define KEY_PRESSED_OFFSET_A ((uint16_t)1 << 2)
#define KEY_PRESSED_OFFSET_D ((uint16_t)1 << 3)
#define KEY_PRESSED_OFFSET_SHIFT ((uint16_t)1 << 4)
#define KEY_PRESSED_OFFSET_CTRL ((uint16_t)1 << 5)
#define KEY_PRESSED_OFFSET_Q ((uint16_t)1 << 6)
#define KEY_PRESSED_OFFSET_E ((uint16_t)1 << 7)
#define KEY_PRESSED_OFFSET_R ((uint16_t)1 << 8)
#define KEY_PRESSED_OFFSET_F ((uint16_t)1 << 9)
#define KEY_PRESSED_OFFSET_G ((uint16_t)1 << 10)
#define KEY_PRESSED_OFFSET_Z ((uint16_t)1 << 11)
#define KEY_PRESSED_OFFSET_X ((uint16_t)1 << 12)
#define KEY_PRESSED_OFFSET_C ((uint16_t)1 << 13)
#define KEY_PRESSED_OFFSET_V ((uint16_t)1 << 14)
#define KEY_PRESSED_OFFSET_B ((uint16_t)1 << 15)


#define Left_Press          (rc_ctrl.mouse.press_l==1)
#define Left__NoPress       (rc_ctrl.mouse.press_l==0)
#define Right_Press         (rc_ctrl.mouse.press_r==1)
#define Right_NoPress       (rc_ctrl.mouse.press_r==0)

#define W_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_W)
#define S_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_S)
#define A_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_A)
#define D_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_D)

#define SHIFT_Press         (rc_ctrl.key.v & KEY_PRESSED_OFFSET_SHIFT)
#define CTRL_Press          (rc_ctrl.key.v & KEY_PRESSED_OFFSET_CTRL)

#define Q_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_Q)
#define E_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_E)
#define R_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_R)
#define F_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_F)
#define G_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_G)
#define Z_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_Z)
#define X_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_X)
#define C_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_C)
#define V_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_V)
#define B_Press             (rc_ctrl.key.v & KEY_PRESSED_OFFSET_B)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
