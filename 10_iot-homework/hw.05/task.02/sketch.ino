#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define LCDWIDTH 16
#define BLUE 9 
#define GREEN 10 
#define RED 11
#define TRIG 13
#define ECHO 12

#define DELAY_ULTRASONIC 100
#define DELAY_DISPLAY_LCD 1000

float distance_cmeters;
float distance_meters;
int cross_pos_X = 0; int cross_pos_Y = 1;
unsigned int timer_ut = 0, timer_lcd = 0, timer_led = 0;

void ReadUltrasonicDistance() {  
  if (millis() - timer_ut >= DELAY_ULTRASONIC) {

    pinMode(TRIG, OUTPUT); // сброс Trig  
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG, HIGH); // установка TRIG на 10 мкс
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    pinMode(ECHO, INPUT); // измерение длительности ECHO
    distance_cmeters = (pulseIn(ECHO, HIGH) / 58.0);
    distance_meters = distance_cmeters/100;
    timer_ut = millis();
  }
}

void setLCDText() {
  lcd.setCursor(0, 0);
  lcd.print("distance:");
}

void setLCDDistance() {
  lcd.setCursor(0, 1);
  for (int i = 0; i < LCDWIDTH; i++) {
    lcd.print(" ");
  }
}

void updateLCD() {
  if (millis() - timer_lcd >= DELAY_DISPLAY_LCD) {
    setLCDDistance();
    lcd.setCursor(0, 1);
    lcd.print(distance_meters, 1);
    lcd.setCursor(4, 1);
    lcd.print("m");
    timer_lcd = millis();
  }
}

void SetLEDColor(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void updateLED() {
  if (distance_meters < 1.0) {
    if (millis() - timer_led >= 150) {
      SetLEDColor(0, 255, 255); // Red
      delay(distance_meters*150);
      SetLEDColor(255, 255, 255); 
      timer_led = millis();
    }
  } else if (distance_meters >= 1.0 && distance_meters < 3.0) {
    if (millis() - timer_led >= 150) {
      SetLEDColor(0, 0, 255); // Yellow
      delay(distance_meters*150);
      SetLEDColor(255, 255, 255);
      timer_led = millis();
    }
  } else if (distance_meters >= 3.0) {
    if (millis() - timer_led >= 300) {
      SetLEDColor(255, 0, 255); // Green
      delay(300);
      SetLEDColor(255, 255, 255);
      timer_led = millis();
    }
  } else {
    SetLEDColor(255, 255, 255);
  }
}

void displayGreeting(String start_string) {
  lcd.clear();

  for (int i=0; i < LCDWIDTH + 2; i++) {
    start_string = " " + start_string;  
  } 
  lcd.print(start_string);
  for (int i = 0; i < (LCDWIDTH + 2)*2; i++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }

  lcd.clear();
  lcd.setCursor(cross_pos_X, cross_pos_Y);
  // lcd.blink();
  // lcd.cursor();
}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  displayGreeting("Parktronic...");
  delay(2000);
  lcd.clear();

  setLCDText();
}

void loop() {
  ReadUltrasonicDistance();
  updateLCD();
  updateLED();
}