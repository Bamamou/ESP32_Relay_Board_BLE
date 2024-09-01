/******************************************************************************
 * main.h
 * Header for the DashBoard file
 *****************************************************************************/
#ifndef __GLOBAL_CONSTANS_H__
#define __GLOBAL_CONSTANS_H__

#include"global_Constants.h"
#include<Arduino.h>
#if defined(ESP8266)
  /* ESP8266 Dependencies */
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(ESP32)
  /* ESP32 Dependencies */
  //#include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif
#include <ESPDash.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 12


void taskCode_Dash(void *pvParameters);

void taskCode_Dallastemp(void *pvParameters);


#endif
