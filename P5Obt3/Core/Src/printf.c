/*
 * printf.c
 *
 *  Created on: 30 nov. 2020
 *      Author: rpaz
 */

#include "main.h"
#include "cmsis_os.h"
#include "semphr.h"

extern UART_HandleTypeDef huart1;
extern SemaphoreHandle_t xSemaphore;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	static signed long xHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR(xSemaphore, NULL);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}

int __io_putchar(int ch)
{
	xSemaphoreTake(xSemaphore, 0xffff);

	HAL_UART_Transmit_IT(&huart1, (uint8_t*) &ch, 1);

	//while(HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 30000))
	//{
	//	;
	//}
	return ch;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static signed long xHigherPriorityTaskWoken = pdFALSE;

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

int __io_getchar(void)
{
	uint8_t ch = 0;

	//while(HAL_OK != HAL_UART_Receive(&huart1, &ch, 1, 30000))
	//{
	//	;
	//}
	HAL_UART_Receive(&huart1, &ch, 1, 0);

	return ch;


}
