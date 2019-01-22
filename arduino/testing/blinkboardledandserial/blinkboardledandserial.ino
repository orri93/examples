#define BAUD_RATE 9600

#define PIN_LED_1 LED_BUILTIN
#define PIN_LED_2 6

#define INTERVAL_LED     200
#define INTERVAL_SERIAL 1100

byte value = HIGH;

unsigned long long tick, nextled = 0, nextserial = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
#ifdef PIN_LED_1
  pinMode(PIN_LED_1, OUTPUT);
  digitalWrite(PIN_LED_1, LOW);
#endif
#ifdef PIN_LED_2
  pinMode(PIN_LED_2, OUTPUT);
  digitalWrite(PIN_LED_2, LOW);
#endif
  Serial.begin(BAUD_RATE);
  Serial.println("\n");
  Serial.print("Starting blinking LED test with LED blink interval (high/low) as ");
  Serial.print(INTERVAL_LED, DEC);
  Serial.print(" milliseconds and serial output 1 for high and 0 for low on ");
  Serial.print(INTERVAL_SERIAL, DEC);
  Serial.print(" milliseconds interval");
  Serial.println("\n");
}

// the loop function runs over and over again forever
void loop() {
  tick = millis();

  if (tick >= nextled) {
    nextled = tick + INTERVAL_LED;
#ifdef PIN_LED_1
    digitalWrite(PIN_LED_1, value);
#endif
#ifdef PIN_LED_2
    digitalWrite(PIN_LED_2, value);
#endif
    value = value == HIGH ? LOW : HIGH;
  }

  if (tick >= nextserial) {
    nextserial = tick + INTERVAL_SERIAL;
    if (value == HIGH) {
      Serial.print(1, DEC);
    } else {
      Serial.print(0, DEC);
    }
  }
}
