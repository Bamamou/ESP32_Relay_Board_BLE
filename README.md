# ESP32_Relay_Board_BLE
 This is a simple Dev Board for ESP32 Relay with RS485, BLE, OTA, UART, I2C, WiFi, BT Classic, ADC, four 10A relays etc... <br>
 The below schematic drawing is for the four 10A realys that are been controlled by the ESP32 on the same board
 ![image](https://github.com/user-attachments/assets/dc2e0ae3-1aca-4fa4-bcf6-546e6f7ec1be)
 The drwain of the ESP32 chip and the power supply including the RS485 Chip are on this page. <br>
 The power suply has both the USB Type C 5V power supply and the regular 9V power supply. <br>
 The board also has 4 general purpose IO that can be used as input or output for sensors.
 ![image](https://github.com/user-attachments/assets/31fe9561-9f4f-489f-ac1b-4b7d6bdbcb99) <br>
 Below is the 3D of the baord for more informaton on it.<br>
 
 ![ESP32 Relay](https://github.com/user-attachments/assets/2c08da4c-4c60-4d89-b729-26cb1e177436)

You can also use the 9V PS (power supply).<br>

![ESP32 relay board](https://github.com/user-attachments/assets/f78504fc-087c-4369-b0f4-7a717d52bf78)

As you can see the back traces are made specifically to handle up to 16A for home application which is suitable for IOT applications but remember the relays are rated for 10A.<br>
![ESP32 Relay board back](https://github.com/user-attachments/assets/d5f7bb2f-6727-4efb-a417-058adcae1032)

The project currently has four tasks 
## 1. BLE Task
This handle all the required actions for the BLE
## 2. RS485
This task handles all the required actions for the RS845 protcol.
## 3. Dash 
This task handles all the required actiona for the Dash online App management. This includes the widgets updates and the callback functions. <br>
This task handles also the reading and displaying of the Dallas temperature sensor using GPIO 12 of the ESP32.
![Dash](https://github.com/user-attachments/assets/43b1963b-fa53-468b-8323-5bcbb7077a2c)

![Dash all](https://github.com/user-attachments/assets/d4c7a6b5-68f3-45a2-8a98-734323509db9)
![Dash all On](https://github.com/user-attachments/assets/f369d27d-4e22-4b01-b34e-117faf96defe)


## 4. The WebServer UI
This task updates the state of each switch or relay on a WebServer UI according to the user's interaction with the UI and reflects the user's actions on the hardware level.
## 5.  OTA
The OTA task uses the Elegant OTA tasks to update the firmware over the air. <br>
The next one under development is the BLE OTA which I am excited to announce the release of a stability version.
