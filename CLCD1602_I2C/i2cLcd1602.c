/*
 * i2cLcd1602.c
 *
 *  Created on: 2020. 2. 4.
 *      Author: Kim Ju-seng
 */
#include "i2cLcd1602.h"

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly
#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup

void lcdSendCmd (char cmd)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0 ,wr=0
	data_t[1] = data_u|0x08;  //en=0, rs=0 ,wr=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0 ,wr=0
	data_t[3] = data_l|0x08;  //en=0, rs=0 ,wr=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcdSendData (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0 ,wr=1
	data_t[1] = data_u|0x09;  //en=0, rs=0 ,wr=1
	data_t[2] = data_l|0x0D;  //en=1, rs=0 ,wr=1
	data_t[3] = data_l|0x09;  //en=0, rs=0 ,wr=1
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_clear (void)
{
	lcdSendCmd(0x01);
}

void lcd_gotoxy(uint8_t x, uint8_t y)
{
	switch (y)
	{
	case 0:
		x |= 0x80;
		break;
	case 1:
		x |= 0xC0;
		break;
	}

	lcdSendCmd(x);
}


void lcdInit (void)
{
	uint8_t initStr[5]={0x28,0x08,0x01,0x06,0x0c};

	HAL_Delay(50);  // wait for >40ms
	for(int i=0; i<3; i++)
	{
		lcdSendCmd(0x30);
		HAL_Delay(10);
	}
	lcdSendCmd(0x20);  // 4bit mode
	HAL_Delay(10);

	for(int i=0; i<5; i++)
	{
		lcdSendCmd(initStr[i]);
		HAL_Delay(10);
	}
}

void lcd_puts (char *str)
{
	while(*str) lcdSendData(*str++);
}

void lcd_putc (char c)
{
	lcdSendData(c);
}

void lcdCgram (uint8_t addr, uint8_t *cusChar)
{
	for(int i=0; i<8; i++)
	{
		lcdSendCmd(0x40+i+(addr*8));
		lcdSendData(*cusChar++);
	}
}
