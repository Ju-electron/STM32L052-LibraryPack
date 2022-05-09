/**
 ******************************************************************************
 * File Name: clcd_2004.h
 * Author   : In-Beom Shin
 * Edit	by	: Ju-seung Kim
 ******************************************************************************
 * 20x4 Character LCD 4Bit interface
 *
 ******************************************************************************
 */

/* Includes */
#include "main.h"
#include "string.h"
#include "stm32l0xx_hal.h"

/* Defines */
#define LCD_D7_GPIO LCD_D7_GPIO_Port
#define LCD_D7_PIN  LCD_D7_Pin
#define LCD_RS(x)   HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, (GPIO_PinState)x)
#define LCD_RW(x)   HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, (GPIO_PinState)x)
#define LCD_EN(x)   HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, (GPIO_PinState)x)
#define LCD_D4(x)   HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (GPIO_PinState)x)
#define LCD_D5(x)   HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (GPIO_PinState)x)
#define LCD_D6(x)   HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (GPIO_PinState)x)
#define LCD_D7(x)   HAL_GPIO_WritePin(LCD_D7_GPIO, LCD_D7_PIN, (GPIO_PinState)x)

/* Functions */
uint8_t LcdBusyCheck(void);
void LcdSendNibble(uint8_t n);
void LcdSendByte(uint8_t address, uint8_t n);
void lcdInit(void);
void lcd_gotoxy(int x, int y);
void lcd_putc(uint8_t c);
void lcd_puts(const uint8_t *str);
//void lcd_cgram(uint8_t room, uint8_t n);
void lcd_cgram(uint8_t room, uint8_t *fData);
