#include <MODBUS.h>


ModbusRTU mb;
HardwareSerial mySerial1(1); // Setup Serial1





void modbusTask(void *pvParameters) {

    Serial.begin(115200, SERIAL_8N1);
    mySerial1.begin(115200, SERIAL_8N1, MBUS_RXD_PIN, MBUS_TXD_PIN); // RX1 18 TX1 19

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

    while (1) {
        mb.task();
        vTaskDelay(1 / portTICK_PERIOD_MS); // Give some delay for the task scheduling
    }
}

void switchControlTask(void *pvParameters) {
  while (1) {
    if (mb.Hreg(REGN) == 0)
      digitalWrite(SWITCH1, HIGH);
    else if (mb.Hreg(REGN) == 1)
      digitalWrite(SWITCH1, LOW);

    if (mb.Hreg(REGN + 1) == 0)
      digitalWrite(SWITCH1, HIGH);
    else if (mb.Hreg(REGN + 1) == 1)
      digitalWrite(SWITCH1, LOW);

    if (mb.Hreg(REGN + 2) == 0)
      digitalWrite(SWITCH2, HIGH);
    else if (mb.Hreg(REGN + 2) == 1)
      digitalWrite(SWITCH2, LOW);

    if (mb.Hreg(REGN + 3) == 0)
      digitalWrite(SWITCH3, HIGH);
    else if (mb.Hreg(REGN + 3) == 1)
      digitalWrite(SWITCH3, LOW);

    vTaskDelay(10 / portTICK_PERIOD_MS); // Control the switches every 10ms
  }
}

