/*
 Name:		ModbusRtuSlaveUno1.ino
 Created:	7/14/2019 4:02:14 AM
 Author:	SigurdssonGO
*/

#include <ModbusSlave.h>

#define PIN_SS_ETHERNET               10
#define PIN_SS_SD                      4

#define PIN_RS485_MODBUS_TE            2

#define PIN_COIL_OUTPUT_1              3

#define PIN_DISCRETE_INPUT_1           7
#define PIN_DISCRETE_INPUT_2           8

#define PIN_INPUT_REGISTRY_1          A0
#define PIN_INPUT_REGISTRY_2          A1

#define PIN_HOLDING_REGISTRY_OUTPUT_1  5
#define PIN_HOLDING_REGISTRY_OUTPUT_2  6

#define MODBUS_SLAVE_ID               11
#define RS485_BAUD                  9600

#define DELAY_SETUP_COMPLETED         10

enum Coil {
  Coil1 = 0x0000,
  Coil2 = 0x0001,
};

enum DiscreteInput {
  DiscreteInput1 = 0x0000,
  DiscreteInput2 = 0x0001
};

enum HoldingRegistry {
  HoldingRegistry1 = 0x0000,
  HoldingRegistry2 = 0x0001
};

enum InputRegistry {
  InputRegistry1 = 0x0000,
  InputRegistry2 = 0x0001
};

bool coil1 = false, coil2;
uint16_t address, holdingregistry1, holdingregistry2;

Modbus slave(MODBUS_SLAVE_ID, PIN_RS485_MODBUS_TE);

#ifdef PIN_COIL_OUTPUT_1
#include <arduinosinled.h>
fds::SinLed sinledcoil1(PIN_COIL_OUTPUT_1);
#endif

#ifdef PIN_HOLDING_REGISTRY_OUTPUT_1
#include <arduinosinled.h>
fds::SinLed sinled1(PIN_HOLDING_REGISTRY_OUTPUT_1);
#endif
#ifdef PIN_HOLDING_REGISTRY_OUTPUT_2
#include <arduinosinled.h>
fds::SinLed sinled2(PIN_HOLDING_REGISTRY_OUTPUT_2);
#endif

/* 0x01 Read Coils */
uint8_t read_coils(uint8_t fc, uint16_t startaddress, uint16_t length) {
  for (address = startaddress; address < startaddress + length; address++) {
    switch (address) {
    case Coil1:
      slave.writeCoilToBuffer(address, coil1);
      break;
    case Coil2:
      slave.writeCoilToBuffer(address, coil2);
      break;
    default:
      return STATUS_ILLEGAL_DATA_ADDRESS;
    }
  }
  return STATUS_OK;
}

/* 0x02 Read Discrete Inputs */
uint8_t read_discrete_inputs(uint8_t fc, uint16_t startaddress, uint16_t length) {
  for (address = startaddress; address < startaddress + length; address++) {
    switch (address) {
    case DiscreteInput1:
      slave.writeDiscreteInputToBuffer(address, digitalRead(PIN_DISCRETE_INPUT_1));
      break;
    case DiscreteInput2:
      slave.writeDiscreteInputToBuffer(address, digitalRead(PIN_DISCRETE_INPUT_2));
      break;
    default:
      return STATUS_ILLEGAL_DATA_ADDRESS;
    }
  }
  return STATUS_OK;
}

/* 0x03 Read Multiple Holding Registers */
uint8_t read_holding_registers(uint8_t fc, uint16_t startaddress, uint16_t length) {
  for (address = startaddress; address < startaddress + length; address++) {
    switch (address) {
    case HoldingRegistry1:
      slave.writeRegisterToBuffer(address, holdingregistry1);
      break;
    case HoldingRegistry2:
      slave.writeRegisterToBuffer(address, holdingregistry2);
      break;
    default:
      return STATUS_ILLEGAL_DATA_ADDRESS;
    }
  }
  return STATUS_OK;
}

/* 0x04 Read Input Registers */
uint8_t read_input_registers(uint8_t fc, uint16_t startaddress, uint16_t length) {
  for (address = startaddress; address < startaddress + length; address++) {
    switch (address) {
    case InputRegistry1:
      slave.writeRegisterToBuffer(address, analogRead(PIN_DISCRETE_INPUT_1));
      break;
    case InputRegistry2:
      slave.writeRegisterToBuffer(address, analogRead(PIN_DISCRETE_INPUT_2));
      break;
    default:
      return STATUS_ILLEGAL_DATA_ADDRESS;
    }
  }
  return STATUS_OK;
}

