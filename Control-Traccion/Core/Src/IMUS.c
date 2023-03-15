/*
 * IMUS.c
 *
 *  Created on: Mar 8, 2023
 *      Author: carlos
 */
#include "IMUS.h"

int16_t accDataXYZ_1[3];
int16_t accDataXYZ_2[3];
float 	gyroDataXYZ[3];

extern QueueHandle_t xQueueIMUs;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

void InitIMUS(){

	uint8_t buffer[1];
	buffer[0] = 0x40;
	HAL_I2C_Mem_Write(&hi2c2, 0xD4,0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);
	HAL_I2C_Mem_Write(&hi2c1, 0xD4,0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);


}



int16_t ReadIMU1(uint8_t axxis) {

	uint8_t buffer1[2];
	int16_t accel;
	uint8_t address = 0x28 + (2*axxis);
	HAL_I2C_Mem_Read(&hi2c2, 0xD4, address,I2C_MEMADD_SIZE_8BIT,buffer1, 2, 1000);
	accel = ((int16_t)(buffer1[1]<<8) | buffer1[0])*0.061;
	return accel;

}

int16_t ReadIMU2(uint8_t axxis) {

	uint8_t buffer2[2];
	int16_t accel;
	uint8_t address = 0x2E + (2*axxis);
	HAL_I2C_Mem_Read(&hi2c2, 0xD4, address,I2C_MEMADD_SIZE_8BIT,buffer2, 2, 1000);
	accel = ((int16_t)(buffer2[1]<<8) | buffer2[0])*0.061;
	return accel;

}

void TareaIMUS(void *pArg){

	//InitSensores();
	//struct P5sensores_t struc;
	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		ReadIMU1(0);
		ReadIMU1(1);
		ReadIMU1(2);

		ReadIMU2(0);
		ReadIMU2(1);
		ReadIMU2(2);

//		struc.accelX = accDataXYZ[0];
//		struc.accelY = accDataXYZ[1];
//		struc.accelZ = accDataXYZ[2];

		xQueueSend(xQueueIMUs, 0, portMAX_DELAY);
	}



}

