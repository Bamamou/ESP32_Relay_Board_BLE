/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
*********/

#include "Task_DallasTemp.h"
AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server); 
/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
Card temperature_C(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card temperature_F(&dashboard, TEMPERATURE_CARD, "Temperature", "°F");
Card button(&dashboard, BUTTON_CARD, "LED Button");
Card sliderR(&dashboard, SLIDER_CARD, "R Slider", "", 0, 255, 1);
Card sliderG(&dashboard, SLIDER_CARD, "G Slider", "", 0, 255, 1);
Card sliderB(&dashboard, SLIDER_CARD, "B Slider", "", 0, 255, 1);
Card potentiometer(&dashboard, GENERIC_CARD, "Potentiometer");
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity", "%");
/* 
  Dashboard Charts
  Format - (Dashboard Instance, Chart Type, Chart Name )
*/
// Bar Chart Data
String XAxis[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int YAxis[] = {0, 0, 0, 0, 0, 0, 0};

// Bar Chart Instance
Chart power(&dashboard, BAR_CHART, "Power Usage (kWh)");
//Instantiate both the DHT sensor and the Display
//DHT dht(DHT_Pin, DHT11);  // Instantiate a dht element from the DHT object// Code for the task that takes care of classic Bluetooth
DHTesp dht;
Card DHTtemperature_C(&dashboard, TEMPERATURE_CARD, "DHT_Temperature", "°C");
Card DHTtemperature_F(&dashboard, TEMPERATURE_CARD, "DHT_Temperature", "°F");
Card DHTheatIdex(&dashboard, HUMIDITY_CARD, "DHT_Heat Index", "%");
Card DHTdewPoint(&dashboard, HUMIDITY_CARD, "DHT_dewPoint", "%");
Card DHTstatus(&dashboard, STATUS_CARD, "Comfort Status", "s");

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
ComfortState cf;  // The for the confort ratio computation

void taskCode_Dallastemp(void *pvParameters)
{
  /* Start AsyncWebServer */
  server.begin();
  sensors.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(12, INPUT);  // Potentiometer
  power.updateX(XAxis, 7);

    dht.setup(DHT_Pin, DHTesp::DHT11);
    /* Button card callback */
    button.attachCallback([&](int value){
      Serial.println("Button Callback Triggered: "+String((value == 1)?"true":"false"));
      /* Button card updater - you need to update the button with latest value upon firing of callback */
      button.update(value);
      /* Send update to dashboard */
      dashboard.sendUpdates();
      digitalWrite(LED_BUILTIN, value);
    });



    sliderR.attachCallback([&](float value){
      Serial.println("[Card1] Slider Callback Triggered: "+String(value));
      sliderR.update(value);
      analogWrite(23,value);
      dashboard.sendUpdates();
    });

    sliderG.attachCallback([&](float value){
      Serial.println("[Card1] Slider Callback Triggered: "+String(value));
      sliderG.update(value);
      analogWrite(19,value);
      dashboard.sendUpdates();
    });
    sliderB.attachCallback([&](float value){
      Serial.println("[Card1] Slider Callback Triggered: "+String(value));
      sliderB.update(value);
      analogWrite(18,value);
      dashboard.sendUpdates();
    });


    while (true)
    {
      // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
      sensors.requestTemperatures(); 
      


      temperature_C.update((float)sensors.getTempCByIndex(0));
      temperature_F.update((float)sensors.getTempFByIndex(0));
      potentiometer.update((float)random(0, 100));
      humidity.update((int)random(0, 5));
      button.update(bool(digitalRead(2)));

       TempAndHumidity newValues = dht.getTempAndHumidity();
        // Check if any reads failed and exit early (to try again).
        float heatIndex = dht.computeHeatIndex(newValues.temperature, newValues.humidity);
        float dewPoint = dht.computeDewPoint(newValues.temperature, newValues.humidity);
        float temp = newValues.temperature;
        float humid = newValues.humidity;
        float cr = dht.getComfortRatio(cf, newValues.temperature, newValues.humidity);

        String comfortStatus;
        switch(cf) {
          case Comfort_OK:
            comfortStatus = "Comfort_OK";
            break;
          case Comfort_TooHot:
            comfortStatus = "Comfort_TooHot";
            break;
          case Comfort_TooCold:
            comfortStatus = "Comfort_TooCold";
            break;
          case Comfort_TooDry:
            comfortStatus = "Comfort_TooDry";
            break;
          case Comfort_TooHumid:
            comfortStatus = "Comfort_TooHumid";
            break;
          case Comfort_HotAndHumid:
            comfortStatus = "Comfort_HotAndHumid";
            break;
          case Comfort_HotAndDry:
            comfortStatus = "Comfort_HotAndDry";
            break;
          case Comfort_ColdAndHumid:
            comfortStatus = "Comfort_ColdAndHumid";
            break;
          case Comfort_ColdAndDry:
            comfortStatus = "Comfort_ColdAndDry";
            break;
          default:
            comfortStatus = "Unknown:";
            break;
        };


        DHTtemperature_C.update(newValues.temperature);
        DHTheatIdex.update(newValues.humidity);
        DHTtemperature_F.update(heatIndex);
        DHTdewPoint.update(dewPoint);
        DHTstatus.update(comfortStatus);
      // Randomize YAxis Values ( for demonstration purposes only )
      for(int i=0; i < 7; i++){
        YAxis[i] = (int)random(0, 200);
      }

      /* Update Chart Y Axis (yaxis_array, array_size) */
      power.updateY(YAxis, 7);

      /* Send Updates to our Dashboard (realtime) */
      dashboard.sendUpdates();
  
      Serial.print("Celsius temperature: ");
      // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
      Serial.print(sensors.getTempCByIndex(0)); 
      Serial.print(" - Fahrenheit temperature: ");
      Serial.println(sensors.getTempFByIndex(0));
    
      // Put the task to sleep
     vTaskDelay(task_DallasTemp.getInterval() / portTICK_PERIOD_MS);  
    }
}
