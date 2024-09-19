#define BLUE 11
#define GREEN 12
#define RED 13

void RedLight (int _delay) {
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  delay(_delay);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  delay(_delay);
}

void BlueLight (int _delay) {
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  delay(_delay);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  delay(_delay);
}

void GreenLight (int _delay) {
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
  delay(_delay);
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
  delay(_delay);
}

void setup()
{
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
}
void loop()
{
  int freq = 500;
  RedLight(freq);
  BlueLight(freq);
  GreenLight(freq);
}
