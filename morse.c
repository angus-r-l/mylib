/**
  ******************************************************************************
  * @file    mylib/morse.c 
  * @author  Angus Lohrisch
  * @date    08-02-2018
  * @brief   This file contains the source code for the lookup table 
  *          functionality for the morse codes
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morse.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
char* morse_table[37] = {
    ".-",               // A
    "-...",             // B
    "-.-.",             // C
    "-..",              // D
    ".",                // E
    "..-.",             // F
    "--.",              // G
    "....",             // H
    "..",               // I
    ".---",             // J
    "-.-",              // K
    ".-..",             // L
    "--",               // M
    "-.",               // N
    "---",              // O
    ".--.",             // P
    "--.-",             // Q
    ".-.",              // R
    "...",              // S
    "-",                // T
    "..-",              // U
    "...-",             // V
    ".--",              // W
    "-..-",             // X
    "-.--",             // Y
    "--..",             // Z
    "-----",            // 0
    ".----",            // 1
    "..---",            // 2
    "...--",            // 3
    "....-",            // 4
    ".....",            // 5
    "-....",            // 6
    "--...",            // 7
    "---..",            // 8
    "----.",            // 9
    "!"                 // ! error
};
/* Private function prototypes -----------------------------------------------*/
static uint8_t is_valid(char);
static char* get_code(uint8_t, uint8_t);

/**
  * @brief External wrapper to retrieve appropriate codes or error
  * @param char Letter or number
  * @retval char* Code in string form
  */
extern char* morse_get_code(char c) {
    return get_code(c, is_valid(c));
}

/**
  * @brief Checks the character and reports back a flag
  * @param char Letter or number
  * @retval uint8_t Number flag
  */
static uint8_t is_valid(char c) {
    if (c >= '0' && c <= '9') {
        return 3;
    } else if (c >= 'A' && c <= 'Z') {
        return 2;
    } else if (c >= 'a' && c <= 'z') {
        return 1;
    } else {        // Bad char
        return 0;
    }
}

/**
  * @brief Retrieves the code attached to a specific character 0-9, A-Z
  * @param uint8_t Letter or number, uint8_t Flag number
  * @retval char* Code in string format
  */
static char* get_code(uint8_t c, uint8_t valid) {
    if (valid == 3) {
        return morse_table[26 + (c - '0')];
    } else if (valid == 2) {
        return morse_table[(c - 'A')];
    } else if (valid == 1) {
        return morse_table[(c- 'a')];
    } else {
        return morse_table[36];     // Error code
    }
}