#include <ModbusRTUSlave.h>

#define PIN_LED LED_BUILTIN
#define PIN_TX 1
#define PIN_RE 8
#define PIN_DE 8
#define PIN_TE 8

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

u8  buffercoil[MODBUS_COIL_COUNT];
u16 bufferregister[MODBUS_HOREG_COUNT];

ModbusRTUSlave modbusrtuslave(MODBUS_SLAVE_ID, &Serial, PIN_TE);

void setup() {
  ::memset(buffercoil, 0x0, sizeof(u8) * MODBUS_COIL_COUNT);
  ::memset(bufferregister, 0x0, sizeof(u16) * MODBUS_HOREG_COUNT)

  // configure the LED
  pinMode(PIN_LED, OUTPUT);
  for(i = 0; i < 8; i++) {
    if(led) {
      led = 0;
      digitalWrite(PIN_LED, LOW);    
    } else {
      led = 255;
      digitalWrite(PIN_LED, HIGH);    
    }
    delay(250);
  }
  led = 0;
  digitalWrite(PIN_LED, LOW);

  Serial.begin(RS485_BAUD);
  modbusrtuslave.begin(RS485_BAUD);

  modbusrtuslave.addBitArea(MODBUS_COIL_START, buffercoil, MODBUS_COIL_COUNT);
  modbusrtuslave.   (MODBUS_HOREG_START, bufferregister, MODBUS_HOREG_COUNT);
}

void loop() {
  modbusrtuslave.process();
  // poll for Modbus RTU requests
  ModbusRTUServer.poll();
  holdregval = bufferregister[0];
  if(holdregval != last_analog_led) {
    led = holdregval;
    last_analog_led = holdregval;
    bufferregister[1] = holdregval;
  }
  // read the current value of the coil
  digital_led = getBit(buffercoil, 0);
  if(digital_led != last_digital_led) {
    led = digital_led == 1 ? 255 : 0;
    digital_led = digital_led;
  }
  if(led != last_led) {
    analogWrite(PIN_LED, led);
    last_led = led;
  }
}
