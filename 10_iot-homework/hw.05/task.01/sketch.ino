#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
#define LCDWIDTH 16

int cross_pos_X = 0; int cross_pos_Y = 1;

const float BETA = 3950; 
const float T0 = 298.15; 
const int thermistorPins[] = {A0, A1, A2};
const int thermistorCount = 3;

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

float readTemperature(int pin) {
  int analogValue = analogRead(pin);
  if (analogValue == 0 || analogValue == 1023) {
    return NAN; // Если датчик неправильно подключён или вне диапазона
  }
  float celsius = 1 / (log(1 / (1023.0 / analogValue - 1)) / BETA + 1.0 / T0) - 273.15;
  return celsius;
}

float findMaxTemperature(float temps[], int size) {
  float maxTemp = temps[0];
  for (int i = 1; i < size; i++) {
    if (temps[i] > maxTemp) {
      maxTemp = temps[i];
    }
  }
  return maxTemp;
}

float findMinTemperature(float temps[], int size) {
  float minTemp = temps[0];
  for (int i = 1; i < size; i++) {
    if (temps[i] < minTemp) {
      minTemp = temps[i];
    }
  }
  return minTemp;
}

float calculateAverageTemperature(float temps[], int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += temps[i];
  }
  return sum / size;
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  displayGreeting("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temperatures[thermistorCount];

  for (int i = 0; i < thermistorCount; i++) {
    temperatures[i] = readTemperature(thermistorPins[i]);
  }

  float maxTemp = findMaxTemperature(temperatures, thermistorCount);
  float minTemp = findMinTemperature(temperatures, thermistorCount);
  float avgTemp = calculateAverageTemperature(temperatures, thermistorCount);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mx:");
  lcd.print(maxTemp, 1);
  lcd.print(" Mn:");
  lcd.print(minTemp, 1);

  lcd.setCursor(0, 1);
  lcd.print("Avg:");
  lcd.print(avgTemp, 1);

  delay(1000);
}
