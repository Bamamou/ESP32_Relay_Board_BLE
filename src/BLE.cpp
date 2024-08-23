#include"BLE.h"


BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
char BLEbuf[32] = {0};
uint32_t cnt = 0;

struct _BLE {
    char len;
    char bledata[100];
};
struct _BLE ble;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.print("------>Received Value: ");

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();

        if (rxValue.find("11") != -1) {
          Serial.print("Rx 11!");
          digitalWrite(SWITCH1, LOW);   
        }
        else if (rxValue.find("10") != -1) {
          Serial.print("Rx 10!");
          digitalWrite(SWITCH1, HIGH);   
        }
        if (rxValue.find("21") != -1) {
          Serial.print("Rx 21!");
          digitalWrite(SWITCH2, LOW);   
        }
        else if (rxValue.find("20") != -1) {
          Serial.print("Rx 20!");
          digitalWrite(SWITCH2, HIGH);   
        } 
         if (rxValue.find("31") != -1) {
          Serial.print("Rx 31!");
          digitalWrite(SWITCH3, LOW);   
        }
        else if (rxValue.find("30") != -1) {
          Serial.print("Rx 30!");
          digitalWrite(SWITCH3, HIGH);   
        } 
        if (rxValue.find("41") != -1) {
          Serial.print("Rx 41!");
          digitalWrite(SWITCH4, LOW);   
        }
        else if (rxValue.find("40") != -1) {
          Serial.print("Rx 40!");
          digitalWrite(SWITCH4, HIGH);   
        } 
        Serial.println();
      }
    }
};

void BLE_Init(void) {
  BLEDevice::init(DeviceName);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting for a client connection to notify...");
}

// Task that handles BLE operations
void taskCode_BLE(void *pvParameters) {
  while (1) {
    if (deviceConnected) {
      pCharacteristic->setValue(ble.bledata);
      pCharacteristic->notify(); 
      Serial.println("ble Connected OK");
      digitalWrite(LED_RED, HIGH);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      digitalWrite(LED_RED, LOW);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    } else {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
}
