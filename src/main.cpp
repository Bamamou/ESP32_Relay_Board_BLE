#include"main.h"

/* Cahnge this based on your Wifi info */
const char* host = "evoke";                      // the name of the website for updationg ther firmware
const char* ssid = "EvokeMotorcycles_4G";       // the SSID of your router
const char* password = "EvokeEvoke";             // The password of your internet

void setup() {
  Serial.begin(115200);
  /* Connect WiFi */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  pinMode(LED_RED, OUTPUT);
  BLE_Init();
  delay(500);
  pinMode(SWITCH1, OUTPUT);
  pinMode(SWITCH2, OUTPUT);
  pinMode(SWITCH3, OUTPUT);
  pinMode(SWITCH4, OUTPUT);
  digitalWrite(SWITCH1, HIGH); 
  digitalWrite(SWITCH2, HIGH); 
  digitalWrite(SWITCH3, HIGH); 
  digitalWrite(SWITCH4, HIGH); 

  // Create BLE task pinned to core 0
  xTaskCreatePinnedToCore(
    taskCode_BLE,          // Task function
    "BLETask",        // Task name
    3000,            // Stack size
    NULL,             // Task input parameter
    1,                // Task priority
    NULL,             // Task handle
    0                 // Core where the task should run (0 = core 0)
  );

  // Create FreeRTOS tasks
//xTaskCreatePinnedToCore(modbusTask, "ModbusTask", 3000, NULL, 1, NULL, 1);
//xTaskCreatePinnedToCore(switchControlTask, "SwitchControlTask", 3000, NULL, 1, NULL, 1);
xTaskCreatePinnedToCore(taskCode_Dallastemp, "taskCode_Dallastemp", 3000, NULL, 1, NULL, 0);

}

void loop() {
  // loop() can remain empty as the task handles the functionality
}
