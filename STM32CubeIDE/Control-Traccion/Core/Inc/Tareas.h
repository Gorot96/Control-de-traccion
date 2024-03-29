/*
 * Tareas.h
 *
 *  Created on: Mar 8, 2023
 *      Author: Raul Duran
 */

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "IMUS.h"

#ifndef INC_TAREAS_H_
#define INC_TAREAS_H_

void CrearTareas(void);
void CrearObjetosSerie(void);
void TareaServidorWeb(void * pArg);
void TareaIMUs(void *pArg);
void GetSensores(struct CT_Sensores_t* pSensores, uint8_t packet_size);

#endif /* INC_TAREAS_H_ */
