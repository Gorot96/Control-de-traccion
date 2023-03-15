/*
 * Tareas.c
 *
 *  Created on: Mar 8, 2023
 *      Author: Raul Duran
 */


#include "Tareas.h"

QueueHandle_t xQueueIMUs;
TaskHandle_t sensoresTaskHandler;

SemaphoreHandle_t xSemaphore;

void CreaTareas(void) {
	// Creamos tarea para el control de las IMUs
	xTaskCreate(TareaIMUs, "TareaIMUs", 128, NULL, 1, NULL);

	// Creamos la tarea para el control del servidor web
	xTaskCreate(TareaServidorWeb,"TareaWebServer", 256, NULL,1, NULL);
}

void CrearObjetosSerie(void) {
	// Creamos la cola de mensajes que mandará y recibirá datos de las IMUs.
	xQueueIMUs = xQueueCreate(1, sizeof (struct CT_Sensores_t));
}

void TareaServidorWeb(void * pArg) {

	while(1) {
		// Bucle infinito
	}
}

struct CT_Sensores_t GetSensores()
{
	struct CT_Sensores_t sensors;
	xTaskNotifyGive(sensoresTaskHandler);
	xQueueReceive(xQueueIMUs, &sensors, portMAX_DELAY);
	return sensors;
}
