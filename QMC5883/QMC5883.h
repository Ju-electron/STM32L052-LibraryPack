/*
 * QMC5883.h
 *
 *  Created on: 2020. 5. 22.
 *      Author: bbb
 */

#ifndef QMC5883_H_
#define QMC5883_H_

#include <main.h>

#define QMC5883_ADDR (0x0D << 1)

#define Mode_Standby    0b00000000
#define Mode_Continuous 0b00000001

#define ODR_10Hz        0b00000000
#define ODR_50Hz        0b00000100
#define ODR_100Hz       0b00001000
#define ODR_200Hz       0b00001100

#define RNG_2G          0b00000000
#define RNG_8G          0b00010000

#define OSR_512         0b00000000
#define OSR_256         0b01000000
#define OSR_128         0b10000000
#define OSR_64          0b11000000

#endif /* QMC5883_H_ */
