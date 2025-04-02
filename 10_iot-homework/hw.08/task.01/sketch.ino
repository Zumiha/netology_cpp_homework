//hw.08.01
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <Servo.h>
#include "CyclicArray.h"

#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_LINES 2
#define LCDWIDTH 16

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

int cross_pos_X = 0; int cross_pos_Y = 0;
const char deg = 223;

const int PIN_RECEIVER = 2; // Вход для ИК приемника
IRrecv receiver(PIN_RECEIVER); // приемник иК

#define SERVO 3
Servo  servo_motor;
int angle_input;

CyclicArray inputCommands(SERVO);

void displayGreeting(String start_string) {
  lcd.clear();
  for (int i = 0; i < LCDWIDTH + 2; i++) {
    start_string = " " + start_string;
  }
  lcd.print(start_string);
  for (int i = 0; i < (LCDWIDTH + 2) * 2; i++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  lcd.clear();
  // lcd.blink();
  // lcd.cursor();
}

//Функция вывода нового значения на индикатор
void lcdPrint(char* text, int& value)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
  lcd.setCursor(0, 1);
  lcd.print(" Value: ");
  lcd.print(value); lcd.print(deg);
}

void translateIR()
{
  switch (receiver.decodedIRData.command) {
    case 168:
      angle_input = inputCommands.valueServo();
      if (angle_input > 180) {
        inputCommands.reset_input();
        angle_input = inputCommands.valueServo();
        lcdPrint("WRONG ANGLE", angle_input);
      } else {
        lcdPrint("ACTUATE SERVO", angle_input);
        servo_motor.write(angle_input);
        delay(15);
      }
      break;
    case 176:
      inputCommands.reset_input();
      angle_input = inputCommands.valueServo();
      lcdPrint("CANCEL INPUT", angle_input);
      break;
    case 104:
    case 48:
    case 24:
    case 122:
    case 16:
    case 56:
    case 90:
    case 66:
    case 74:
    case 82:
      inputCommands.push_back(receiver.decodedIRData.command);
      angle_input = inputCommands.valueServo();
      lcdPrint("ANGLE INPUT", angle_input);
      break;
    default:
      lcd.clear();
      lcd.print(receiver.decodedIRData.command);
      lcd.print(" other button ");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //for debug purpose
  lcd.init();
  lcd.backlight();
  lcd.begin(LCDWIDTH, LCD_LINES);
  displayGreeting("IR control...");
  delay(500);
  servo_motor.attach(SERVO);
  lcd.print("<press a button>");
  receiver.enableIRIn(); // Запуск ИК приемника
}

void loop() {
  // put your main code here, to run repeatedly:
  if (receiver.decode()) //проверка новых данных
  {
    translateIR();
    // Serial.println(inputCommands.current());
    receiver.resume(); //запуск приема новой команды
  }

}

