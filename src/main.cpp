#include"main.h"

/* Cahnge this based on your Wifi info */
const char* host = "evoke";                      // the name of the website for updationg ther firmware
const char* ssid = "EvokeMotorcycles_4G";       // the SSID of your router
const char* password = "EvokeEvoke";             // The password of your internet

// Replace with your network credentials
// const char* ssid = "nicolas";
// const char* password = "Jesuisde94.";

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
  // Assign each GPIO to a relay
int GPIOs[NUM_RELAYS] = {SWITCH1, SWITCH2, SWITCH3, SWITCH4};
  pinMode(LED_RED, OUTPUT);
// Set all relays to off when the program starts - if set to Normally Open (NO), the relay is off when you set the relay to HIGH
  for(int i=1; i<=NUM_RELAYS; i++){
    pinMode(GPIOs[i-1], OUTPUT);
    if(RELAY_NO){
      digitalWrite(GPIOs[i-1], HIGH);
    }
    else{
      digitalWrite(GPIOs[i-1], LOW);
    }
  }
  BLE_Init();
  delay(500);
 // Create BLE task pinned to core 0
xTaskCreatePinnedToCore(taskCode_BLE, "BLETask", 3000, NULL, 2, NULL, 0);
  // Create FreeRTOS tasks
//xTaskCreatePinnedToCore(modbusTask, "ModbusTask", 3000, NULL, 1, NULL, 1);
xTaskCreatePinnedToCore(taskCode_Dash, "taskCode_Dash", 3000, NULL, 1, NULL, 1);
//xTaskCreatePinnedToCore(WebServerTask, "WebServerTask", 2000, NULL, 1, NULL, 0);

}

void loop() {
  // loop() can remain empty as the task handles the functionality
}
