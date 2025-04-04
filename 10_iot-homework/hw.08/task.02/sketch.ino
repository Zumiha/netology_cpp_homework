//hw.08.02
#define POWER 2
#define DIR 3

#define DIRPIN 8
#define STEPPIN 9
int steps_per_revolution; //количество шагов на один оборот
int delay_step;

volatile bool isRunning = false;
volatile bool direction = true;

void setup()
{
  pinMode(POWER, INPUT_PULLUP); 
  pinMode(DIR, INPUT_PULLUP); 
  pinMode(STEPPIN, OUTPUT);
  pinMode(DIRPIN, OUTPUT);
  attachInterrupt(0, stepPower, RISING); //разрешение внешнего прерывания (вывод 2 Arduino UNO)
  attachInterrupt(1, stepDirection, RISING); //разрешение внешнего прерывания (вывод 3 Arduino UNO)
  steps_per_revolution = 200;
  delay_step = 5000;
}
void loop()
{
  if(isRunning) stepperWork();
}

void stepperWork() {
  digitalWrite(DIRPIN, direction); //установка направления
  digitalWrite(STEPPIN, HIGH);
  delayMicroseconds(delay_step);
  digitalWrite(STEPPIN, LOW);
  delayMicroseconds(delay_step);
}

//Функция обработки внешнего прерывания
void stepPower()
{
 isRunning = !isRunning;
}

void stepDirection()
{
 direction = !direction;
}