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

float ReadGyro(uint8_t axxis) {
	// Código del giroscopio
	return 0.;
}


void TareaIMUs(void * pArg) {
	// Inicio sensores
	struct CT_Sensores_t struc;
	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		// Leo sensores
		struc.IMU1accelX = ReadIMU1(0);
		struc.IMU1accelY = ReadIMU1(1);
		struc.IMU1accelZ = ReadIMU1(2);
		struc.IMU2accelX = ReadIMU2(0);
		struc.IMU2accelY = ReadIMU2(1);
		struc.IMU2accelY = ReadIMU2(2);
		struc.IMU2gyroX = ReadGyro(0);
		struc.IMU2gyroY = ReadGyro(1);
		struc.IMU2gyroZ = ReadGyro(2);

		xQueueSend(xQueueIMUs, &struc, portMAX_DELAY);
	}
}


