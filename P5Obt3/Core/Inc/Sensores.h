/*
 * Sensores.h
 *
 *  Created on: Nov 29, 2020
 *      Author: rpaz
 */

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"

#include "../BSP/stm32l475e_iot01.h"
#include "../BSP/stm32l475e_iot01_accelero.h"
#include "../BSP/stm32l475e_iot01_gyro.h"
#include "../BSP/stm32l475e_iot01_magneto.h"
#include "../BSP/stm32l475e_iot01_hsensor.h"
#include "../BSP/stm32l475e_iot01_psensor.h"
#include "../BSP/stm32l475e_iot01_tsensor.h"
#include "../BSP/stm32l475e_iot01_qspi.h"

#ifndef INC_SENSORES_H_
#define INC_SENSORES_H_

void InitSensores();
void ReadSensores();
void TareaSensores(void *pArg);

#endif /* INC_SENSORES_H_ */
