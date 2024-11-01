
#include"OpenCV_task.h"

void OpenCV(void *pvParameters){
    // Define the LED pins
    const int ledPins[] = {2, 3, 4, 5, 6}; // Pins where the LEDs are connected
    const int numLeds = 5; // Number of LEDs


    char lastChar = '\0';  // Variable to store the last read character
      // Initialize the LED pins as outputs
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW); // Ensure all LEDs are off initially
    }
    
    // Start serial communication
    Serial.begin(115200);
    Serial.setTimeout(1);
    while (true)
    {
    
        // Check if data is available on the serial port
        if (Serial.available() > 0) {

            // Read the incoming data
            int value = Serial.readString().toInt();
            
            // Ensure the value is within the range 0-5
            if (value >= 0 && value <= numLeds) {
            // Turn off all LEDs first
            for (int i = 0; i < numLeds; i++) {
                digitalWrite(ledPins[i], LOW);
            }

            // Turn on the appropriate number of LEDs
            for (int i = 0; i < value; i++) {
                digitalWrite(ledPins[i], HIGH);
            }

            }
        }
    

            // Delay to prevent too frequent updates (optional)
            vTaskDelay(10/portTICK_PERIOD_MS);
            }
    }
    
