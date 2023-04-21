/*
 * IMUS.h
 *
 *  Created on: Mar 8, 2023
 *      Author: carlos
 */

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"

#ifndef INC_IMUS_H_
#define INC_IMUS_H_

#define MAX_QUEUE_LENGTH 100

void initAccelerometer ();
int16_t ReadIMU1(uint8_t axxis);
int16_t ReadIMU2(uint8_t axxis);
float ReadGyro(uint8_t axxis);
void ReadSensores(void);
void TareaIMUs(void *pArg);

#endif /* INC_IMUS_H_ */
