#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
#define LCDWIDTH 16

#define LED 13
#define SENSOR 2
#define YAXIS A0

unsigned long counter = 0;

bool led_on = false;
int led_timer = 2;

int val = 0;
int pirState = LOW;

int cross_pos_X = 0; int cross_pos_Y = 1;

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

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

void CheckMotionSensor() {
  val = digitalRead(SENSOR);
  if (val == HIGH) // есть сигнал от датчика 
  {
    if (pirState == LOW) {
      Serial.println("Motion detected!"); // отправляем сообщение только один раз
      updateLED(); // LED blink
      pirState = HIGH;
    }
  }  else {
    if (pirState == HIGH) {
      pirState = LOW;
      Serial.println("Motion ended!"); // отправляем сообщение только один раз
    }
  }
}

void updateLED() {
  digitalWrite(LED, HIGH);
  delay(led_timer*1000);
  digitalWrite(LED, LOW);
}

void JoystickControls() {
  int ycoord;
  ycoord = analogRead(YAXIS);

  if (ycoord < 512) {
    led_timer--;
    if (led_timer < 2) led_timer = 2;
  } else if (ycoord > 512) {
    led_timer++;
    if (led_timer > 10) led_timer = 10;
  }
  delay(100);
}

void updateLCD() {
  lcd.setCursor(0, 1);
  lcd.print("  ");
  lcd.setCursor(0, 1);
  lcd.print(led_timer);
}

void setup() {
  // Init
  pinMode(YAXIS, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);
  Serial.begin(9600); //for debug purpose
  lcd.init();
  lcd.backlight();
  lcd.begin(LCDWIDTH, 2);
  displayGreeting("Motion Sensor");
  delay(500);
  lcd.setCursor(0, 0); lcd.print("Delay:");
  lcd.setCursor(3, 1); lcd.print("seconds");
}


void loop() {
  updateLCD();
  CheckMotionSensor();
  JoystickControls();
}
