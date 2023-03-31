/*
 * Sensores.c
 *
 *  Created on: Nov 29, 2020
 *      Author: rpaz
 */

#include "Sensores.h"

TickType_t sensor_period = 100;

float humidity;
float temperature;
float pressure;
int16_t accDataXYZ[3];
float 	gyroDataXYZ[3];
int16_t magDataXYZ[3];

extern QueueHandle_t xQueueSensors;

void InitSensores()
{
	BSP_HSENSOR_Init();
	BSP_PSENSOR_Init();
	BSP_TSENSOR_Init();

	BSP_ACCELERO_Init();
	BSP_GYRO_Init();
	BSP_MAGNETO_Init();
}

void ReadSensores()
{
	humidity = BSP_HSENSOR_ReadHumidity();
	pressure = BSP_PSENSOR_ReadPressure();
	temperature = BSP_TSENSOR_ReadTemp();

	BSP_ACCELERO_AccGetXYZ(accDataXYZ);
	BSP_GYRO_GetXYZ(gyroDataXYZ);
	BSP_MAGNETO_GetXYZ(magDataXYZ);
}


void TareaSensores(void *pArg)
{
	InitSensores();
	struct P5sensores_t struc;
	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		ReadSensores();

		struc.temperature = temperature;
		struc.humidity = humidity;
		struc.accelX = accDataXYZ[0];
		struc.accelY = accDataXYZ[1];
		struc.accelZ = accDataXYZ[2];

		xQueueSend(xQueueSensors, &struc, portMAX_DELAY);
	}
}
