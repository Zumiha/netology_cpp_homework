  #include <LiquidCrystal.h>

  LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
  #define LCDWIDTH 16

  int cross_pos_X = 0; int cross_pos_Y = 1;

  const float BETA = 3950; 
  const float T0 = 298.15; 
  const int thermistorPins[] = {A0, A1, A2};
  const int thermistorCount = 3;
  const int buffer_size = 10;

  float temperatures[thermistorCount][buffer_size];
  int step = 0;

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

  float calculateAverageTemperature(float temps[thermistorCount][buffer_size], int num) {
    float sum = 0;
    for (int i = 0; i < buffer_size; i++) {
      sum += temps[num][i];
    }
    return sum / buffer_size;
  }

  void setup() {
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    displayGreeting("Initializing...");
    delay(2000);
    for (int j = 0; j < thermistorCount; j++) {
      for (int i = 0; i < buffer_size; i++) {
        temperatures[j][i] = 0;
      }
    }  
    lcd.clear();
  }

  void loop() {

    for (int j = 0; j < thermistorCount; j++) {
      temperatures[j][step] = readTemperature(thermistorPins[j]);
    }
    step = (step + 1) % 10;
    float avgTemp1 = calculateAverageTemperature(temperatures, 0);
    float avgTemp2 = calculateAverageTemperature(temperatures, 1);
    float avgTemp3 = calculateAverageTemperature(temperatures, 2);

    float minTemp = min(avgTemp1, min(avgTemp2, avgTemp3));
    float maxTemp = max(avgTemp1, max(avgTemp2, avgTemp3));
    float avgTemp = (avgTemp1 + avgTemp2 + avgTemp3) / 3.0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mx:");
    lcd.print(maxTemp, 1);
    lcd.print(" Mn:");
    lcd.print(minTemp, 1);

    lcd.setCursor(0, 1);
    lcd.print("Avg:");
    lcd.print(avgTemp, 1);

    delay(100);
  }