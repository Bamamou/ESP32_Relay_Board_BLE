/******************************************************************************
 * main.h
 * Header for the MODBUS file
 *****************************************************************************/
#ifndef __MODBUS_H__
#define __MODBUS_H__

#include <Arduino.h>
#include <ModbusRTU.h>
#include <HardwareSerial.h>
#include"global_Constants.h"

#define REGN 10 // Register address
#define SLAVE_ID 1 // Slave ID
#define RXTX_PIN  32 // RS485 direction control pin
//#define MBUS_HW_SERIAL Serial1
#define MBUS_TXD_PIN   19        
#define MBUS_RXD_PIN   18

void modbusTask(void *pvParameters);



#endif