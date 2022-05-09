/**
  ******************************************************************************
  * File Name: clcd_1602.h
  * Author   : In-Beom Shin
  ******************************************************************************
  * 16x2 Character LCD 4Bit interface
  * 
  ******************************************************************************
  */

/* Includes */
#include "string.h"
#include "stm32l0xx_hal.h"

/* Defines */
#define LCD_D7_GPIO GPIOB
#define LCD_D7_PIN  GPIO_PIN_7
#define LCD_RS(x)   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (GPIO_PinState)x)
#define LCD_RW(x)   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (GPIO_PinState)x)
#define LCD_EN(x)   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (GPIO_PinState)x)
#define LCD_D4(x)   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (GPIO_PinState)x)
#define LCD_D5(x)   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState)x)
#define LCD_D6(x)   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState)x)
#define LCD_D7(x)   HAL_GPIO_WritePin(LCD_D7_GPIO, LCD_D7_PIN, (GPIO_PinState)x)

/* Functions */
uint8_t LcdBusyCheck(void);
void LcdSendNibble(uint8_t n);
void LcdSendByte(uint8_t address, uint8_t n);
void LcdInit(void);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_putc(uint8_t c);
void lcd_puts(const uint8_t *str);
void lcd_cgram(uint8_t room, uint8_t n);
