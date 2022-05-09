/*
 * smt32l0xx_USB_Terminal.h
 *
 *  Created on: 2020. 2. 22.
 *      Author: Ju-seng Kim
 */
#ifndef STM32L0XX_USB_TERMINAL_H_
#define STM32L0XX_USB_TERMINAL_H_

#include <stdio.h>
#include "stm32l0xx.h"
#include "stm32l0xx_USB_Terminal.h"
#include "usbd_cdc_if.h"

#define APP_RX_DATA_SIZE  64
#define APP_TX_DATA_SIZE  64
extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
extern uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

//text stvle
#define CDC_reset "\x1b[0m"
#define CDC_bright "\x1b[1m"
#define CDC_dim "\x1b[2m"
#define CDC_italic "\x1b[3m"
#define CDC_underscore "\x1b[4m"
#define CDC_blink "\x1b[5m"
#define CDC_Blink_Rapid "\x1b[6m"
#define CDC_reverse "\x1b[7m"
#define CDC_hidden "\x1b[8m"
#define CDC_Crossed_Out "\x1b[9m"

//text color
#define CDC_black "\x1b[30m"
#define CDC_red "\x1b[31m"
#define CDC_green "\x1b[32m"
#define CDC_yellow "\x1b[33m"
#define CDC_blue "\x1b[34m"
#define CDC_magenta "\x1b[35m"
#define CDC_cyan "\x1b[36m"
#define CDC_white "\x1b[37m"

//Back ground color
#define CDC_BGblack "\x1b[40m"
#define CDC_BGred "\x1b[41m"
#define CDC_BGgreen "\x1b[42m"
#define CDC_BGyellow "\x1b[43m"
#define CDC_BGblue "\x1b[44m"
#define CDC_BGmagenta "\x1b[45m"
#define CDC_BGcyan "\x1b[46m"
#define CDC_BGwhite "\x1b[47m"

//reset
#define NoStyle "\x1b[0m"
#define NoUnderline "\x1b[24m"
#define NoInverse "\x1b[27m"
#define NoColor "\x1b[39m"

//Back ground all
#define Bg_Black_All "$Bg_Black$AllColors"
#define Bg_Red_All "$Bg_Red$AllColors"
#define Bg_Green_All "$Bg_Green$AllColors"
#define Bg_Yellow_All "$Bg_Yellow$AllColors"
#define Bg_Blue_All "$Bg_Blue$AllColors"
#define Bg_Magenta_All "$Bg_Magenta$AllColors"
#define Bg_Cyan_All "$Bg_Cyan$AllColors"
#define Bg_White_All "$Bg_White$AllColors"

void terminal_clear();
void putstr(char *str);
char getch();
void cdc_gotoxy(uint8_t x, uint8_t y);


#endif /* STM32L0XX_USB_TERMINAL_H_ */
