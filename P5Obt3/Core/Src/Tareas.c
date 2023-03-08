/*
 * Tareas.c
 *
 *  Created on: 29 nov. 2020
 *      Author: rpaz
 */

#include "Tareas.h"

extern UART_HandleTypeDef huart1;

SemaphoreHandle_t xSemaphore;
QueueHandle_t xQueue;

TaskHandle_t sensoresTaskHandler;
QueueHandle_t xQueueLED;
QueueHandle_t xQueueSensors;

int wifi_server(void);

void TareaSensores(void *pArg);
void TareaWebServer(void *pArg)
{
	wifi_server();
}

void TareaLED(void *pArg)
{
	char ch;
	while(1)
	{
		xQueueReceive(xQueueLED, &ch, portMAX_DELAY);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, ch);
	}
}

void CreateTasks()
{
	xTaskCreate(TareaSensores,"TareaSensores", 128, NULL,1, &sensoresTaskHandler);
	xTaskCreate(TareaWebServer,"TareaWebServer", 256, NULL,1, NULL);
	xTaskCreate(TareaLED,"TareaLED", 128, NULL,1, NULL);
}


void CreateSerialObjects()
{
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive (xSemaphore);

	xQueue = xQueueCreate(5, sizeof (char*));
	xQueueLED = xQueueCreate(1, sizeof (char*));
	xQueueSensors = xQueueCreate(1, sizeof (struct P5sensores_t));
}

void EncolarLED(char ch)
{
	xQueueSend(xQueueLED,&ch, portMAX_DELAY);
}

struct P5sensores_t GetSensores()
{
	struct P5sensores_t sensors;
	xTaskNotifyGive(sensoresTaskHandler);
	xQueueReceive(xQueueSensors, &sensors, portMAX_DELAY);
	return sensors;
}
