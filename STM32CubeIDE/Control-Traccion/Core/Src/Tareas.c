/*
 * Tareas.c
 *
 *  Created on: Mar 8, 2023
 *      Author: Raul Duran
 */


#include "Tareas.h"

QueueHandle_t xQueue1;
QueueHandle_t xQueue2;
TaskHandle_t sensoresTaskHandler;
SemaphoreHandle_t xSemaphore;

SemaphoreHandle_t xSemaphore;

int wifi_server(void);

uint8_t usingQ, fullQ;

void CrearObjetosSerie(void) {
	// Creamos el semáforo para permitir la impresión de datos por pantalla
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive (xSemaphore);

	// Creamos la cola de mensajes que mandará y recibirá datos de las IMUs.
	xQueue1 = xQueueCreate(1, sizeof (struct CT_Sensores_t));
	xQueue2 = xQueueCreate(1, sizeof (struct CT_Sensores_t));

	usingQ = 0;
}

void CrearTareas(void) {
	// Creamos tarea para el control de las IMUs
	xTaskCreate(TareaIMUs, "TareaIMUs", 128, NULL, 1, &sensoresTaskHandler);

	// Creamos la tarea para el control del servidor web
	xTaskCreate(TareaServidorWeb,"TareaWebServer", 256, NULL,1, NULL);
}

void TareaServidorWeb(void * pArg) {
	wifi_server();
}

struct CT_Sensores_t GetSensores()
{
	struct CT_Sensores_t sensors;
	xTaskNotifyGive(sensoresTaskHandler);
	switch (usingQ){
	case 0:
		xQueueReceive(xQueue1, &sensors, portMAX_DELAY);
		break;
	case 1:
		xQueueReceive(xQueue2, &sensors, portMAX_DELAY);
		break;
	}
	return sensors;
}
