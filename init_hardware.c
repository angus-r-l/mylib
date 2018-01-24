/**
  ******************************************************************************
  * @file    init_hardware.c
  * @author  Angus Lohrisch
  * @date    24-01-2017
  * @brief   This file contains all the basic HAL initialisation needed to
  *          configure the NucleoF401RE for use.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "init_hardware.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/**
  * @brief Initalises all the hardware
  * @param 
  * @retval
  */
extern void init_hardware(void) {

    // Probably can put these into a common.h file to use in all projects
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    HAL_Init();

    // Enable GPIO clocks for USR_LED and USR_BTN
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /* Configure the system clock to 84 MHz */
    SystemClock_Config();

    // Configure D0/D1 pins for ST-Link VCP serial communication
    GPIO_InitTypeDef USART_TX;
    GPIO_InitTypeDef USART_RX;

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

    // Initalise the board LED
    BSP_LED_Init(LED);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 84000000
  *            HCLK(Hz)                       = 84000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 336
  *            PLL_P                          = 4
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale2 mode
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void) {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /* Enable HSI Oscillator and activate PLL with HSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 0x10;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
        while(1) {}
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        while(1) {}
    }
}