/*
 * MPU6050.c
 *
 *  Created on: 2020. 5. 22.
 *      Author: bbb
 */

#include "MPU6050.h"

I2C_HandleTypeDef hi2c1;

//void GYRO_Init()
//{
//  HAL_Delay(100);
//
//  HAL_I2C_Mem_Write(&hi2c1,0x68,0x68,I2C_MEMADD_SIZE_8BIT,0x00,1,1000);
//  HAL_Delay(3);
//  HAL_I2C_Mem_Write(&hi2c1,0x68,0x1B,I2C_MEMADD_SIZE_8BIT,0xF8,1,1000);
//  HAL_Delay(3);
//  HAL_I2C_Mem_Write(&hi2c1,0x68,0x1C,I2C_MEMADD_SIZE_8BIT,0xF8,1,1000);
//}

void MPU6050_Write_bits(uint8_t Address, uint8_t bitStart, uint8_t length, uint8_t data){
    uint8_t tmp = 0;
    HAL_I2C_Mem_Read(&hi2c1, MPU6050, Address, 1, (uint8_t *)&tmp, 1, 10);
    uint8_t mask = 0;
    switch(length){
        case 1: mask = 0x01; break;
        case 2: mask = 0x03; break;
        case 3: mask = 0x07; break;
        case 4: mask = 0x0F; break;
        case 5: mask = 0x1F; break;
        case 6: mask = 0x3F; break;
        case 7: mask = 0x7F; break;
        case 8: mask = 0xFF; break;
    }
    tmp &= ~(mask << bitStart);
    tmp |= (data << bitStart);
    HAL_I2C_Mem_Write(&hi2c1, MPU6050, Address, 1, (uint8_t *)&tmp, 1, 10);
}

void init_MPU6050(void){
  uint8_t test = 0;
  char bf[30] = {0};

  HAL_Delay(100);
  HAL_I2C_Mem_Read(&hi2c1,MPU6050,0x75,I2C_MEMADD_SIZE_8BIT,(uint8_t *)&test,1,100);

  MPU6050_Write_bits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 0x01, DISABLE); // SetSleepModeStatus
  HAL_Delay(10);
  MPU6050_Write_bits(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_XGYRO);      // SetClockSource
  MPU6050_Write_bits(MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS_250);   // SetFullScaleGyroRange
  MPU6050_Write_bits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, MPU6050_ACCEL_FS_2); // SetFullScaleAccelRange
}
