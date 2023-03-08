/*
 * Tareas.c
 *
 *  Created on: Mar 8, 2023
 *      Author: Raul Duran
 */


#include "Tareas.h"

void CreaTareas(void) {
	// Creamos tarea para el control de las IMUs
	xTaskCreate(TareaIMUs, "TareaIMUs", 128, NULL, 1, NULL);
}

void TareaIMUs(void * pArg) {

	while (1) {
		// Bucle infinito
	}
}
