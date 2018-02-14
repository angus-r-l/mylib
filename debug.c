/**
  ******************************************************************************
  * @file    debug.c
  * @author  Angus Lohrisch
  * @date    07-02-2017
  * @brief   This file contains all the basic HAL initialisation needed to
  *          print and read from a usb terminal
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "debug.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef UART_debug; // UART handle 
GPIO_InitTypeDef USART_TX; // Configure D0/D1 for ST-Link VCP serial comms
GPIO_InitTypeDef USART_RX;
/* Private function prototypes -----------------------------------------------*/

extern void init_debug(void) {
    USART_TX.Pin = GPIO_PIN_2;
    USART_TX.Mode = GPIO_MODE_AF_PP;
    USART_TX.Pull = GPIO_NOPULL;
    USART_TX.Speed = GPIO_SPEED_FAST;
    USART_TX.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &USART_TX);

    USART_RX.Pin = GPIO_PIN_3;
    USART_RX.Mode = GPIO_MODE_AF_PP;
    USART_RX.Pull = GPIO_NOPULL;
    USART_RX.Speed = GPIO_SPEED_FAST;
    USART_RX.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &USART_RX);

    __USART2_CLK_ENABLE(); // Enable the USART2 clock

    UART_debug.Instance = USART2;
    UART_debug.Init.BaudRate = 115200;
    UART_debug.Init.WordLength = UART_WORDLENGTH_8B;
    UART_debug.Init.StopBits = UART_STOPBITS_1;
    UART_debug.Init.Parity = UART_PARITY_NONE;
    UART_debug.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UART_debug.Init.OverSampling = UART_OVERSAMPLING_16;
    UART_debug.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UART_debug);
}

extern int usb_getc(void) {
    uint8_t rxchar = '\0';
    HAL_UART_Receive(&UART_debug, &rxchar, sizeof(char), 30);
    return rxchar;
}

extern void ssprintf(char* fmt, ...) {
    char print_data[128];
    va_list args;
    va_start(args, fmt);
    memset(print_data, 0, sizeof(print_data));
    vsprintf(print_data, fmt, args);
    va_end(args);
    HAL_UART_Transmit(&UART_debug, (uint8_t*) print_data, sizeof(print_data), 10);
}