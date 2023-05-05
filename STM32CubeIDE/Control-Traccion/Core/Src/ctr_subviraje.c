/*
 * actuadores.c
 *
 *  Created on: Mar 21, 2023
 *      Author: carlos
 */

#include <ctr_subviraje.h>

extern TIM_HandleTypeDef htim3;

uint32_t duty_cycle = 400; // En microsegundos
uint32_t period = 1000;    // En microsegundos
uint32_t ticks = period * HAL_RCC_GetSysClockFreq() / 1000000; // En ticks del temporizador
uint32_t duty_ticks = (duty_cycle * ticks) / period;

void freno(int16_t duty_ticks){
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty_ticks);
}

//UpDown es GPIO_PIN_SET (1) o GPIO_PIN_RESET (0)

void mux(uint32_t UpDown){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, UpDown);
}

void Tarea_ctr_subviraje(void * pArg) {


	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		struct CT_Sensores_t sensors;
		if(sensors.IMU1accelX<sensors.IMU2accelX){
			freno(duty_ticks);
			mux(GPIO_PIN_SET);
		}




		xQueueSend(xQueueIMUs, &struc, portMAX_DELAY);
	}
}

