/**
  ******************************************************************************
  * @file    init_hardware.h 
  * @author  Angus Lohrisch
  * @date    24-01-2017
  * @brief   This file contains external variables and function protoypes for
  *          all basic hardware initialisation for all projects
  ******************************************************************************
  */
#ifndef __INIT_HW_H
#define __INIT_HW_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
/* External typedef ----------------------------------------------------------*/
/* External define -----------------------------------------------------------*/
/* External macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Led_TypeDef LED;
UART_HandleTypeDef UART_debug;
/* External function prototypes ----------------------------------------------*/
extern void init_hardware(void);

#endif