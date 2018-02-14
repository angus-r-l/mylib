/**
  ******************************************************************************
  * @file    mylib/hal_laser.c 
  * @author  Angus Lohrisch
  * @date    08-02-2018
  * @brief   This file contains the HAL level initialisation and source code 
  *          for the diode laser module
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "hal_laser.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define LASER_PIN       GPIO_PIN_10
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef laser_pin;
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief Initialises the HAL to use D2 as the laser output pin
  * @param None
  * @retval None
  */
extern void hal_laser_init(void) {
    laser_pin.Pin = LASER_PIN;
    laser_pin.Mode = GPIO_MODE_OUTPUT_PP;
    laser_pin.Pull = GPIO_PULLDOWN;
    laser_pin.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOA, &laser_pin);

    hal_laser_off();
}

/**
  * @brief Writes a value to the laser output pin - D2
  * @param uint8_t Pin value
  * @retval None
  */
extern void hal_laser_write(uint8_t value) {
    HAL_GPIO_WritePin(GPIOA, LASER_PIN, value);
}