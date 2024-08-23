#include "Dash_Board.h"




AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server); 
/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
Card button1(&dashboard, BUTTON_CARD, "Switch 1");
Card button2(&dashboard, BUTTON_CARD, "Switch 2");
Card button3(&dashboard, BUTTON_CARD, "Switch 3");
Card button4(&dashboard, BUTTON_CARD, "Switch 4");





void taskCode_Dallastemp(void *pvParameters)
{
  /* Start AsyncWebServer */
     server.begin();
    /* Button card callback */
    button1.attachCallback([&](int value){
        Serial.println("Button Callback Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button1.update(value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH1, value);
    });
    button2.attachCallback([&](int value){
        Serial.println("Button Callback Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button2.update(value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH2, value);
    });
      button3.attachCallback([&](int value){
        Serial.println("Button Callback Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button3.update(value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH3, value);
    });
    button4.attachCallback([&](int value){
        Serial.println("Button Callback Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button4.update(value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH4, value);
    });

    while (true)
    {
 
      button1.update(bool(digitalRead(SWITCH1)));
      button2.update(bool(digitalRead(SWITCH2)));
      button3.update(bool(digitalRead(SWITCH3)));
      button4.update(bool(digitalRead(SWITCH4)));

      /* Send Updates to our Dashboard (realtime) */
      dashboard.sendUpdates();
      // Put the task to sleep
     vTaskDelay(500 / portTICK_PERIOD_MS);  
    }
}
