/*
 * IMUS.h
 *
 *  Created on: Mar 8, 2023
 *      Author: carlo
 */

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

#ifndef INC_IMUS_H_
#define INC_IMUS_H_

void InitIMUS();
void ReadIMUS();
void TareaIMUS(void *pArg);

#endif /* INC_IMUS_H_ */
