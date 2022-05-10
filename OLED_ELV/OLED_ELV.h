/*
 * OLED_ELV.h
 *
 *  Created on: May 10, 2022
 *      Author: js372
 */

#ifndef INC_OLED_ELV_H_
#define INC_OLED_ELV_H_

#define SSD1306_I2C_ADDR 0x78
#define OLED_WRITECOMMAND(command)      OLED_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
#define OLED_WRITEDATA(data)            OLED_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))

#include "stm32L0xx_hal.h"
#include "main.h"

uint8_t SSD1306_Init(void);
void OLED_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
void OLED_sel(uint8_t sel);
void OLED_clear();
void OLED_fill();
void OLED_init();
void OLED_number(uint8_t x, uint8_t num);
void OLED_up(uint8_t x, uint8_t step);
void OLED_down(uint8_t x, uint8_t step);
void OLED_open(uint8_t step);
void OLED_close(uint8_t step);

#endif /* INC_OLED_ELV_H_ */
