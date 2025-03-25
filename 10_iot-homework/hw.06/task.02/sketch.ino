//hw.06.02
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

#define I2C_ADDR 0x27
#define LCDWIDTH 20
#define LCDHEIGHT 4

#define MPU_ADRR1 0x68
#define MPU_ADRR2 0x69

LiquidCrystal_I2C lcd(I2C_ADDR,LCDWIDTH,LCDHEIGHT);
MPU6050 mpu1(MPU_ADRR1);
MPU6050 mpu2(MPU_ADRR2);

int cross_pos_X = 0; int cross_pos_Y = 0;

const int coord = 3;
const int buffer_size = 10;
const char deg = 223;

int16_t ac_reading[coord][buffer_size];
int16_t gyro_reading[coord][buffer_size];
int buffer_step = 0;

String axis_name[] = {"oX:", "oY:", "oZ:"};
float accelAxis[coord];
float gyroAxis[coord];

float filterReading(int16_t readings[coord][buffer_size], int num) {
  float sum = 0;
  for (int i = 0; i < buffer_size; i++) {
    sum += readings[num][i];
  }
  return sum / buffer_size;
}

void clearLCDrow(int row) {
  lcd.setCursor(0, row);
  for (int i = 0; i < LCDWIDTH; i++) {
    lcd.print(" ");
  }
}

void displayRow (int axis) {
  int row = axis + 1;
  clearLCDrow(row);
  lcd.setCursor(0, row);
  lcd.print(axis_name[axis]);
  lcd.setCursor(5, row);
  lcd.print(accelAxis[axis], 2); lcd.print(" g"); 
  lcd.setCursor(14, row);
  lcd.print(gyroAxis[axis], 0); lcd.print(deg);  
}

void setup() {
  // put your setup code here, to run once:
  // lcd.init();
  lcd.backlight();
  lcd.begin(LCDWIDTH, LCDHEIGHT);

  Serial.begin(9600); //for debug purpose
  Wire.begin();
  mpu1.initialize();
  Serial.println(mpu1.testConnection() ? "MPU6050(1) OK" : "MPU6050(1) FAIL");
  mpu2.initialize();
  Serial.println(mpu2.testConnection() ? "MPU6050(2) OK" : "MPU6050(2) FAIL");

  delay(500);


  lcd.setCursor(5, 0);
  lcd.print("Accel:");
  lcd.setCursor(13, 0);
  lcd.print("Rotate:");
}


void loop() {
  // put your main code here, to run repeatedly:
  ac_reading[0][buffer_step] = abs(mpu1.getAccelerationX() - mpu2.getAccelerationX());
  ac_reading[1][buffer_step] = abs(mpu1.getAccelerationY() - mpu2.getAccelerationY());
  ac_reading[2][buffer_step] = abs(mpu1.getAccelerationZ() - mpu2.getAccelerationZ());

  gyro_reading[0][buffer_step] = abs(mpu1.getRotationX() - mpu2.getRotationX());
  gyro_reading[1][buffer_step] = abs(mpu1.getRotationY() - mpu2.getRotationY());
  gyro_reading[2][buffer_step] = abs(mpu1.getRotationZ() - mpu2.getRotationZ());

  buffer_step = (buffer_step + 1) % 10;

  for (int i = 0; i < coord; i++) {
    accelAxis[i] = filterReading(ac_reading, i)/32768*2;
    gyroAxis[i] = filterReading(gyro_reading, i)/32768*250;
    displayRow(i);
  }
  delay(100); 
}