/*
 * Tareas.h
 *
 *  Created on: 21 nov. 2022
 *      Author: Raul Duran
 */

#include "main.h"
#include "cmsis_os.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "Sensores.h"

#ifndef INC_TAREAS_H_
#define INC_TAREAS_H_

void TareaSensores(void *pArg);
void TareaWebServer(void *pArg);
void TareaLED(void *pArg);

void CreateTasks();
void CreateSerialObjects();

void EncolarLED(char ch);
struct P5sensores_t GetSensores();

#endif /* INC_TAREAS_H_ */
