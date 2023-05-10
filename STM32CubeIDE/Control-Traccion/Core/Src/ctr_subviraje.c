/*
 * actuadores.c
 *
 *  Created on: Mar 21, 2023
 *      Author: carlos
 */

#include "ctr_subviraje.h"

extern TIM_HandleTypeDef htim3;
extern QueueHandle_t xQueue;
extern TaskHandle_t sensoresTaskHandler;

void Tarea_ctr_subviraje(void * pArg) {
	uint32_t duty_cycle = 400; // En microsegundos
	uint32_t period = 1000;    // En microsegundos
	uint32_t ticks = period * HAL_RCC_GetSysClockFreq() / 1000000; // En ticks del temporizador
	uint32_t duty_ticks = (duty_cycle * ticks) / period;

//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	__HAL_TIM_SET_PRESCALER(&htim3, 159);

	while(1)
	{
		xTaskNotifyGive(sensoresTaskHandler);

		struct CT_Sensores_t sensors;

		xQueueReceive(xQueue, &sensors, portMAX_DELAY);

		// Aplico el freno al canal PWM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, duty_ticks);

		if(sensors.IMU1accelX<sensors.IMU2accelX){
			// Activo el multiplexor
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		} else {
			// Desactivo el multiplexor
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		}
	}
}

