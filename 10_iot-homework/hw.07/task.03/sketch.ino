#include <Servo.h>

#define ECHO 2
#define TRIG 3
#define DELAY_ULTRASONIC 100

#define SERVO 5

Servo  servo_motor;
float distance_cmeters;
unsigned int timer_ut = 0;

void distanceUTtoServo() {  
  if (millis() - timer_ut >= DELAY_ULTRASONIC) {

    pinMode(TRIG, OUTPUT); // сброс Trig  
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG, HIGH); // установка TRIG на 10 мкс
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    pinMode(ECHO, INPUT); // измерение длительности ECHO
    distance_cmeters = (pulseIn(ECHO, HIGH) / 58.0);
    timer_ut = millis();
  }
  servo_motor.write(map(distance_cmeters, 0, 400, 180, 0));
  delay(15);
}

void setup() {
  servo_motor.attach(SERVO);
}

void loop() {
  distanceUTtoServo();
}