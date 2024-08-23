/******************************************************************************
 * main.h
 * Header for the BLE file
 *****************************************************************************/
#ifndef __BLE_H__
#define __BLE_H__

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include"global_Constants.h"

#define DESTINATION_ADDL 2
#define LORAMODE  0


#define DeviceName "WEMO_BLE"
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// Code for the task UpdateIO
void taskCode_BLE(void *pvParameters);

// Code for the BLE to init 
void BLE_Init(void);


#endif
