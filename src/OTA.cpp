
// #include "OTA.h"

// #if defined(ESP8266)
//   ESP8266WebServer server(80);
// #elif defined(ESP32)
//   WebServer server(80);
// #endif


// //==================================OTA Section ================================================//

// void OTA_TaskCode(void *pvParameters)
// {
//   server.on("/", []() 
//   {
//     server.send(200, "text/plain", "Hi! This is ElegantOTA Demo.");
//   });

//   ElegantOTA.begin(&server);    // Start ElegantOTA
//   server.begin();
//   Serial.println("HTTP server started");
//   // Set Authentication Credentials
//   ElegantOTA.setAuth("Wemo", "Jesuisde94.");

//   // Disable Auto Reboot
//   ElegantOTA.setAutoReboot(false);

//   while (true)
//   {
//     server.handleClient();
//     ElegantOTA.loop();
//     vTaskDelay(500/portTICK_PERIOD_MS);
//   }
  
// }