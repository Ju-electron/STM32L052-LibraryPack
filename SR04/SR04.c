/*
 * SR04.c
 */
#include "SR04.h"

uint32_t usV=0; //micro second count
float distance=0; //retun distance
extern TIM_HandleTypeDef htim21; //using timer handler

void SR04_init(){
	HAL_TIM_IC_Start_IT(&htim21, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim21, TIM_CHANNEL_1);
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM21){
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			TIM21->CNT = 0;
		}
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			usV = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		}
	}
}

void SR04_trig(){
	HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, 1);
	HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, 0);
}
float SR04_getDistance(){
	if(DISTANCE_UNIT) distance = usV/58; //cm
	else distance = usV/148; //inch

	return distance;
}
