//hw.06.01
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
#define LCDWIDTH 16

#define MPU_ADRR 0x68

LiquidCrystal_I2C lcd(I2C_ADDR,LCD_COLUMNS,LCD_LINES);
MPU6050 mpu(MPU_ADRR);

int cross_pos_X = 0; int cross_pos_Y = 0;

const int coord = 3;
const int buffer_size = 10;

int16_t ac_reading[coord][buffer_size];
int buffer_step = 0;

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
  // lcd.blink();
  // lcd.cursor();
}

float filterAccel(int16_t readings[coord][buffer_size], int num) {
  float sum = 0;
  for (int i = 0; i < buffer_size; i++) {
    sum += readings[num][i];
  }
  return sum / buffer_size;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //for debug purpose
  lcd.init();
  lcd.backlight();
  lcd.begin(LCDWIDTH, LCD_LINES);
  displayGreeting("MPU6050 Initilization");
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("acX:");
  lcd.setCursor(6, 0);
  lcd.print("acY:");
  lcd.setCursor(12, 0);
  lcd.print("acZ:");
}

void loop() {
  // put your main code here, to run repeatedly:
  ac_reading[0][buffer_step] = mpu.getAccelerationX();
  ac_reading[1][buffer_step] = mpu.getAccelerationY();
  ac_reading[2][buffer_step] = mpu.getAccelerationZ();
  buffer_step = (buffer_step + 1) % 10;

  float Axis1 = filterAccel(ac_reading, 0)/32768*2;
  float Axis2 = filterAccel(ac_reading, 1)/32768*2;
  float Axis3 = filterAccel(ac_reading, 2)/32768*2;

  lcd.setCursor(0, 1);
  lcd.print("                ");

  lcd.setCursor(0, 1);
  lcd.print(Axis1, 1);

  lcd.setCursor(6, 1);
  lcd.print(Axis2, 1);
  
  lcd.setCursor(12, 1);
  lcd.print(Axis3, 1);

  delay(150); 
}
