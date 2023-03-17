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

void initAccelerometer (){
	  uint8_t buffer [1];
	  buffer [0]=0x40;
	  HAL_I2C_Mem_Write(&hi2c2, 0xD4, 0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);
	  HAL_I2C_Mem_Write(&hi2c1, 0xD4, 0x10,I2C_MEMADD_SIZE_8BIT, buffer, 1, 1000);
}

int16_t readAccel1(uint8_t axxis){
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
int16_t readAccel2(uint8_t axxis){
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

//void TareaIMUS(void *pArg){
//
//	//InitSensores();
//	//struct P5sensores_t struc;
//	while(1)
//	{
//		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
//		ReadIMUS();
//
////		struc.accelX = accDataXYZ[0];
////		struc.accelY = accDataXYZ[1];
////		struc.accelZ = accDataXYZ[2];
//
//		xQueueSend(xQueueIMUs, 0, portMAX_DELAY);
//	}
//
//
//
//}

