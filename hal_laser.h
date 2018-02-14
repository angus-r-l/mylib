/**
  ******************************************************************************
  * @file    mylib/hal_laser.h
  * @author  Angus Lohrisch
  * @date    08-02-2018
  * @brief   This file contains HAL level external variables and prototypes 
  *          for the diode laser module
  ******************************************************************************
  */
#ifndef __HAL_LASER_H
#define __HAL_LASER_H
/* Includes ------------------------------------------------------------------*/
/* External typedef ----------------------------------------------------------*/
/* External define -----------------------------------------------------------*/
#define L_ON      0x00
#define L_OFF     0x01
/* External macro ------------------------------------------------------------*/
#define hal_laser_on() hal_laser_write(L_ON)
#define hal_laser_off() hal_laser_write(L_OFF)
/* External variables --------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
extern void hal_laser_init(void);
extern void hal_laser_write(uint8_t);

#endif