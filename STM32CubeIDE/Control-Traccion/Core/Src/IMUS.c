/*
 * IMUS.c
 *
 *  Created on: Mar 8, 2023
 *      Author: carlos
 */
#include "IMUS.h"

int16_t accDataXYZ_1[3];


extern QueueHandle_t xQueueIMUs;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

int16_t IMU1AccelXYZ[3];
int16_t IMU2AccelXYZ[3];
float IMU2GyroXYZ[3];

void initAccelerometer (){
	  uint8_t buffer [1];
	  buffer [0]=0x40;
	  HAL_I2C_Mem_Write(&hi2c2, 0xD4, 0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);
	  HAL_I2C_Mem_Write(&hi2c1, 0xD4, 0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);
}


int16_t ReadIMU1(uint8_t axxis){
	  uint8_t buffer[2];

	  switch(axxis){
	  case 0:
		  HAL_I2C_Mem_Read(&hi2c1, 0xD4, 0x28,I2C_MEMADD_SIZE_8BIT, buffer, 2, 1000);
		  break;

	  case 1:
		  HAL_I2C_Mem_Read(&hi2c1, 0xD4, 0x2A,I2C_MEMADD_SIZE_8BIT, buffer, 2, 1000);
		  break;

	  case 2:
		  HAL_I2C_Mem_Read(&hi2c1, 0xD4, 0x2C,I2C_MEMADD_SIZE_8BIT, buffer, 2, 1000);
		  break;

	  default: break;
	  }
	  int16_t accel = ((int16_t)(buffer[1]<<8) | buffer[0])*0.061;//guardo la informacion de buffer

	  return accel;

}
int16_t ReadIMU2(uint8_t axxis){
	  uint8_t buffer[2];

	  switch(axxis){
	  case 0:
		  HAL_I2C_Mem_Read(&hi2c2, 0xD4, 0x28,I2C_MEMADD_SIZE_8BIT, buffer, 2, 1000);
		  break;

	  case 1:
		  HAL_I2C_Mem_Read(&hi2c2, 0xD4, 0x2A,I2C_MEMADD_SIZE_8BIT, buffer, 2, 1000);
		  break;

	  case 2:
		  HAL_I2C_Mem_Read(&hi2c2, 0xD4, 0x2C,I2C_MEMADD_SIZE_8BIT, buffer, 2, 1000);
		  break;

	  default: break;
	  }
	  int16_t accel = ((int16_t)(buffer[1]<<8) | buffer[0])*0.061;//guardo la informacion de buffer

	  return accel;

}

float ReadGyro(uint8_t axxis) {
	// Código del giroscopio
	return 0.;
}

void ReadSensores(void) {
	int i, j, k;

	for (i = 0; i < 3; i++)
		IMU1AccelXYZ[i] = ReadIMU1(i);

	for (j = 0; j < 3; j++)
		IMU2AccelXYZ[j] = ReadIMU2(j);

	for (k = 0; k < 3; k++)
		IMU2GyroXYZ[k] = ReadGyro(k);
}


void TareaIMUs(void * pArg) {
	initAccelerometer();
	struct CT_Sensores_t struc;

	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		// Leo sensores
		ReadSensores();

		// Guardo los datos en la estructura
		struc.IMU1accelX = IMU1AccelXYZ[0];
		struc.IMU1accelY = IMU1AccelXYZ[1];
		struc.IMU1accelZ = IMU1AccelXYZ[2];
		struc.IMU2accelX = IMU2AccelXYZ[0];
		struc.IMU2accelY = IMU2AccelXYZ[1];
		struc.IMU2accelZ = IMU2AccelXYZ[2];
		struc.IMU1gyroX = IMU2GyroXYZ[0];
		struc.IMU1gyroY = IMU2GyroXYZ[1];
		struc.IMU1gyroZ = IMU2GyroXYZ[2];

		xQueueSend(xQueueIMUs, &struc, portMAX_DELAY);
	}
}


