#include <Stepper.h>

#define POTMET  A5
#define LED     13
#define START   11
#define RIGHT   9
#define LEFT    8

const int stepsPerRevolution = 200;
Stepper explStepper(stepsPerRevolution, 4, 5, 6, 7);

bool isActive = false;
int step_dir = 1;

int lastStartButton = LOW;
int currStartButton = HIGH;

int lastRightButton = LOW;
int currRightButton = HIGH;

int lastLeftButton = LOW;
int currLeftButton = HIGH;


int debounce (int button, int last)  {
  int current = digitalRead(button);
  if(last != current) {
    delay(10);
    current = digitalRead(button);
  }
  return current;
}

void StartButton()
{
  // currStartButton = digitalRead(START);
  currStartButton = debounce(START, lastStartButton);
  if (lastStartButton == HIGH && currStartButton == LOW)
  {
    isActive = !isActive;
    delay(10);
  }
  lastStartButton = currStartButton;
}

void RightButton()
{
  // currRightButton = digitalRead(RIGHT);
  currRightButton = debounce(RIGHT, lastRightButton);
  if (lastRightButton == HIGH && currRightButton == LOW)
  {
    step_dir = 1;
    delay(10);
  }
  lastRightButton = currRightButton;
}

void LeftButton()
{
  // currLeftButton = digitalRead(LEFT);
  currLeftButton = debounce(LEFT, lastLeftButton);
  if (lastLeftButton == HIGH && currLeftButton == LOW)
  {
    step_dir = -1;
    delay(10);
  }
  lastLeftButton = currLeftButton;
}



void setup() {
  // Serial.begin(9600); //for debug purpose

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(START, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(POTMET, INPUT);

}

void loop() {
  StartButton();
  RightButton();
  LeftButton();

  int speed = analogRead(POTMET);
  // Serial.println(speed);
  int motor_speed = map(speed, 0, 1023, 0, 100);

  if (motor_speed > 0 && isActive)
  {
    explStepper.setSpeed(motor_speed); 
    explStepper.step(step_dir * stepsPerRevolution / 100);
  }

}