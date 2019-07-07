#include <ModbusSlave.h>

#define PIN_LED 3
#define PIN_TX 1
#define PIN_RE 2
#define PIN_DE 2
#define PIN_TE 2

#define RS485_BAUD  9600

#define MODBUS_SLAVE_ID 1

#define MODBUS_COIL_COUNT 0x0008
#define MODBUS_HOREG_COUNT 0x0004

Modbus slave(MODBUS_SLAVE_ID, PIN_TE);

int i;
uint8_t pin;
uint16_t holdregval = 0, addr, analog;
u8 led = 0, last_led = 0, last_analog_led = 0;
bool digital_led = false, last_digital_led = false, digital;

uint8_t coils;
uint16_t holding[MODBUS_HOREG_COUNT];

uint8_t readDigital(uint8_t fc, uint16_t address, uint16_t length);
uint8_t readDigitalIn(uint8_t fc, uint16_t address, uint16_t length);
uint8_t readAnalog(uint8_t fc, uint16_t address, uint16_t length);
uint8_t readAnalogIn(uint8_t fc, uint16_t address, uint16_t length);
uint8_t writeDigital(uint8_t fc, uint16_t address, uint16_t length);
uint8_t writeAnalog(uint8_t fc, uint16_t address, uint16_t length);

void ledflash();

void setup() {
  coils = 0x00;
  memset(holding, 0x00, sizeof(uint16_t) * MODBUS_HOREG_COUNT);

  // configure the LED
  pinMode(PIN_LED, OUTPUT);
  for(i = 0; i < 8; i++) {
    ledflash();
  }
  led = 0;
  digitalWrite(PIN_LED, LOW);

  // RS485 control pin must be output
  pinMode(PIN_TE, OUTPUT);

  slave.cbVector[CB_READ_COILS] = readDigital;                  // Coils are R/W digital
  slave.cbVector[CB_READ_DISCRETE_INPUTS] = readDigitalIn;       // Discrete are RO digital Inputs
  slave.cbVector[CB_READ_INPUT_REGISTERS] = readAnalogIn;       // Input Registry are RO analog Inputs
  slave.cbVector[CB_READ_HOLDING_REGISTERS] = readAnalog;       // Holding Registry are R/W analog registry
  slave.cbVector[CB_WRITE_COILS] = writeDigital;
  slave.cbVector[CB_WRITE_HOLDING_REGISTERS] = writeAnalog;

  Serial.begin(RS485_BAUD);
  slave.begin(RS485_BAUD);
}

void loop() {
  slave.poll();
  if(led != last_led) {
    analogWrite(PIN_LED, led);
    last_led = led;
  }
}

uint8_t readDigital(uint8_t fc, uint16_t address, uint16_t length) {
  uint8_t result = STATUS_OK;
  for (i = 0; i < length; i++) {
    addr = address + i;
    if(addr >= 0 && addr <= MODBUS_COIL_COUNT) {
      digital = bitRead(coils, addr);
      slave.writeCoilToBuffer(addr, digital);
    } else {
      result = STATUS_ILLEGAL_DATA_ADDRESS;
      break;
    }
  }
  return result;
}

/**
 * Handel Read Input Status (FC=02)
 * write back the values from digital in pins (input status).
 *
 * handler functions must return void and take:
 *      uint8_t  fc - function code
 *      uint16_t address - first register/coil address
 *      uint16_t length/status - length of data / coil status
 */
uint8_t readDigitalIn(uint8_t fc, uint16_t address, uint16_t length) {
    // read digital input
  uint8_t result = STATUS_OK;
  for (i = 0; i < length; i++) {
    addr = address + i;
    if(addr >= 0 && addr <= 13) {
      digital = digitalRead(addr);
      slave.writeDiscreteInputToBuffer(addr, digital);
    } else {
      result = STATUS_ILLEGAL_DATA_ADDRESS;
      break;
    }
  }
  return result;
}

uint8_t readAnalog(uint8_t fc, uint16_t address, uint16_t length) {
  // read holding registry
  uint8_t result = STATUS_OK;
  for (i = 0; i < length; i++) {
    addr = address + i;
    if(addr >= 0 && addr < MODBUS_HOREG_COUNT) {
      holdregval = holding[addr];
      slave.writeRegisterToBuffer(addr, holdregval);
    } else {
      result = STATUS_ILLEGAL_DATA_ADDRESS;
      break;
    }
  }
  return result;
}

/**
 * Handel Read Input Registers (FC=04)
 * write back the values from analog in pins (input registers).
 */
uint8_t readAnalogIn(uint8_t fc, uint16_t address, uint16_t length) {
  // read analog input
  uint8_t result = STATUS_OK;
  for (i = 0; i < length; i++) {
    addr = address + i;
    pin = A0 + addr;
    if(pin >= A0 && pin <= A5) {
      analog = analogRead(pin);
      slave.writeRegisterToBuffer(addr, analog);
    } else {
      result = STATUS_ILLEGAL_DATA_ADDRESS;
      break;
    }
  }
  return result;
}

/**
 * Handle Force Single Coil (FC=05) and Force Multiple Coils (FC=15)
 * set digital output pins (coils).
 */
uint8_t writeDigital(uint8_t fc, uint16_t address, uint16_t length) {
  uint8_t result = STATUS_OK;
  for (i = 0; i < length; i++) {
    addr = address + i;
    if(addr >= 0 && addr <= MODBUS_COIL_COUNT) {
      digital = slave.readCoilFromBuffer(addr);
      bitWrite(coils, addr, digital);
      switch(addr) {
      case 0:
        digital_led = digital;
        if(digital_led != last_digital_led) {
          led = digital_led ? 255 : 0;
          last_digital_led = digital_led;
        }
        break;
      }      
    } else {
      result = STATUS_ILLEGAL_DATA_ADDRESS;
      break;
    }
  }
  return result;
}

uint8_t writeAnalog(uint8_t fc, uint16_t address, uint16_t length) {
  uint8_t result = STATUS_OK;
  for (i = 0; i < length; i++) {
    addr = address + i;
    if(addr >= 0 && addr < MODBUS_HOREG_COUNT) {
      holdregval = slave.readRegisterFromBuffer(addr);
      holding[addr] = holdregval;
      switch(addr) {
      case 0:
        if(holdregval != last_analog_led && holdregval <= 255) {
          led = holdregval;
          last_analog_led = holdregval;
        }
        break;
      }
    } else {
      result = STATUS_ILLEGAL_DATA_ADDRESS;
      break;
    }
  }
  return result;
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
