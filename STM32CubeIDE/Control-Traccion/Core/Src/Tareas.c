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

SemaphoreHandle_t xSemaphore;

int mqtt_connection(void);

void CrearObjetosSerie(void) {
	// Creamos el semáforo para permitir la impresión de datos por pantalla
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive (xSemaphore);

	// Creamos la cola de mensajes que mandará y recibirá datos de las IMUs.
	//xQueueIMUs = xQueueCreate(1, sizeof (struct CT_Sensores_t));
}

void CrearTareas(void) {
	// Creamos tarea para el control de las IMUs
	//xTaskCreate(TareaIMUs, "TareaIMUs", 128, NULL, 1, &sensoresTaskHandler);

	// Creamos la tarea para el control del servidor web
	xTaskCreate(TareaServidorWeb,"TareaWebServer", 256, NULL,1, NULL);
}

void TareaServidorWeb(void * pArg) {
	return mqtt_connection();
}

struct CT_Sensores_t GetSensores()
{
	struct CT_Sensores_t sensors;
	xTaskNotifyGive(sensoresTaskHandler);
	xQueueReceive(xQueueIMUs, &sensors, portMAX_DELAY);
	return sensors;
}
