
#include"OpenCV_task.h"

void OpenCV(void *pvParameters){
    // Define the LED pins
    const int SW[] = {SWITCH1, SWITCH2, SWITCH3, SWITCH4}; // Pins where the LEDs are connected
    const int numSWs = NUM_RELAYS; // Number of LEDs


    char lastChar = '\0';  // Variable to store the last read character
    
    // Start serial communication
    Serial.setTimeout(1);
    while (true)
    {
    
        // Check if data is available on the serial port
        if (Serial.available() > 0) {

            // Read the incoming data
            uint8_t value = Serial.readString().toInt();
            
            // Ensure the value is within the range 0-5
            if (value >= 0 && value <= numSWs) 
            {
            // Turn ON the appropriate number of SW
                for (uint8_t i = 0; i < numSWs; i++) {
                    digitalWrite(SW[i], HIGH);
                }

                // Turn OFF the appropriate number of SW
                for (uint8_t i = 0; i < value; i++) {
                    digitalWrite(SW[i], LOW);
                }

            }
        }
    

            // Delay to prevent too frequent updates (optional)
            vTaskDelay(10/portTICK_PERIOD_MS);
            }
    }
    
