/*
 * mqtt_messaging.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Raul Duran
 */

#include <unistd.h>
#include "main.h"
#include "es_wifi.h"
#include "wifi.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "Tareas.h"
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include "MQTTPacket.h"
#include "transport.h"

/* Update SSID and PASSWORD with own Access point settings */
#define SSID     "Redmi Note 8 Pro de Raul"
#define PASSWORD "e5292c6c45df"
#define PORT           1883

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

static  uint8_t  IP_Addr[4];
static uint8_t wifi_isConnected = 0;


// Prototipos
int wifi_server(void);

static  int wifi_start(void);
static  int wifi_connect(void);
static  int mqtt_connection(void);



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

int wifi_server(void)
{
  bool StopServer = false;

  LOG(("\r\nRunning HTML Server test\r\n"));
  if (wifi_connect()!=0) return -1;


  if (WIFI_STATUS_OK!=WIFI_StartServer(SOCKET, WIFI_TCP_PROTOCOL, 1, "", PORT))
  {
    LOG(("ERROR: Cannot start server.\r\n"));
  }

  LOG(("Server is running and waiting for an HTTP  Client connection to %d.%d.%d.%d\r\n",IP_Addr[0],IP_Addr[1],IP_Addr[2],IP_Addr[3]));

  do
  {
    uint8_t RemoteIP[4];
    uint16_t RemotePort;


    while (WIFI_STATUS_OK != WIFI_WaitServerConnection(SOCKET,1000,RemoteIP,&RemotePort))
    {
        LOG(("Waiting connection to  %d.%d.%d.%d\r\n",IP_Addr[0],IP_Addr[1],IP_Addr[2],IP_Addr[3]));

    }

    LOG(("Client connected %d.%d.%d.%d:%d\r\n",RemoteIP[0],RemoteIP[1],RemoteIP[2],RemoteIP[3],RemotePort));

    wifi_isConnected = 1;
    StopServer=mqtt_connection();

    if(WIFI_CloseServerConnection(SOCKET) != WIFI_STATUS_OK)
    {
      LOG(("ERROR: failed to close current Server connection\r\n"));
      return -1;
    }
  }
  while(StopServer == false);

  if (WIFI_STATUS_OK!=WIFI_StopServer(SOCKET))
  {
    LOG(("ERROR: Cannot stop server.\r\n"));
  }

  wifi_isConnected = 0;
  LOG(("Server is stop\r\n"));
  return 0;
}

extern SPI_HandleTypeDef hspi3;

/******************************************************************************/
/*                 STM32L4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file.                                                                     */
/************************************************************
 *															*
 *		Rutinas de servicio de interrupciones				*
 *															*
 ************************************************************/

/**
  * @brief  This function handles external lines 1interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
 HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
 portYIELD_FROM_ISR(pdFALSE);
}

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
    case (GPIO_PIN_1):
    {
      SPI_WIFI_ISR();
      break;
    }
    default:
    {
      break;
    }
  }
  portYIELD_FROM_ISR(pdFALSE);
}

/**
  * @brief  SPI3 line detection callback.
  * @param  None
  * @retval None
  */
extern  SPI_HandleTypeDef hspi;
void SPI3_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&hspi);
  portYIELD_FROM_ISR(pdFALSE);
}

/***************************************************************************/

int toStop = 0;

void stop_init(void);
/* */

/* Same as above, we provide a set of functions to test/debug on a friendlier system;
the init() and  close() actions on the serial are just for this, you will probably
handle this on whatever handles your media in your application */
int sampleserial_init(void);
void sampleserial_close(void);
int samplesend(unsigned char *address, unsigned int bytes);
int samplerecv(unsigned char *address, unsigned int maxbytes);
/* */

/* You will use your hardware specifics here, see transport.h. */
static transport_iofunctions_t iof = {samplesend, samplerecv};

enum states { READING, PUBLISHING };

