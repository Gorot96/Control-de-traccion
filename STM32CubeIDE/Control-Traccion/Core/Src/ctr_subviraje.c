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

	while(1)
	{
		xTaskNotifyGive(sensoresTaskHandler);

		struct CT_Sensores_t sensors;

		xQueueReceive(xQueue, &sensors, portMAX_DELAY);

		if(sensors.IMU1accelX<sensors.IMU2accelX){
			// Aplico el freno al canal PWM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, duty_ticks);

			// Activo el multiplexor
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		} else {
			// Desactivo el multiplexor
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		}
	}
}

