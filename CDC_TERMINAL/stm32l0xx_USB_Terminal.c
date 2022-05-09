/*
 * stm32l0xx_USB_Terminal.c
 *
 *  Created on: 2020. 2. 22.
 *      Author: Ju-seung Kim
 */
#include "stm32l0xx_USB_Terminal.h"

void terminal_clear()
{
	putstr("\x1b[2J");
}

void putstr(char *str)
{
	CDC_Transmit_FS(str,strlen(str));
}

char getch()
{
	char tempStr[1];
	char outTemp;
	//uint16_t len = strlen((const char*)UserRxBufferFS);
	if(strlen((const char*)UserRxBufferFS))
	{
		strcpy((char*)tempStr,(char*)UserRxBufferFS);

		memset(UserRxBufferFS, 0, sizeof(UserRxBufferFS));
		memset(UserTxBufferFS, 0, sizeof(UserTxBufferFS));

		outTemp=tempStr[0];
		return outTemp;
	}
	//return inTemp;
}

void cdc_gotoxy(uint8_t x, uint8_t y)
{
	char temp[30];
	sprintf(temp,"\x1b[%d;%dH",y,x);
	putstr(temp);
}

