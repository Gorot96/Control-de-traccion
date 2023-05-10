/*
 * web_server.c
 *
 *  Created on: 10 mar. 2023
 *      Author: Raul Duran
 */

#include <unistd.h>
#include "main.h"
#include "es_wifi.h"
#include "wifi.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "Tareas.h"

/* Update SSID and PASSWORD with own Access point settings */
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


static  char http[1024];
static  uint8_t  IP_Addr[4];


// Prototipos
int wifi_server(void);

static  WIFI_Status_t SendWebPage(void);
static  int wifi_start(void);
static  int wifi_connect(void);
static  bool WebServerProcess(void);

struct CT_Sensores_t sensorArray[10];
uint8_t arraySize = 10;

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

  // Running HTML Server test
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
        // Waiting connection

    }

    LOG(("Client connected %d.%d.%d.%d:%d\r\n",RemoteIP[0],RemoteIP[1],RemoteIP[2],RemoteIP[3],RemotePort));

    StopServer=WebServerProcess();

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

  LOG(("Server is stop\r\n"));
  return 0;
}


static bool WebServerProcess(void)
{
  uint16_t  respLen;
  static   uint8_t resp[1024];
  bool    stopserver=false;

  if (WIFI_STATUS_OK == WIFI_ReceiveData(SOCKET, resp, 1000, &respLen, WIFI_READ_TIMEOUT))
  {
   // get bytes from server

   if( respLen > 0)
   {
      if(strstr((char *)resp, "GET")) /* GET: put web page */
      {
		GetSensores(sensorArray, arraySize);
        if(SendWebPage() != WIFI_STATUS_OK)
        {
          LOG(("> ERROR : Cannot send web page\r\n"));
        }
        else
        {
          //Send page after  GET command
        }
       }
       else if(strstr((char *)resp, "POST"))/* POST: received info */
       {
         // Post request

         if(strstr((char *)resp, "stop_server"))
         {
           if(strstr((char *)resp, "stop_server=0"))
           {
             stopserver = false;
           }
           else if(strstr((char *)resp, "stop_server=1"))
           {
             stopserver = true;
           }
         }
         GetSensores(sensorArray, arraySize);
         if(SendWebPage() != WIFI_STATUS_OK)
         {
           LOG(("> ERROR : Cannot send web page\r\n"));
         }
         else
         {
           // Send Page after POST command
         }
       }
     }
  }
  else
  {
    LOG(("Client close connection\r\n"));
  }
  return stopserver;

 }

/**
  * @brief  Send HTML page
  * @param  None
  * @retval None
  */
static WIFI_Status_t SendWebPage(void)
{
  uint16_t SentDataLength;
  WIFI_Status_t ret;
  uint8_t k;

  sprintf(http, "0");

  /* construct web page content */
  for (k = 0; k < arraySize; k++) {
	  struct CT_Sensores_t sensors = sensorArray[k];
	  char newjson[256];

	  sprintf(newjson, "###{\"IMU1accelX\": %d, \"IMU1accelY\": %d, \"IMU1accelZ\": %d, \"IMU2accelX\": %d, "
			  "\"IMU2accelY\": %d, \"IMU2accelZ\": %d}",
			(int) sensors.IMU1accelX, (int) sensors.IMU1accelY, (int) sensors.IMU1accelZ, (int) sensors.IMU2accelX,
			(int) sensors.IMU2accelY, (int) sensors.IMU2accelZ);

	  strcat(http, newjson);
  }

  ret = WIFI_SendData(0, (uint8_t *)http, strlen((char *)http), &SentDataLength, WIFI_WRITE_TIMEOUT);

  if((ret == WIFI_STATUS_OK) && (SentDataLength != strlen((char *)http)))
  {
    ret = WIFI_STATUS_ERROR;
  }

  return ret;
}


//*************************************************************************//

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