int mqtt_connection(void) {
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	int rc = 0;
	int mysock = 0;
	unsigned char buf[200];
	int buflen = sizeof(buf);
	int msgid = 1;
	MQTTString topicString = MQTTString_initializer;
	int req_qos = 0;
	char* payload = "mypayload";
	int payloadlen = strlen(payload);
	int len = 0;
	MQTTTransport mytransport;
	int state = READING;

	stop_init();
	sampleserial_init();

	mysock = transport_open(&iof);
	if(mysock < 0)
		return mysock;
	/* You will (or already are) 'somehow' connect(ed) to host:port via your hardware specifics. E.g.:
		you have a serial (RS-232/UART) link
		you have a cell modem and you issue your AT+ magic
		you have some TCP/IP which is not lwIP (nor a full-fledged socket compliant one)
		 and you TCP connect
	*/

	mytransport.sck = &mysock;
	mytransport.getfn = transport_getdatanb;
	mytransport.state = 0;
	data.clientID.cstring = "me";
	data.keepAliveInterval = 20;
	data.cleansession = 1;
	data.username.cstring = "testuser";
	data.password.cstring = "testpassword";

	len = MQTTSerialize_connect(buf, buflen, &data);

	// Ejemplo 1:
	/* This one blocks until it finishes sending, you will probably not want this in real life,
	in such a case replace this call by a scheme similar to the one you'll see in the main loop */
	rc = transport_sendPacketBuffer(mysock, buf, len);

	printf("Sent MQTT connect\n");
	/* wait for connack */
	do {
		int frc;
		if ((frc=MQTTPacket_readnb(buf, buflen, &mytransport)) == CONNACK){
			unsigned char sessionPresent, connack_rc;
			if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0){
				printf("Unable to connect, return code %d\n", connack_rc);
				goto exit;
			}
			break;
		}
		else if (frc == -1)
			goto exit;
	} while (1); /* handle timeouts here */

	printf("MQTT connected\n");
	/* subscribe */
	topicString.cstring = "substopic";
	len = MQTTSerialize_subscribe(buf, buflen, 0, msgid, 1, &topicString, &req_qos);

	/* This is equivalent to the one above, but using the non-blocking functions. You will probably not want this in real life,
	in such a case replace this call by a scheme similar to the one you'll see in the main loop */
	transport_sendPacketBuffernb_start(mysock, buf, len);
	while((rc=transport_sendPacketBuffernb(mysock)) != TRANSPORT_DONE);
	do {
		int frc;
		if ((frc=MQTTPacket_readnb(buf, buflen, &mytransport)) == SUBACK){ /* wait for suback */
			unsigned short submsgid;
			int subcount;
			int granted_qos;

			rc = MQTTDeserialize_suback(&submsgid, 1, &subcount, &granted_qos, buf, buflen);
			if (granted_qos != 0){
				printf("granted qos != 0, %d\n", granted_qos);
				goto exit;
			}
			break;
		}
		else if (frc == -1)
			goto exit;
	} while (1); /* handle timeouts here */
	printf("Subscribed\n");


	/* loop getting msgs on subscribed topic */
	topicString.cstring = "pubtopic";
	state = READING;
	while (!toStop)	{
		/* do other stuff here */
		switch(state){
		case READING:
			if((rc=MQTTPacket_readnb(buf, buflen, &mytransport)) == PUBLISH){
				unsigned char dup;
				int qos;
				unsigned char retained;
				unsigned short msgid;
				int payloadlen_in;
				unsigned char* payload_in;
				int rc;
				MQTTString receivedTopic;

				rc = MQTTDeserialize_publish(&dup, &qos, &retained, &msgid, &receivedTopic,
						&payload_in, &payloadlen_in, buf, buflen);
				printf("message arrived %.*s\n", payloadlen_in, payload_in);
				printf("publishing reading\n");
				state = PUBLISHING;
				len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, (unsigned char*)payload, payloadlen);
				transport_sendPacketBuffernb_start(mysock, buf, len);
			} else if(rc == -1){
				/* handle I/O errors here */
				goto exit;
			}	/* handle timeouts here */
			break;
		case PUBLISHING:
			switch(transport_sendPacketBuffernb(mysock)){
			case TRANSPORT_DONE:
				printf("Published\n");
				state = READING;
				break;
			case TRANSPORT_ERROR:
				/* handle any I/O errors here */
				goto exit;
				break;
			case TRANSPORT_AGAIN:
			default:
				/* handle timeouts here, not probable unless there is a hardware problem */
				break;
			}
			break;
		}
	}

	printf("disconnecting\n");
	len = MQTTSerialize_disconnect(buf, buflen);
	/* Same blocking related stuff here */
	rc = transport_sendPacketBuffer(mysock, buf, len);

exit:
	transport_close(mysock);

	sampleserial_close();
	return 0;
}

/* To stop the sample */
void cfinish(int sig)
{
	signal(SIGINT, NULL);
	toStop = 1;
}

void stop_init(void)
{
	signal(SIGINT, cfinish);
	signal(SIGTERM, cfinish);
}

/* Serial hack:
Simulate serial transfers on an established TCP connection
 */
static int sockfd;

int sampleserial_init(void)
{
	if (!wifi_isConnected) {
		printf("ERROR connecting\n");
		return -1;
	}
	printf("- TCP Connected to Eclipse\n");
		/* set to non-blocking */
	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);

	return 0;
}

void sampleserial_close(void)
{
	close(sockfd);
}

int samplesend(unsigned char *address, unsigned int bytes)
{
int len;

	if(rand() > (RAND_MAX/2))	// 50% probability of being busy
		return 0;
	if(rand() > (RAND_MAX/2)){	// 50% probability of sending half the requested data (no room in buffer)
		if(bytes > 1)
			bytes /= 2;
	}
	if((len = write(sockfd, address, bytes)) >= 0)
		return len;
	if(errno == EAGAIN)
		return 0;
	return -1;
}

int samplerecv(unsigned char *address, unsigned int maxbytes)
{
int len;

	if(rand() > (RAND_MAX/2))	// 50% probability of no data
		return 0;
	if(rand() > (RAND_MAX/2)){	// 50% probability of getting half the requested data (not arrived yet)
		if(maxbytes > 1){
			maxbytes /= 2;
		}
	}
	if((len = read(sockfd, address, maxbytes)) >= 0)
		return len;
	if(errno == EAGAIN)
		return 0;
	return -1;
}
