void bubbleUp (int start, int ind_delay) {
  for (int i = start; i < 12; i++) {
    digitalWrite(i, HIGH);
    delay(ind_delay);
    digitalWrite(i, LOW);
    delay(100);
  }
}

void bubbleDown(int start, int ind_delay) {
    for (int i = start; i > 1; i--) {
    digitalWrite(i, HIGH);
    delay(ind_delay);
    digitalWrite(i, LOW);
    delay(100);
  }
}

void setup() {
  for (int i = 2; i < 12; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  //bubble up
  int bottoms = 2;
  int ups = 11; 
  bubbleUp(bottoms, 1000);
  delay(1000);
  bubbleDown(ups, 500);
  delay(1000);
  bubbleUp(bottoms, 250);
  delay(1000);
  bubbleDown(ups, 100);
  delay(1000);

}
