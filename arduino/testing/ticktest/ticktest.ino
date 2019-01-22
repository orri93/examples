#define BAUD_RATE 19200

#define PIN_LED LED_BUILTIN

#define INTERVAL_LED     100
#define INTERVAL_A      1100
#define INTERVAL_B      2010

byte value = HIGH;

unsigned long long tick, nextled = 0, nexta = 0, nextb = 0;

int tickdown;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(BAUD_RATE);
  Serial.println("\n");
  Serial.print("Starting ticktest with LED blink interval (high/low) as ");
  Serial.print(INTERVAL_LED, DEC);
  Serial.print(" milliseconds and two serial intervals of ");
  Serial.print(INTERVAL_A, DEC);
  Serial.print(" milliseconds and ");
  Serial.print(INTERVAL_B, DEC);
  Serial.print(" milliseconds");
  Serial.println("\n");
}

// the loop function runs over and over again forever
void loop() {
  tick = millis();
  tickdown = (int)tick;

  if(tick >= nextled) {
    nextled = tick + INTERVAL_LED;
    digitalWrite(PIN_LED, value);
    value = value == HIGH ? LOW : HIGH;  
  }

  if(tick >= nexta) {
    nexta = tick + INTERVAL_A;
    Serial.print("Tick A: ");
    Serial.println(tickdown, DEC);
  }

  if(tick >= nextb) {
    nextb = tick + INTERVAL_B;
    Serial.print("Tick B: ");
    Serial.println(tickdown, DEC);
  }
}