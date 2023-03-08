/*
 * Tareas.h
 *
 *  Created on: Mar 8, 2023
 *      Author: Raul Duran
 */

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

#ifndef INC_TAREAS_H_
#define INC_TAREAS_H_

void CreaTareas(void);
void TareaIMUs(void * pArg);

#endif /* INC_TAREAS_H_ */
