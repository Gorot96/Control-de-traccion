/*
 * IMUS.h
 *
 *  Created on: Mar 8, 2023
 *      Author: carlos
 */

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "Tareas.h"

#ifndef INC_IMUS_H_
#define INC_IMUS_H_

void InitIMUS();
int16_t ReadIMU1(uint8_t axxis);
int16_t ReadIMU2(uint8_t axxis);
void TareaIMUS(void *pArg);

#endif /* INC_IMUS_H_ */
