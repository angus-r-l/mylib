/**
  ******************************************************************************
  * @file    mylib/hal_acceler.h
  * @author  Angus Lohrisch
  * @date    25-01-2017
  * @brief   This file contains external variables and prototypes for the 
  *          accelerometer (ADXL335) driver
  ******************************************************************************
  */
#ifndef HAL_ACCEL
#define HAL_ACCEL
/* Includes ------------------------------------------------------------------*/
/* External typedef ----------------------------------------------------------*/
/* External define -----------------------------------------------------------*/
/* External macro ------------------------------------------------------------*/
#define acceler_read_x() acceler_read(0)
#define acceler_read_y() acceler_read(1)
#define acceler_read_z() acceler_read(2)
/* External variables --------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
extern void hal_acceler_init(void);
extern uint16_t acceler_read(int);

#endif