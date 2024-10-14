#define SEG_COUNT 7 //количество используемых сегментов

#define BUTTON 13

const int firstSeg = 2; //младший номер вывода для подключения индикатора

// Таблица перекодировки символов

byte numberSegments[10] = {
  0b00111111,
  0b00001010,
  0b01011101,
  0b01011110,
  0b01101010,
  0b01110110,
  0b01110111,
  0b00011010,
  0b01111111,
  0b01111110,
};

int lastButton = LOW;
int curButton = LOW;

int debounce (int last)  {
  int current = digitalRead(BUTTON);
  if(last != current) {
    delay(10);
    current = digitalRead(BUTTON);
  }
  return current;
}

int number = 0;

void setup() {
  for (int i = 0; i < SEG_COUNT; ++i)
  pinMode(i + firstSeg, OUTPUT);
}

void loop() {

int mask;
boolean enableSegment;

  curButton = debounce (lastButton);
  if(lastButton == HIGH && curButton == LOW)  {
    number++;
  } 
  
  lastButton = curButton;
  
  mask = numberSegments[number];
  for (int i = 0; i < SEG_COUNT; i++) {
    enableSegment = bitRead(mask, i);
    digitalWrite(i + firstSeg, enableSegment);
  }

  if (number > 9) number = 0;

}