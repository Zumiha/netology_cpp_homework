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
  int freq = 1000;
  // RedLight(freq);
  // BlueLight(freq);
  // GreenLight(freq);

  //yellow light
  delay(freq);
  digitalWrite(BLUE, HIGH);
  delay(freq);
  digitalWrite(BLUE, LOW);
  delay(freq);

  //purple light
  digitalWrite(GREEN, HIGH);
  delay(freq);
  digitalWrite(GREEN, LOW);
  delay(freq);

  //cyan light
  digitalWrite(RED, HIGH);
  delay(freq);
  digitalWrite(RED, LOW);
  delay(freq);

  //red light
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  delay(freq);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  delay(freq);  

  //blue ligth
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);
  delay(freq);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  delay(freq);

  //green light
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
  delay(freq);
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
  delay(freq);

  //no light
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  delay(freq);
  
  //white light
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  delay(freq);

}
