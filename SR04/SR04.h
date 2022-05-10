/*
 * SR04.h
 *
 * Ultra sonic wave sensor library
 * with STM32 Timer inputCapture interrupt.
 *
 * Pls flollow the instructions down below
 * 1. Turn on the Timer in ioc file
 * (Clock Sourse = Internal Clock, Channel1 = Input capture indirect Mode, Channel2 = Input Capture direct Mode)
 * (Channel1 and Channel2 has changed possible each other)
 * 2. Set "Polarity Selection" of indirect Mode channel to Rising Edge in Parameter Settings.
 * 3. Set "Polarity Selection" of Direct Mode channel to Falling Edge in Parameter Settings.
 *
 * 4. Set timer prescaler = 32-1 (Based on 32MHz)
 * 5. Counter Peroid = 65536
 * (for set timer speed to 1us)
 *
 *6. Edit below code in top of SR04.c
 *extern TIM_HandleTypeDef htim<yours>;
 *Edit below code in "SR04_init()" function in SR04.c
 *HAL_TIM_IC_Start_IT(&htim<yours>, TIM_CHANNEL_<yours>); //direct
 *HAL_TIM_IC_Start_IT(&htim<yours>, TIM_CHANNEL_<yours>); //indirect
 *
 *7. Edit below code in "HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)l" function in SR04.c
 *if(htim->Instance == TIM<yours>){
 *if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_<your direct channel>){
 *		TIM<yous>->CNT = 0;
 *	}
 *	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_<your indirect channel>){
 *		usV = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_<your indirect channel>);
 *	}
 *}

 *8. Add "SR04_init()" function in "USER CODE 2" sector.
 *9. You can get distance value as float using "SR04_getDistance()" function.
 *10. Enjoy!
 */

#ifndef SRC_SR04_H_
#define SRC_SR04_H_

#include "main.h"
#include "stm32l0xx_hal.h"

#define CM 0
#define INCH 1
#define DISTANCE_UNIT CM

void SR04_init();
void SR04_trig();
float SR04_getDistance();

#endif /* SRC_SR04_H_ */
