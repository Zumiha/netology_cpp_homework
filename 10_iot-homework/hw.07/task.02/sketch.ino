#include "Driver.h"

#define DIRPIN 2
#define STEPPIN 3

StepDriver testStepper (STEPPIN, DIRPIN);

void setup() {
  // Serial.begin(9600); //for debug purpose
  pinMode(STEPPIN, OUTPUT); //выводы как выходы
  pinMode(DIRPIN, OUTPUT);
}

void loop()
{
  delay(1000); // ожидание секунды
  testStepper.setSpeed(5000);
  testStepper.step(200);
  delay(1000); // ожидание секунды
  testStepper.setSpeed(2000);
  testStepper.step(-200);
}