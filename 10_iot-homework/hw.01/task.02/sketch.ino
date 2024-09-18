void setup()
{
  for (int i = 2; i < 12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}
void loop()
{
for (int i = 2; i < 12; i++) {
    digitalWrite(i, LOW);
    delay(500);
}

for (int i = 11; i > 0; i--) {
    digitalWrite(i, HIGH);
    delay(500);
}

}
