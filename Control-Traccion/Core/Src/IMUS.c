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

struct CT_Sensores_t struc;

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


void TareaIMUs(void * pArg) {

	struc.IMU1accelX = 0;
	struc.IMU1accelY = 1;
	struc.IMU1accelZ = 2;
	struc.IMU2accelX = 3;
	struc.IMU2accelY = 4;
	struc.IMU2accelZ = 5;
	struc.IMU2gyroX = 6.;
	struc.IMU2gyroY = 7.;
	struc.IMU2gyroZ = 8.;

	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		// Leo sensores
		struc.IMU1accelX = struc.IMU1accelX + 1;
		struc.IMU1accelY = struc.IMU1accelY + 1;
		struc.IMU1accelZ = struc.IMU1accelZ + 1;
		struc.IMU2accelX = ReadIMU2(0);
		struc.IMU2accelY = ReadIMU2(1);
		struc.IMU2accelZ = ReadIMU2(2);
		struc.IMU2gyroX = struc.IMU2gyroX + 1;
		struc.IMU2gyroY = struc.IMU2gyroY + 1;
		struc.IMU2gyroZ = struc.IMU2gyroZ + 1;

		xQueueSend(xQueueIMUs, &struc, portMAX_DELAY);
	}
}


