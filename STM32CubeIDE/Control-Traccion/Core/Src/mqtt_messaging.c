///*
// * mqtt_messaging.c
// *
// *  Created on: Mar 24, 2023
// *      Author: Raul Duran
// */
//
//#include <unistd.h>
//#include <fcntl.h>
//#include <errno.h>
//#include <stdlib.h>
//#include <signal.h>
//#include <time.h>
//
//#include "main.h"
//#include "es_wifi.h"
//#include "wifi.h"
//#include "cmsis_os.h"
//#include "semphr.h"
//#include "Tareas.h"
//
//#define MQTT_DO_NOT_USE_CUSTOM_CONFIG
//#include "FreeRTOS.h"
//#include "core_mqtt.h"
//#include "transport_interface.h"
//
///* Update SSID and PASSWORD with own Access point settings */
//#define SSID     "Redmi Note 8 Pro de Raul"
//#define PASSWORD "e5292c6c45df"
//#define PORT           1883
//
//#define TERMINAL_USE
//
//#define WIFI_WRITE_TIMEOUT 10000
//#define WIFI_READ_TIMEOUT  10000
//#define SOCKET                 0
//
//
//#ifdef  TERMINAL_USE
//#define LOG(a) printf a
//#else
//#define LOG(a)
//#endif
///* Private defines -----------------------------------------------------------*/
//
//static  uint8_t  IP_Addr[4];
//static uint8_t wifi_isConnected = 0;
//
//
//// Prototipos
//int wifi_server(void);
//
//static  int wifi_start(void);
//static  int wifi_connect(void);
//
//int mqtt_connection(void);
//
//
//
//static int wifi_start(void)
//{
//  uint8_t  MAC_Addr[6];
//
// /*Initialize and use WIFI module */
//  if(WIFI_Init() ==  WIFI_STATUS_OK)
//  {
//    LOG(("ES-WIFI Initialized.\r\n"));
//    if(WIFI_GetMAC_Address(MAC_Addr) == WIFI_STATUS_OK)
//    {
//      LOG(("> es-wifi module MAC Address : %X:%X:%X:%X:%X:%X\r\n",
//               MAC_Addr[0],
//               MAC_Addr[1],
//               MAC_Addr[2],
//               MAC_Addr[3],
//               MAC_Addr[4],
//               MAC_Addr[5]));
//    }
//    else
//    {
//      LOG(("> ERROR : CANNOT get MAC address\r\n"));
//      return -1;
//    }
//  }
//  else
//  {
//    return -1;
//  }
//  return 0;
//}
//
//
//
//int wifi_connect(void)
//{
//
//  wifi_start();
//
//  LOG(("\r\nConnecting to %s , %s\r\n",SSID,PASSWORD));
//  if( WIFI_Connect(SSID, PASSWORD, WIFI_ECN_WPA2_PSK) == WIFI_STATUS_OK)
//  {
//    if(WIFI_GetIP_Address(IP_Addr) == WIFI_STATUS_OK)
//    {
//      LOG(("> es-wifi module connected: got IP Address : %d.%d.%d.%d\r\n",
//               IP_Addr[0],
//               IP_Addr[1],
//               IP_Addr[2],
//               IP_Addr[3]));
//    }
//    else
//    {
//		  LOG((" ERROR : es-wifi module CANNOT get IP address\r\n"));
//      return -1;
//    }
//  }
//  else
//  {
//		 LOG(("ERROR : es-wifi module NOT connected\r\n"));
//     return -1;
//  }
//  return 0;
//}
//
//int wifi_server(void)
//{
//  bool StopServer = false;
//
//  LOG(("\r\nRunning HTML Server test\r\n"));
//  if (wifi_connect()!=0) return -1;
//
//
//  if (WIFI_STATUS_OK!=WIFI_StartServer(SOCKET, WIFI_TCP_PROTOCOL, 1, "", PORT))
//  {
//    LOG(("ERROR: Cannot start server.\r\n"));
//  }
//
//  LOG(("Server is running and waiting for an HTTP  Client connection to %d.%d.%d.%d\r\n",IP_Addr[0],IP_Addr[1],IP_Addr[2],IP_Addr[3]));
//
//  do
//  {
//    uint8_t RemoteIP[4];
//    uint16_t RemotePort;
//
//
//    while (WIFI_STATUS_OK != WIFI_WaitServerConnection(SOCKET,1000,RemoteIP,&RemotePort))
//    {
//        LOG(("Waiting connection to  %d.%d.%d.%d\r\n",IP_Addr[0],IP_Addr[1],IP_Addr[2],IP_Addr[3]));
//
//    }
//
//    LOG(("Client connected %d.%d.%d.%d:%d\r\n",RemoteIP[0],RemoteIP[1],RemoteIP[2],RemoteIP[3],RemotePort));
//
//    wifi_isConnected = 1;
//    StopServer=mqtt_connection();
//
//    if(WIFI_CloseServerConnection(SOCKET) != WIFI_STATUS_OK)
//    {
//      LOG(("ERROR: failed to close current Server connection\r\n"));
//      return -1;
//    }
//  }
//  while(StopServer == false);
//
//  if (WIFI_STATUS_OK!=WIFI_StopServer(SOCKET))
//  {
//    LOG(("ERROR: Cannot stop server.\r\n"));
//  }
//
//  wifi_isConnected = 0;
//  LOG(("Server is stop\r\n"));
//  return 0;
//}
//
//extern SPI_HandleTypeDef hspi3;
//
///******************************************************************************/
///*                 STM32L4xx Peripherals Interrupt Handlers                   */
///*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
///*  available peripheral interrupt handler's name please refer to the startup */
///*  file.                                                                     */
///************************************************************
// *															*
// *		Rutinas de servicio de interrupciones				*
// *															*
// ************************************************************/
//
///**
//  * @brief  This function handles external lines 1interrupt request.
//  * @param  None
//  * @retval None
//  */
//void EXTI1_IRQHandler(void)
//{
// HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
// portYIELD_FROM_ISR(pdFALSE);
//}
//
///**
//  * @brief  EXTI line detection callback.
//  * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
//  * @retval None
//  */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//  switch (GPIO_Pin)
//  {
//    case (GPIO_PIN_1):
//    {
//      SPI_WIFI_ISR();
//      break;
//    }
//    default:
//    {
//      break;
//    }
//  }
//  portYIELD_FROM_ISR(pdFALSE);
//}
//
///**
//  * @brief  SPI3 line detection callback.
//  * @param  None
//  * @retval None
//  */
//extern  SPI_HandleTypeDef hspi;
//void SPI3_IRQHandler(void)
//{
//  HAL_SPI_IRQHandler(&hspi);
//  portYIELD_FROM_ISR(pdFALSE);
//}
//
///***************************************************************************/
//
/////*******************************************************************************
//// * Copyright (c) 2014 IBM Corp.
//// *
//// * All rights reserved. This program and the accompanying materials
//// * are made available under the terms of the Eclipse Public License v1.0
//// * and Eclipse Distribution License v1.0 which accompany this distribution.
//// *
//// * The Eclipse Public License is available at
//// *    http://www.eclipse.org/legal/epl-v10.html
//// * and the Eclipse Distribution License is available at
//// *   http://www.eclipse.org/org/documents/edl-v10.php.
//// *
//// * Contributors:
//// *    Sergio R. Caprile
//// *******************************************************************************/
////
////#define KEEPALIVE_INTERVAL 20
////
/////* This is to get a timebase in seconds to test the sample */
////
////time_t old_t;
////void start_ping_timer(void)
////{
////	time(&old_t);
////	old_t += KEEPALIVE_INTERVAL/2 + 1;
////}
////
////int time_to_ping(void)
////{
////time_t t;
////
////	time(&t);
////	if(t >= old_t)
////	  	return 1;
////	return 0;
////}
////
/////* This is in order to get an asynchronous signal to stop the sample,
////as the code loops waiting for msgs on the subscribed topic.
////Your actual code will depend on your hw and approach, but this sample can be
////run on Linux so debugging of the non-hardware specific bare metal code is easier.
////See at bottom of file for details */
////
////int toStop = 0;
////
////void stop_init(void);
/////* */
////
/////* Same as above, we provide a set of functions to test/debug on a friendlier system;
////the init() and  close() actions on the serial are just for this, you will probably
////handle this on whatever handles your media in your application */
////void sampleserial_init(void);
////void sampleserial_close(void);
////int samplesend(unsigned char *address, unsigned int bytes);
////int samplerecv(unsigned char *address, unsigned int maxbytes);
/////* */
////
/////* You will use your hardware specifics here, see transport.h. */
////static transport_iofunctions_t iof = {samplesend, samplerecv};
////
////enum states { IDLE, SENDPING, GETPONG };
////
////int mqtt_connection(void)
////{
////	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
////	int rc = 0;
////	int mysock = 0;
////	unsigned char buf[200];
////	int buflen = sizeof(buf);
////	int len = 0;
////	MQTTTransport mytransport;
////	int state;
////
////	stop_init();
////	sampleserial_init();
////
////	mysock = transport_open(&iof);
////	if(mysock < 0)
////		return mysock;
////	/* You will (or already are) 'somehow' connect(ed) to host:port via your hardware specifics. E.g.:
////		you have a serial (RS-232/UART) link
////		you have a cell modem and you issue your AT+ magic
////		you have some TCP/IP which is not lwIP (nor a full-fledged socket compliant one)
////		 and you TCP connect
////	*/
////
////	mytransport.sck = &mysock;
////	mytransport.getfn = transport_getdatanb;
////	mytransport.state = 0;
////	data.clientID.cstring = "me";
////	data.keepAliveInterval = KEEPALIVE_INTERVAL;
////	data.cleansession = 1;
////	data.username.cstring = "testuser";
////	data.password.cstring = "testpassword";
////
////	len = MQTTSerialize_connect(buf, buflen, &data);
////	/* This one blocks until it finishes sending, you will probably not want this in real life,
////	in such a case replace this call by a scheme similar to the one you'll see in the main loop */
////	rc = transport_sendPacketBuffer(mysock, buf, len);
////
////	printf("Sent MQTT connect\n");
////	/* wait for connack */
////	do {
////		int frc;
////		if ((frc=MQTTPacket_readnb(buf, buflen, &mytransport)) == CONNACK){
////			unsigned char sessionPresent, connack_rc;
////			if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0){
////				printf("Unable to connect, return code %d\n", connack_rc);
////				goto exit;
////			}
////			break;
////		}
////		else if (frc == -1)
////			goto exit;
////	} while (1); /* handle timeouts here */
////
////	printf("MQTT connected\n");
////	start_ping_timer();
////	state = IDLE;
////	while (!toStop)	{
////		switch(state){
////		case IDLE:
////			if(time_to_ping()){
////				len = MQTTSerialize_pingreq(buf, buflen);
////				transport_sendPacketBuffernb_start(mysock, buf, len);
////				state = SENDPING;
////			}
////			break;
////		case SENDPING:
////			switch(transport_sendPacketBuffernb(mysock)){
////			case TRANSPORT_DONE:
////				printf("Ping...");
////				start_ping_timer();
////				state = GETPONG;
////				break;
////			case TRANSPORT_ERROR:
////				/* handle any I/O errors here */
////				goto exit;
////				break;
////			case TRANSPORT_AGAIN:
////			default:
////				/* handle timeouts here, not probable unless there is a hardware problem */
////				break;
////			}
////			break;
////		case GETPONG:
////			if((rc=MQTTPacket_readnb(buf, buflen, &mytransport)) == PINGRESP){
////				printf("Pong\n");
////				start_ping_timer();
////				state = IDLE;
////			} else if(rc == -1){
////				/* handle I/O errors here */
////				printf("OOPS\n");
////				goto exit;
////			}	/* handle timeouts here */
////			break;
////		}
////	}
////
////	printf("disconnecting\n");
////	len = MQTTSerialize_disconnect(buf, buflen);
////	/* Same blocking related stuff here */
////	rc = transport_sendPacketBuffer(mysock, buf, len);
////
////exit:
////	transport_close(mysock);
////
////	sampleserial_close();
////	return 0;
////}
////
////
/////* To stop the sample */
////void cfinish(int sig)
////{
////	signal(SIGINT, NULL);
////	toStop = 1;
////}
////
////void stop_init(void)
////{
////	signal(SIGINT, cfinish);
////	signal(SIGTERM, cfinish);
////}
////
/////* Serial hack:
////Simulate serial transfers on an established TCP connection
//// */
////
////static int sockfd;
////
////void sampleserial_init(void)
////{
////	uint8_t server_ip[4] = {192, 168, 196, 74};
////	WIFI_Status_t status;
////
////	status = WIFI_OpenClientConnection(sockfd, WIFI_TCP_PROTOCOL, "RN8P_MQTT", server_ip, 1883, 1883);
////
////	if (status != WIFI_STATUS_OK) {
////		printf("ERROR connecting\n");
////		exit(-1);
////	}
////	printf("- TCP Connected to Eclipse\n");
////        /* set to non-blocking */
////	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);
////}
////
////void sampleserial_close(void)
////{
////	close(sockfd);
////}
////
////int samplesend(unsigned char *address, unsigned int bytes)
////{
////int len;
////
////	if((len = write(sockfd, address, bytes)) >= 0)
////		return len;
////	if(errno == EAGAIN)
////		return 0;
////	return -1;
////}
////
////int samplerecv(unsigned char *address, unsigned int maxbytes)
////{
////int len;
////
////	if((len = read(sockfd, address, maxbytes)) >= 0)
////		return len;
////	if(errno == EAGAIN)
////		return 0;
////	return -1;
////}
//
//
////static void prvMQTTDemoTask( void * pvParameters )
////{
////    uint32_t ulPublishCount = 0U, ulTopicCount = 0U;
////    const uint32_t ulMaxPublishCount = 5UL;
////    NetworkContext_t xNetworkContext = { 0 };
////    MQTTContext_t xMQTTContext;
////    MQTTStatus_t xMQTTStatus;
////    PlaintextTransportStatus_t xNetworkStatus;
////
////    /***
////     * For readability, error handling in this function is restricted to
////     * the use of asserts().
////     ***/
////
////    for( ; ; )
////    {
////        /*************************** Connect. *********************************/
////
////        /* Attempt to connect to the MQTT broker.  The socket is returned in
////         * the network context structure. */
////        xNetworkStatus = prvConnectToServerWithBackoffRetries( &xNetworkContext );
////        configASSERT( xNetworkStatus == PLAINTEXT_TRANSPORT_SUCCESS );
////
////        /* Connect to the MQTT broker using the already connected TCP socket. */
////        prvCreateMQTTConnectionWithBroker( &xMQTTContext, &xNetworkContext );
////
////        /**************************** Subscribe. ******************************/
////
////        /* Subscribe to the test topic. */
////        prvMQTTSubscribeWithBackoffRetries( &xMQTTContext );
////
////        /******************* Publish and Keep Alive Loop. *********************/
////
////        /* Publish messages with QoS0, then send and process Keep Alive
////         * messages. */
////        for( ulPublishCount = 0; ulPublishCount < ulMaxPublishCount; ulPublishCount++ )
////        {
////            prvMQTTPublishToTopic( &xMQTTContext );
////
////            /* Process the incoming publish echo. Since the application subscribed
////             * to the same topic, the broker will send the same publish message
////             * back to the application.  Note there is a separate demo that
////             * shows how to use coreMQTT in a thread safe way - in which case the
////             * MQTT protocol runs in the background and this call is not
////             * required. */
////            xMQTTStatus = MQTT_ProcessLoop( &xMQTTContext,
////                                            mqttexamplePROCESS_LOOP_TIMEOUT_MS );
////            configASSERT( xMQTTStatus == MQTTSuccess );
////
////            /* Leave the connection idle for some time. */
////            vTaskDelay( mqttexampleDELAY_BETWEEN_PUBLISHES );
////        }
////
////        /******************** Unsubscribe from the topic. *********************/
////
////        prvMQTTUnsubscribeFromTopic( &xMQTTContext );
////
////        /* Process the incoming packet from the broker.  Note there is a separate
////         * demo that shows how to use coreMQTT in a thread safe way - in which case
////         * the MQTT protocol runs in the background and this call is not required. */
////        xMQTTStatus = MQTT_ProcessLoop( &xMQTTContext,
////                                        mqttexamplePROCESS_LOOP_TIMEOUT_MS );
////        configASSERT( xMQTTStatus == MQTTSuccess );
////
////        /**************************** Disconnect. *****************************/
////
////        xMQTTStatus = MQTT_Disconnect( &xMQTTContext );
////
////        /* Close the network connection. */
////        xNetworkStatus = Plaintext_FreeRTOS_Disconnect( &xNetworkContext );
////        configASSERT( xNetworkStatus == PLAINTEXT_TRANSPORT_SUCCESS );
////
////        /* Wait for some time between two iterations to ensure that we do not
////         * bombard the MQTT broker. */
////        vTaskDelay( mqttexampleDELAY_BETWEEN_DEMO_ITERATIONS );
////    }
////}
