/**
 ******************************************************************************
 * File Name: clcd_1602.c
 * Author   : In-Beom Shin
 ******************************************************************************
 * 16x2 Character LCD 4Bit interface
 *
 ******************************************************************************
 */

/* Includes */
#include "clcd_1602.h"

/* Functions */
uint8_t LcdBusyCheck()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  uint8_t lcdBusy;

  GPIO_InitStruct.Pin = LCD_D7_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_D7_GPIO, &GPIO_InitStruct);

  LCD_RW(1); LCD_EN(1);

  lcdBusy = HAL_GPIO_ReadPin(LCD_D7_GPIO, LCD_D7_PIN);

  LCD_EN(0); LCD_EN(1); LCD_EN(0);

  GPIO_InitStruct.Pin = LCD_D7_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LCD_D7_GPIO, &GPIO_InitStruct);

  return lcdBusy;
}

void LcdSendNibble(uint8_t data)
{
  LCD_D4(data >> 0 & 1);
  LCD_D5(data >> 1 & 1);
  LCD_D6(data >> 2 & 1);
  LCD_D7(data >> 3 & 1);
  LCD_EN(1); LCD_EN(0);
}

void LcdSendByte(uint8_t addr, uint8_t data)
{
  LCD_RS(0);
  while(LcdBusyCheck());
  LCD_RS(addr);
  LCD_RW(0); LCD_EN(0);
  LcdSendNibble(data >> 4);
  LcdSendNibble(data & 0x0F);
}

void LcdInit()
{
  const uint8_t LCD_INIT_STRING[4] = {0x28, 0x0C, 0x01, 0x06};

  uint8_t i;
  LCD_RS(0); LCD_RW(0); LCD_EN(0);
  HAL_Delay(15);
  for(i=0; i<3; i++)
  {
    LcdSendNibble(0x03);
    HAL_Delay(5);
  }
  LcdSendNibble(0x02);
  for(i=0; i<4; i++) LcdSendByte(0, LCD_INIT_STRING[i]);
}

void lcd_gotoxy(uint8_t x, uint8_t y)
{
  uint8_t addr;
  if(y != 1) addr = 0x40;
  else addr = 0;
  addr += x-1;
  LcdSendByte(0, 0x80 | addr);
}

void lcd_putc(uint8_t c)
{
  if(c == '\f')
  {
    LcdSendByte(0, 1);
    HAL_Delay(2);
  }
  else if(c == '\n') lcd_gotoxy(1, 2);
  else if(c == '\b') LcdSendByte(0, 0x10);
  else LcdSendByte(1, c);
}

void lcd_puts(const uint8_t *str)
{
  while(*str != 0)
  {
    lcd_putc(*str++);
  }
}

void lcd_cgram(uint8_t room, uint8_t n)
{
  const uint8_t data[2][8]={{0x00, 0x01, 0x01, 0x01, 0x12, 0x0A, 0x0A, 0x04}, // Check Mark
                            {0x0E, 0x11, 0x01, 0x02, 0x04, 0x04, 0x00, 0x04}}; // Question Mark
  uint8_t i;

  for(i=0; i<8; i++)
  {
    LcdSendByte(0, 0x40+i+(room*8));
    LcdSendByte(1, data[n][i]);
  }
}
