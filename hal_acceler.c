/**
  ******************************************************************************
  * @file    init_hardware.c
  * @author  Angus Lohrisch
  * @date    25-01-2017
  * @brief   This file contains the initialisation and source code for the 
  *          accelerometer (ADXL335) driver
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "hal_acceler.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define X_CHAN 0
#define Y_CHAN 1
#define Z_CHAN 4
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef acceler_x;
ADC_HandleTypeDef acceler_y;
ADC_HandleTypeDef acceler_z;
ADC_ChannelConfTypeDef conf_x;
ADC_ChannelConfTypeDef conf_y;
ADC_ChannelConfTypeDef conf_z;

/* Private function prototypes -----------------------------------------------*/
static void select_channel(uint8_t);
static uint16_t adc_read(ADC_HandleTypeDef);

/**
  * @brief
  * @param
  * @retval
  */
extern void hal_acceler_init(void) {
    // Initialise the GPIO pins for analog mode
    GPIO_InitTypeDef ADC_PINS;

    __GPIOA_CLK_ENABLE();

    // A0 Pin
    ADC_PINS.Pin = GPIO_PIN_0;
    ADC_PINS.Mode = GPIO_MODE_ANALOG;
    ADC_PINS.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &ADC_PINS);

    // A1 Pin
    ADC_PINS.Pin = GPIO_PIN_1;
    ADC_PINS.Mode = GPIO_MODE_ANALOG;
    ADC_PINS.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &ADC_PINS);

    // A2 Pin
    ADC_PINS.Pin = GPIO_PIN_4;
    ADC_PINS.Mode = GPIO_MODE_ANALOG;
    ADC_PINS.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &ADC_PINS);

    // For using interrupts
    // HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(ADC_IRQn);

    __ADC1_CLK_ENABLE();

    // Initialise the A0 pin
    acceler_x.Instance = (ADC_TypeDef*) ADC1;
    acceler_x.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    acceler_x.Init.Resolution = ADC_RESOLUTION_12B;
    acceler_x.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    acceler_x.Init.ScanConvMode = DISABLE;
    acceler_x.Init.EOCSelection = DISABLE;
    acceler_x.Init.ContinuousConvMode = DISABLE;
    acceler_x.Init.NbrOfConversion = 1;
    acceler_x.Init.DiscontinuousConvMode = DISABLE;
    acceler_x.Init.NbrOfDiscConversion = 0;
    acceler_x.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
    acceler_x.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    acceler_x.Init.DMAContinuousRequests = DISABLE;
    HAL_ADC_Init(&acceler_x);

    conf_x.Channel = ADC_CHANNEL_0;
    conf_x.Rank = 1;
    conf_x.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    conf_x.Offset = 0;
    HAL_ADC_ConfigChannel(&acceler_x, &conf_x);

    // Initialise the A1 pin
    acceler_y.Instance = (ADC_TypeDef*) ADC1;
    acceler_y.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    acceler_y.Init.Resolution = ADC_RESOLUTION_12B;
    acceler_y.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    acceler_y.Init.ScanConvMode = DISABLE;
    acceler_y.Init.EOCSelection = DISABLE;
    acceler_y.Init.ContinuousConvMode = DISABLE;
    acceler_y.Init.NbrOfConversion = 1;
    acceler_y.Init.DiscontinuousConvMode = DISABLE;
    acceler_y.Init.NbrOfDiscConversion = 0;
    acceler_y.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
    acceler_y.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    acceler_y.Init.DMAContinuousRequests = DISABLE;
    HAL_ADC_Init(&acceler_y);

    conf_y.Channel = ADC_CHANNEL_1;
    conf_y.Rank = 1;
    conf_y.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    conf_y.Offset = 0;
    HAL_ADC_ConfigChannel(&acceler_y, &conf_y);

    // Initialise the A2 pin
    acceler_z.Instance = (ADC_TypeDef*) ADC1;
    acceler_z.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    acceler_z.Init.Resolution = ADC_RESOLUTION_12B;
    acceler_z.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    acceler_z.Init.ScanConvMode = DISABLE;
    acceler_z.Init.EOCSelection = DISABLE;
    acceler_z.Init.ContinuousConvMode = DISABLE;
    acceler_z.Init.NbrOfConversion = 1;
    acceler_z.Init.DiscontinuousConvMode = DISABLE;
    acceler_z.Init.NbrOfDiscConversion = 0;
    acceler_z.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
    acceler_z.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    acceler_z.Init.DMAContinuousRequests = DISABLE;
    HAL_ADC_Init(&acceler_z);

    conf_z.Channel = ADC_CHANNEL_4;
    conf_z.Rank = 1;
    conf_z.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    conf_z.Offset = 0;
    HAL_ADC_ConfigChannel(&acceler_z, &conf_z);
}

/**
  * @brief Wrapper function to read the ADC values on each channel
  * @param pin: Number of the pin to be read
  * @retval value: Returns directly from the read, the 12-bit number on the ADC
  */
extern uint16_t acceler_read(int pin) {
    if (pin == 0) {
        select_channel(X_CHAN);
        return adc_read(acceler_x);
    } else if (pin == 1) {
        select_channel(Y_CHAN);
        return adc_read(acceler_y);
    } else if (pin == 2) {
        select_channel(Z_CHAN);
        return adc_read(acceler_z);
    } else {
        return 0;
    }
}

/**
  * @brief Adjust the rank of the channels to select one based on priority
  * @param chan: Channel number of the ADC to be used
  * @retval None
  */
static void select_channel(uint8_t chan) {
    switch (chan) {
        case 0: // A0 Pin
            conf_x.Rank = 1;
            conf_y.Rank = 2;
            conf_z.Rank = 3;
            HAL_ADC_ConfigChannel(&acceler_x, &conf_x);
            HAL_ADC_ConfigChannel(&acceler_y, &conf_y);
            HAL_ADC_ConfigChannel(&acceler_z, &conf_z);
            break;
        case 1: // A1 Pin
            conf_x.Rank = 2;
            conf_y.Rank = 1;
            conf_z.Rank = 3;
            HAL_ADC_ConfigChannel(&acceler_x, &conf_x);
            HAL_ADC_ConfigChannel(&acceler_y, &conf_y);
            HAL_ADC_ConfigChannel(&acceler_z, &conf_z);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4: // A2 Pin
            conf_x.Rank = 2;
            conf_y.Rank = 3;
            conf_z.Rank = 1;
            HAL_ADC_ConfigChannel(&acceler_x, &conf_x);
            HAL_ADC_ConfigChannel(&acceler_y, &conf_y);
            HAL_ADC_ConfigChannel(&acceler_z, &conf_z);
            break;
    }
}

/**
  * @brief Reads the value on the ADC associated with the handle
  * @param handle: ADC_HandleTypeDef struct
  * @retval value: The 12-bit number read on the ADC
  */
static uint16_t adc_read(ADC_HandleTypeDef handle) {
    HAL_ADC_Start(&handle);
    while(HAL_ADC_PollForConversion(&handle, 10) != HAL_OK);
    uint16_t value = (uint16_t) HAL_ADC_GetValue(&handle);
    HAL_ADC_Stop(&handle);
    return value;
}