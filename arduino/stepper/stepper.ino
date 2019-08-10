#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200

#define PIN_STBY 5
#define PIN_PWMA 10
#define PIN_PWMB 16

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 6, 7, 8, 9);


void setup()
{
  Serial.begin(9600);
  Serial.println("Stepper test!");
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(60);

  pinMode(PIN_STBY, OUTPUT);
  digitalWrite(PIN_STBY, LOW);

  pinMode(PIN_PWMA, OUTPUT);
  digitalWrite(PIN_PWMA, HIGH);
  pinMode(PIN_PWMB, OUTPUT);
  digitalWrite(PIN_PWMB, HIGH);

  fds::modbus::setup();
}

void loop()
{
  Serial.println("Forward");
  stepper.step(STEPS);
  Serial.println("Backward");
  stepper.step(-STEPS);
}