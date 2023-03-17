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

void CreaTareas(void);
void CrearObjetosSerie(void);
void TareaServidorWeb(void * pArg);
struct CT_Sensores_t GetSensores(void);

#endif /* INC_TAREAS_H_ */
