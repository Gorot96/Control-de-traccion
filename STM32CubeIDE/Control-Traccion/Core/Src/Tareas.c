/*
 * Tareas.c
 *
 *  Created on: Mar 8, 2023
 *      Author: Raul Duran
 */


#include "Tareas.h"

/*
 * Esta variable decidirá si vamos a usar la placa para leer datos, o si, en cambio
 * vamos a usarla para controlar el derrape.
 */
uint8_t testing = 2;

QueueHandle_t xQueue;
TaskHandle_t sensoresTaskHandler;
SemaphoreHandle_t xSemaphore;

SemaphoreHandle_t xSemaphore;

int wifi_server(void);
void Tarea_ctr_subviraje(void * pArg);

void CrearObjetosSerie(void) {
	// Creamos el semáforo para permitir la impresión de datos por pantalla
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive (xSemaphore);

	// Creamos la cola de mensajes que mandará y recibirá datos de las IMUs.
	xQueue = xQueueCreate(10, sizeof (struct CT_Sensores_t));
}

void CrearTareas(void) {
	// Creamos tarea para el control de las IMUs
	xTaskCreate(TareaIMUs, "TareaIMUs", 128, NULL, 1, &sensoresTaskHandler);

	switch (testing) {
	case 0:
		// Creamos la tarea para el control del subviraje
		xTaskCreate(Tarea_ctr_subviraje, "TareaCtrSubviraje", 128, NULL, 1, NULL);
		break;
	case 1:
		// Creamos la tarea para el control del servidor web
		xTaskCreate(TareaServidorWeb,"TareaWebServer", 256, NULL,1, NULL);
		break;
	case 2:
		// Creamos la tarea para el control del servidor web
		xTaskCreate(TareaServidorWeb,"TareaWebServer", 256, NULL,1, NULL);

		// Creamos la tarea para el control del subviraje
		xTaskCreate(Tarea_ctr_subviraje, "TareaCtrSubviraje", 128, NULL, 1, NULL);
		break;
	}
}

void TareaServidorWeb(void * pArg) {
	wifi_server();
}

void GetSensores(struct CT_Sensores_t* pSensores, uint8_t packet_size)
{
	uint8_t i;
	for (i = 0; i < packet_size; i++) {
		struct CT_Sensores_t sensors;
		xTaskNotifyGive(sensoresTaskHandler);
		xQueueReceive(xQueue, &sensors, portMAX_DELAY);

		pSensores[i] = sensors;
	}
}
