/*
 * IMUS.c
 *
 *  Created on: Mar 8, 2023
 *      Author: carlos
 */
#include "IMUS.h"

int16_t accDataXYZ[3];
float 	gyroDataXYZ[3];

extern QueueHandle_t xQueueSensors;

void InitIMUS(){

	uint8_t buffer[1];
	buffer[0] = 0x40;
	HAL_I2C_Mem_Write(&hi2c2, 0xD4,0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);
	HAL_I2C_Mem_Write(&hi2c1, 0xD4,0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);


}

void ReadIMUS(){

	uint8_t buffer[2];
	int16_t accel;
	uint8_t address = 0x28 + (2*axxis);
	HAL_I2C_Mem_Read(&hi2c2, 0xD4, address,I2C_MEMADD_SIZE_8BIT,
	buffer, 2, 1000);
	accel = ((int16_t)(buffer[1]<<8) | buffer[0])*0.061;
	return accel;

}

void TareaIMUS(void *pArg){

	InitSensores();
		struct P5sensores_t struc;
		while(1)
		{
			ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
			ReadIMUS();

			struc.accelX = accDataXYZ[0];
			struc.accelY = accDataXYZ[1];
			struc.accelZ = accDataXYZ[2];

			xQueueSend(xQueueIMUS, &struc, portMAX_DELAY);
		}



}