/* 0x05 Write Single Coil and 0x0f Write Multiple Coils */
uint8_t write_coils(uint8_t fc, uint16_t startaddress, uint16_t length) {
  for (address = startaddress; address < startaddress + length; address++) {
    switch (address) {
    case Coil1:
      coil1 = slave.readCoilFromBuffer(address);
#ifdef PIN_COIL_OUTPUT_1
      if (coil1) {
        sinledcoil1.setat(0.0F);
      } else {
        digitalWrite(PIN_COIL_OUTPUT_1, LOW);
      }
#endif
      break;
    case Coil2:
      coil2 = slave.readCoilFromBuffer(address);
#ifdef PIN_COIL_OUTPUT_2
      digitalWrite(PIN_COIL_OUTPUT_2, coil2 ? HIGH : LOW);
#endif

      break;
    default:
      return STATUS_ILLEGAL_DATA_ADDRESS;
    }
  }
  return STATUS_OK;
}

/* 0x06 Write Single Holding Register and 0x10 Write Multiple Holding Registers */
uint8_t write_holding_registers(uint8_t fc, uint16_t startaddress, uint16_t length) {
  for (address = startaddress; address < startaddress + length; address++) {
    switch (address) {
    case HoldingRegistry1:
      holdingregistry1 = slave.readRegisterFromBuffer(address);
#ifdef PIN_HOLDING_REGISTRY_OUTPUT_1
      if (holdingregistry1 >= 0 && holdingregistry1 <= 255) {
        analogWrite(PIN_HOLDING_REGISTRY_OUTPUT_1, holdingregistry1);
      }
      else {
        return STATUS_ILLEGAL_DATA_VALUE;
      }
#endif
      break;
    case HoldingRegistry2:
      holdingregistry2 = slave.readRegisterFromBuffer(address);
#ifdef PIN_HOLDING_REGISTRY_OUTPUT_2
      if (holdingregistry2 >= 0 && holdingregistry2 <= 255) {
        analogWrite(PIN_HOLDING_REGISTRY_OUTPUT_2, holdingregistry2);
      }
      else {
        return STATUS_ILLEGAL_DATA_VALUE;
      }
#endif
      break;
    default:
      return STATUS_ILLEGAL_DATA_ADDRESS;
    }
  }
  return STATUS_OK;
}

// the setup function runs once when you press reset or power the board
void setup() {
#ifdef PIN_COIL_OUTPUT_1
  pinMode(PIN_COIL_OUTPUT_1, OUTPUT);
#endif
#ifdef PIN_COIL_OUTPUT_2
  pinMode(PIN_COIL_OUTPUT_2, OUTPUT);
#endif
  pinMode(PIN_DISCRETE_INPUT_1, INPUT_PULLUP);
  pinMode(PIN_DISCRETE_INPUT_2, INPUT_PULLUP);
  pinMode(PIN_INPUT_REGISTRY_1, INPUT);
  //pinMode(PIN_INPUT_REGISTRY_2, INPUT);
#ifdef PIN_COIL_OUTPUT_1
  sinledcoil1.initialize();
  sinledcoil1.fullcycle(3);
#endif
#ifdef PIN_HOLDING_REGISTRY_OUTPUT_1
  sinled1.initialize();
#endif
#ifdef PIN_HOLDING_REGISTRY_OUTPUT_2
  sinled2.initialize(1);
#endif

  // RS485 control pin must be output
  pinMode(PIN_RS485_MODBUS_TE, OUTPUT);

  slave.cbVector[CB_READ_COILS] = read_coils;                             // Coils are R/W digital
  slave.cbVector[CB_READ_DISCRETE_INPUTS] = read_discrete_inputs;         // Discrete are RO digital Inputs
  slave.cbVector[CB_READ_INPUT_REGISTERS] = read_input_registers;         // Input Registry are RO analog Inputs
  slave.cbVector[CB_READ_HOLDING_REGISTERS] = read_holding_registers;     // Holding Registry are R/W analog registry
  slave.cbVector[CB_WRITE_COILS] = write_coils;
  slave.cbVector[CB_WRITE_HOLDING_REGISTERS] = write_holding_registers;

  Serial.begin(RS485_BAUD);
  slave.begin(RS485_BAUD);

#ifdef DELAY_SETUP_COMPLETED
  delay(DELAY_SETUP_COMPLETED);
#endif
}

// the loop function runs over and over again until power down or reset
void loop() {
  slave.poll();
  if (coil1) {
    sinledcoil1.cycle();
  }
}
