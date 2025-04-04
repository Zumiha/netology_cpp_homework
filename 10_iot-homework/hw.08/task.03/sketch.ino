//hw.08.02
#include <TimerOne.h>

#define ACTION 2
#define LED 13

#define DOT 200000
#define DASH 600000

volatile bool isRunning = false;
int ledState = LOW; //состояние светодиода
volatile unsigned long blinkCount = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ACTION, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  attachInterrupt(0, pressButton, RISING); //разрешение внешнего прерывания (вывод 2 Arduino UNO)
  Timer1.initialize();
  Timer1.attachInterrupt(blinkSOS);
}

void loop()
{

}

//Функция обработки внешнего прерывания
void pressButton()
{
  if (!isRunning) {
    isRunning = true;
  }
}

void blinkSOS(void)
{
  if (isRunning) {  
    if (ledState == LOW)
    {
      ledState = HIGH;
      blinkCount++; //количество миганий
    } else {
      ledState = LOW;
    }
    if (blinkCount > 9) {
      ledState = LOW;
      blinkCount = 0;
      isRunning = false;
    } 
    else if (blinkCount > 6) {Timer1.setPeriod(DOT);} 
    else if (blinkCount > 3) {Timer1.setPeriod(DASH);} 
    else {Timer1.setPeriod(DOT);}
    digitalWrite(LED, ledState);    
  }
}
