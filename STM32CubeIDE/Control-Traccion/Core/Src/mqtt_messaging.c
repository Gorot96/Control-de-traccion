/*
 * mqtt_messaging.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Raul Duran
 */

#include "mqtt_messaging.h"

// Settings.
#define CONNECTION_KEEPALIVE_S 60UL/* Update SSID and PASSWORD with own Access point settings */
#define SSID     "Redmi Note 8 Pro de Raul"
#define PASSWORD "e5292c6c45df"
#define PORT           80

#define TERMINAL_USE

#define WIFI_WRITE_TIMEOUT 10000
#define WIFI_READ_TIMEOUT  10000
#define SOCKET                 0


#ifdef  TERMINAL_USE
#define LOG(a) printf a
#else
#define LOG(a)
#endif
/* Private defines -----------------------------------------------------------*/


static  uint8_t http[1024];
static  uint8_t  IP_Addr[4];


// Prototipos
int wifi_server(void);

static  WIFI_Status_t SendWebPage(struct CT_Sensores_t sensors);
static  int wifi_start(void);
static  int wifi_connect(void);
static  bool WebServerProcess(void);



static int wifi_start(void)
{
  uint8_t  MAC_Addr[6];

 /*Initialize and use WIFI module */
  if(WIFI_Init() ==  WIFI_STATUS_OK)
  {
    LOG(("ES-WIFI Initialized.\r\n"));
    if(WIFI_GetMAC_Address(MAC_Addr) == WIFI_STATUS_OK)
    {
      LOG(("> es-wifi module MAC Address : %X:%X:%X:%X:%X:%X\r\n",
               MAC_Addr[0],
               MAC_Addr[1],
               MAC_Addr[2],
               MAC_Addr[3],
               MAC_Addr[4],
               MAC_Addr[5]));
    }
    else
    {
      LOG(("> ERROR : CANNOT get MAC address\r\n"));
      return -1;
    }
  }
  else
  {
    return -1;
  }
  return 0;
}



int wifi_connect(void)
{

  wifi_start();

  LOG(("\r\nConnecting to %s , %s\r\n",SSID,PASSWORD));
  if( WIFI_Connect(SSID, PASSWORD, WIFI_ECN_WPA2_PSK) == WIFI_STATUS_OK)
  {
    if(WIFI_GetIP_Address(IP_Addr) == WIFI_STATUS_OK)
    {
      LOG(("> es-wifi module connected: got IP Address : %d.%d.%d.%d\r\n",
               IP_Addr[0],
               IP_Addr[1],
               IP_Addr[2],
               IP_Addr[3]));
    }
    else
    {
		  LOG((" ERROR : es-wifi module CANNOT get IP address\r\n"));
      return -1;
    }
  }
  else
  {
		 LOG(("ERROR : es-wifi module NOT connected\r\n"));
     return -1;
  }
  return 0;
}

static void prvTemperaturePublisher(void *pvParameters) {
	unsigned char buffer[128];
	MQTTTransport transporter;
	int result;
	int length;

	// State machine.
	int internalState = 0;
	while(1) {
		switch(internalState){
		case 0:	{
			// Initialize the network and connect to
			wifi_start();
			if(network_connect("iot.eclipse.org", 1883, CONNECTION_KEEPALIVE_S, false) == 0){
				// To the next state.
				internalState++;
			}
		} break;
		case 1:	{
			// Populate the transporter.
			transporter.sck = &transport_socket;
			transporter.getfn = transport_getdatanb;
			transporter.state = 0;

			// Populate the connect struct.
			MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
			connectData.MQTTVersion = 3;
			connectData.clientID.cstring = "TemperaturePublisher";
			connectData.keepAliveInterval = CONNECTION_KEEPALIVE_S * 2;
			length = MQTTSerialize_connect(buffer, sizeof(buffer), &connectData);

			// Send CONNECT to the mqtt broker.
			if((result = transport_sendPacketBuffer(transport_socket, buffer, length)) == length){
				// To the next state.
				internalState++;
			} else {
				// Start over.
				internalState = 0;
			}
		} break;
		case 2:	{
			// Wait for CONNACK response from the mqtt broker.
			while(true) {
				// Wait until the transfer is done.
				if((result = MQTTPacket_readnb(buffer, sizeof(buffer), &transporter)) == CONNACK){
					// Check if the connection was accepted.
					unsigned char sessionPresent, connack_rc;
					if ((MQTTDeserialize_connack(&sessionPresent, &connack_rc, buffer, sizeof(buffer)) != 1) || (connack_rc != 0)){
						// Start over.
						internalState = 0;
						break;
					}else{
						// To the next state.
						internalState++;
						break;
					}
				} else if (result == -1) {
					// Start over.
					internalState = 0;
					break;
				}
			}
		} break;
		case 3:	{
			// Turn the LED on.
			vLedWrite(0, true);

			// Set delay timer.
			TickType_t wakeTime = xTaskGetTickCount();

			// Populate the publish message.
			MQTTString topicString = MQTTString_initializer;
			topicString.cstring = "temperature/value";
			unsigned char payload[16];
			length = MQTTSerialize_publish(buffer, sizeof(buffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%d", (int)temperature_read())));

			// Send PUBLISH to the mqtt broker.
			if((result = transport_sendPacketBuffer(transport_socket, buffer, length)) == length){
				// Turn the LED off.
				vLedWrite(0, false);

				// Wait 5s.
				vTaskDelayUntil(&wakeTime, pdMS_TO_TICKS(5000));
			} else {
				// Start over.
				internalState = 0;
			}
		} break;
		default:
			internalState = 0;
		}
	}
}

/*
 * @brief Time provider for the networkwrapper..
 * @return Time in ms.
 */
long unsigned int network_gettime_ms(void) {
	return (xTaskGetTickCount() * portTICK_PERIOD_MS);
}


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
