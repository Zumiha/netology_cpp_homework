#define BLUE 11
#define GREEN 12
#define RED 13
#define BUTTON 2

int lastButton = LOW;
int curButton = LOW;
int ledOn = LOW;
int light_num = BLUE;

int debounce (int last)  {
  int current = digitalRead(BUTTON);
  if(last != current) {
    delay(10);
    current = digitalRead(BUTTON);
  }
  return current;
}

void turnOff() {
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

void LightCycle(int state) {
  switch(state) {
    case 0:
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      break;
    case 1:
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);
      break;
    case 2: 
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, LOW);
      break;
    default:
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, HIGH);
  }
}

void setup()
{
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);

  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);

}

int state = 0;

void loop() {
  curButton = debounce (lastButton);
  if(lastButton == HIGH && curButton == LOW)  {
    LightCycle(state);
    state++;
  }

  lastButton = curButton;
  if (state > 3) state = 0;

}
