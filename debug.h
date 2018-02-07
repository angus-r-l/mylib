/**
  ******************************************************************************
  * @file    debug.h 
  * @author  Angus Lohrisch
  * @date    07-02-2017
  * @brief   This file contains external variables and function protoypes for
  *          the usb printing and reading
  ******************************************************************************
  */
#ifndef __INIT_DEBUG_H
#define __INIT_DEBUG_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
/* External typedef ----------------------------------------------------------*/
/* External define -----------------------------------------------------------*/
/* External macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
extern void init_debug(void);
extern void ssprintf(char*, ...);

#endif