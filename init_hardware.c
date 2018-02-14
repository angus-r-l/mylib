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
GPIO_InitTypeDef USR_BTN;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/**
  * @brief Initalises all the hardware
  * @param 
  * @retval
  */
extern void init_hardware(void) {

    HAL_Init();

    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    // Enable GPIO clocks for USR_LED and USR_BTN
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /* Configure the system clock to 84 MHz */
    SystemClock_Config();

    // Initalise the board LED
    BSP_LED_Init(LED);

    // Initialise the board user button
    // Interrupt mode
    USR_BTN.Pin = USER_BUTTON_PIN;
    USR_BTN.Pull = GPIO_NOPULL;
    USR_BTN.Mode = GPIO_MODE_IT_RISING_FALLING;
    USR_BTN.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOC, &USR_BTN);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    //Read mode
    // USR_BTN.Pin = USER_BUTTON_PIN;
    // USR_BTN.Pull = GPIO_NOPULL;
    // USR_BTN.Mode = GPIO_MODE_INPUT;
    // USR_BTN.Speed = GPIO_SPEED_FAST;
    // HAL_GPIO_Init(GPIOC, &USR_BTN);
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