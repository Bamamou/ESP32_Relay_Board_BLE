#include <MODBUS.h>


ModbusRTU mb;
HardwareSerial mySerial1(1); // Setup Serial1

void modbusTask(void *pvParameters) {

  Serial.begin(115200, SERIAL_8N1);
  mySerial1.begin(115200, SERIAL_8N1, MBUS_RXD_PIN, MBUS_TXD_PIN);

#if defined(ESP32) || defined(ESP8266)
  mb.begin(&mySerial1, RXTX_PIN);
#else
  mb.begin(&Serial);
  mb.setBaudrate(115200);
#endif

  mb.slave(SLAVE_ID);
  mb.addHreg(REGN);
  mb.addHreg(REGN + 1);
  mb.addHreg(REGN + 2);
  mb.addHreg(REGN + 3);

  mb.Hreg(REGN, 0);
  mb.Hreg(REGN + 1, 0);
  mb.Hreg(REGN + 2, 0);
  mb.Hreg(REGN + 3, 0);

  while (true)
  {
    // Check and control the switches based on the Modbus register values
    digitalWrite(SWITCH1, mb.Hreg(REGN) == 0 ? HIGH : LOW);
    digitalWrite(SWITCH2, mb.Hreg(REGN + 1) == 0 ? HIGH : LOW);
    digitalWrite(SWITCH3, mb.Hreg(REGN + 2) == 0 ? HIGH : LOW);
    digitalWrite(SWITCH4, mb.Hreg(REGN + 3) == 0 ? HIGH : LOW);

    mb.task();
    vTaskDelay(10 / portTICK_PERIOD_MS);  // Delay to allow other tasks to run
  }

}