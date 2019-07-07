#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

#define PIN_TX 1
#define PIN_RE 2
#define PIN_DE 2
#define PIN_LED 3

#define RS485_BAUD  9600

#define MODBUS_SLAVE_ID 1

#define MODBUS_COIL_START 0x0400
#define MODBUS_COIL_COUNT 0x0008

//#define MODBUS_INREG_START 0x0400
//#define MODBUS_INREG_COUNT 0x0001

#define MODBUS_HOREG_START 0x0100
#define MODBUS_HOREG_COUNT 0x0004

int i;
uint16_t holdregval = 0;
u8 led = 0, last_led = 0, last_analog_led = 0;
bool digital_led = false, last_digital_led = false;

void ledflash();

void setup()
{
  // configure the LED
  pinMode(PIN_LED, OUTPUT);
  for(i = 0; i < 8; i++) {
    ledflash();
  }
  led = 0;
  digitalWrite(PIN_LED, LOW);

  RS485.setPins(PIN_TX, PIN_DE, PIN_RE);

  Serial.begin(RS485_BAUD);
  
  // start the Modbus RTU server, with (slave) id 1
  if (!ModbusRTUServer.begin(MODBUS_SLAVE_ID, RS485_BAUD)) {
    while (true) {
      ledflash();
    }
  }

  // configure a single coil at address 0x00
  ModbusRTUServer.configureCoils(MODBUS_COIL_START, MODBUS_COIL_COUNT);
  ModbusRTUServer.configureHoldingRegisters(MODBUS_HOREG_START, MODBUS_HOREG_COUNT);

  ModbusRTUServer.coilWrite(MODBUS_COIL_START, 0x0);
  ModbusRTUServer.coilWrite(MODBUS_COIL_START + 1, 0x0);
  ModbusRTUServer.holdingRegisterWrite(MODBUS_HOREG_START, 0x00);
  ModbusRTUServer.holdingRegisterWrite(MODBUS_HOREG_START + 1, 0x00);
}

void loop()
{
  // poll for Modbus RTU requests
  ModbusRTUServer.poll();
  holdregval = ModbusRTUServer.holdingRegisterRead(MODBUS_HOREG_START);
  if(holdregval != last_analog_led) {
    led = holdregval;
    last_analog_led = holdregval;
    ModbusRTUServer.holdingRegisterWrite(MODBUS_HOREG_START + 1, holdregval);
  }
  digital_led = ModbusRTUServer.coilRead(MODBUS_COIL_START);
  if(digital_led != last_digital_led) {
    led = digital_led ? 255 : 0;
    last_digital_led = digital_led;
    ModbusRTUServer.coilWrite(MODBUS_COIL_START + 1, digital_led);
  }
  if(led != last_led) {
    analogWrite(PIN_LED, led);
    last_led = led;
  }
}

void ledflash() {
  if(led) {
    led = 0;
    digitalWrite(PIN_LED, LOW);
  } else {
    led = 255;
    digitalWrite(PIN_LED, HIGH);
  }
  delay(250);
}
