#include "Dash_Board.h"

bool ON  ;
bool ON1 ;
bool ON2 ;
bool ON3 ;
bool ON4 ;

AsyncWebServer server(80);
/* Instantiate or Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server); 

/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
Card temperature_C(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card temperature_F(&dashboard, TEMPERATURE_CARD, "Temperature", "°F");
Card button1(&dashboard, BUTTON_CARD, "Switch 1");
Card button2(&dashboard, BUTTON_CARD, "Switch 2");
Card button3(&dashboard, BUTTON_CARD, "Switch 3");
Card button4(&dashboard, BUTTON_CARD, "Switch 4");
Card status1(&dashboard, STATUS_CARD, ON==true? "Some OFF" : "All ON", "i");


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


void taskCode_Dash(void *pvParameters)
{
  /* Start AsyncWebServer */
    server.begin();
   

    /* Button card callback */
    button1.attachCallback([&](int value){
        Serial.println("Button1 Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button1.update(!value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH1, !value);
    });
    button2.attachCallback([&](int value){
        Serial.println("Button2 Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button2.update(!value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH2, !value);
    });
      button3.attachCallback([&](int value){
        Serial.println("Button3 Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button3.update(!value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH3, !value);
    });
    button4.attachCallback([&](int value){
        Serial.println("Button4 Triggered: "+String((value == 1)?"true":"false"));
        /* Button card updater - you need to update the button with latest value upon firing of callback */
        button4.update(!value);
        /* Send update to dashboard */
        dashboard.sendUpdates();
        digitalWrite(SWITCH4, !value);
    });

    while (true)
    {
      ((digitalRead(SWITCH1))==HIGH)? ON1=false : ON1 = true;
      ((digitalRead(SWITCH2))==HIGH)? ON2=false : ON2 = true;
      ((digitalRead(SWITCH3))==HIGH)? ON3=false : ON3 = true;
      ((digitalRead(SWITCH4))==HIGH)? ON4=false : ON4 = true;
 
      button1.update(bool(!(digitalRead(SWITCH1))));
      button2.update(bool(!(digitalRead(SWITCH2))));
      button3.update(bool(!(digitalRead(SWITCH3))));
      button4.update(bool(!(digitalRead(SWITCH4))));
      digitalWrite(LED_RED, !digitalRead(LED_RED));

      // Change the message status if all relay are ON (from iddle to success)
      if (ON1&&ON2&&ON3&&ON4)
      {
        ON =false;
        status1.update("message", "s");
      }
      else
      {
        ON = true;
        status1.update("message", "i");
      }
      
      

      /* Send Updates to our Dashboard (realtime) */
      dashboard.sendUpdates();
      // Put the task to sleep
     vTaskDelay(500 / portTICK_PERIOD_MS);  
    }
}

/* 
* This task handles the reading an updating of the Dallas temperature probe
*
 */

void taskCode_Dallastemp(void *pvParameters)
{
   sensors.begin();

   while (true) 
   {
     
       // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
        sensors.requestTemperatures(); 
        temperature_C.update((float)sensors.getTempCByIndex(0));
        temperature_F.update((float)sensors.getTempFByIndex(0));
        vTaskDelay(500 / portTICK_PERIOD_MS); 
   }
   
  

}