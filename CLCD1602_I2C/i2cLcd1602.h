/*
 * i2cLcd0602.h
 *
 *  Created on: 2020. 2. 4.
 *      Author: Kim Ju-seng
 */
#include "stm32l0xx_hal.h"

#ifndef I2CLCD0602_H_
#define I2CLCD0602_H_

void lcdSendCmd (char cmd);
void lcdSendData (char data);
void lcd_clear (void);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcdInit (void);
void lcd_puts (char *str);
void lcdCgram (uint8_t addr, uint8_t *cusChar);

#endif /* I2CLCD0602_H_ */
