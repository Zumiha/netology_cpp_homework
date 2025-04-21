//hw.09.01

#define LEDNUM 16
#define BUTTON 2

const int dataPin = 11; 
const int latchPin = 4; // пин, управляющий выходной защёлкой
const int clockPin = 13;

int btn_pressed = LOW;

int delay_val = 600;
volatile int speed_gear = 0;

void setup()
{
  Serial.begin(9600); // for debug purpose
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);  
  pinMode(latchPin, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(0, changeSpeed, FALLING);
  delay(100);
}

void loop()
{
  shiftRegVal(HIGH); // в начале цикла в сдвиговый регистр записывается битовая еденица (начальный горящий LED)
  delay(delay_val >> speed_gear);
  for (int i = 0; i < LEDNUM; i++) {
    shiftRegVal(LOW); // "проталкиваем" каждый раз битовый ноль, чтобы смещать горящий LED
    delay(delay_val >> speed_gear);
  }
}

void shiftRegVal(int _val) {
  digitalWrite(latchPin, LOW);  // Установка выходной защелки на LOW для ввода данных
  digitalWrite(clockPin, LOW);      // Установка такта на LOW для переключения в следующего бита
  digitalWrite(dataPin, _val);  // Запишись текущего бита
  digitalWrite(clockPin, HIGH);     //  Установка такта на HIGH для сдвига бита
  digitalWrite(latchPin, HIGH);  // Установка на HIGH для защелкивания данных на пины
}

void changeSpeed() {
  int speed_change = debounce(btn_pressed);
  if(btn_pressed == HIGH && speed_change == LOW){
    speed_gear++;
    if (speed_gear > 3) speed_gear = 0;
    Serial.println(delay_val >> speed_gear);
  }
  btn_pressed = speed_change;
}

int debounce (int last)  {
  int current = digitalRead(BUTTON);
  if(last != current) {
    delay(10);
    current = digitalRead(BUTTON);
  }
  return current;
}
