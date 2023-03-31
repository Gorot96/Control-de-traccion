/*
 * mqtt_messaging.h
 *
 *  Created on: 31 mar. 2023
 *      Author: Raul Duran
 */

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "wifi.h"
#include "MQTTPacket.h"

#ifndef INC_MQTT_MESSAGING_H_
#define INC_MQTT_MESSAGING_H_

static void prvTemperaturePublisher(void *pvParameters);
long unsigned int network_gettime_ms(void);

#endif /* INC_MQTT_MESSAGING_H_ */
