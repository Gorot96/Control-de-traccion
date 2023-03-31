/*
 * mqtt_messaging.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Raul Duran
 */


//ChatGPT dice esto:

/*
#include "stm32f4xx_hal.h"
#include "mqtt.h"

// Definir las constantes necesarias para la conexión MQTT
#define MQTT_SERVER "broker.example.com"
#define MQTT_PORT 1883
#define MQTT_USERNAME "username"
#define MQTT_PASSWORD "password"
#define MQTT_CLIENTID "client_id"

// Definir las constantes necesarias para la publicación MQTT
#define MQTT_TOPIC "mytopic"
#define MQTT_PAYLOAD "Hello, MQTT!"

// Definir la función de retorno de llamada para la recepción de mensajes MQTT
void mqtt_callback(char* topic, uint8_t* payload, uint32_t length) {
  // La función de retorno de llamada puede procesar los mensajes MQTT recibidos
}

int main(void) {
  // Inicializar el hardware STM32 y la biblioteca MQTT
  HAL_Init();
  mqtt_init();

  // Conectar al servidor MQTT
  mqtt_connect(MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENTID);

  // Publicar un mensaje MQTT en un tema específico
  mqtt_publish(MQTT_TOPIC, MQTT_PAYLOAD);

  // Esperar por los mensajes MQTT entrantes
  while (1) {
    mqtt_yield(1000); // Espera por 1 segundo para recibir mensajes MQTT
  }
}


/* Texto:
En este ejemplo de código, se establece una conexión MQTT con el servidor broker.example.com utilizando el puerto 1883 y las credenciales de usuario username y password. Luego, se publica un mensaje MQTT en el tema mytopic con el contenido Hello, MQTT!. Por último, se espera por mensajes MQTT entrantes utilizando la función mqtt_yield.

Es importante tener en cuenta que este es solo un ejemplo básico y que se necesitará adaptar el código a la configuración específica de su proyecto, como la configuración de pines y periféricos de STM32. Además, asegúrese de que la biblioteca de MQTT que esté utilizando sea compatible con su versión de STM32CubeIDE.
 */
