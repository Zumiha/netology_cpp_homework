#include <LiquidCrystal.h>

#define XAXIS A0
#define YAXIS A1
#define JBUTN 6
#define LCDWIDTH 16

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int lastButton = LOW;
int curButton = LOW;

int cross_pos_X = 0; int cross_pos_Y = 1;
int disp_list [26] {};
int list_iter = -1;


void displayGreeting() {
  lcd.clear();
  
  String start_string = "LCD Characters";

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
  lcd.blink();
  // lcd.cursor();
}

int debounce (int last, int _button)  {
  int current = digitalRead(_button);
  if(last != current) {
    delay(15);
    current = digitalRead(_button);
  }
  return current;
}

void JoystickButton() {
  curButton = debounce(lastButton, JBUTN);
  if (lastButton == LOW && curButton == HIGH) {
    if (cross_pos_Y == 0) {
      cross_pos_Y = 1;
    } else {
      cross_pos_Y = 0;
    }
    list_iter = -1;
    lcd.setCursor(cross_pos_X, cross_pos_Y);
  }  
  lastButton = curButton;
}

void changePos(int _val) {
  if (_val > 800 && cross_pos_X > 0) {
    cross_pos_X--;

  } else if (_val < 200 && cross_pos_X < 15) {
    cross_pos_X++;

  }
  delay(100);
}

void changeChar(int _val) {
  if (_val < 200 && list_iter > -1) {
    list_iter--;
  } else if (_val > 800 && list_iter < 26) {
    list_iter++;
  }
  delay(100);
}

void updateDisplay() {
  if (list_iter < 0 || list_iter > 25) {
    lcd.print(char(32)); 
    lcd.setCursor(cross_pos_X, cross_pos_Y);
    return;
  } 
  auto letter = static_cast<char> (disp_list[list_iter]);
  lcd.setCursor(cross_pos_X, cross_pos_Y);
  lcd.print(letter);
  lcd.setCursor(cross_pos_X, cross_pos_Y);
}

void updateCursor() {
  lcd.setCursor(cross_pos_X, cross_pos_Y);
  list_iter = -1;
}

void setup() {
  Serial.begin(9600);
  pinMode(XAXIS, INPUT);
  pinMode(YAXIS, INPUT);
  pinMode(JBUTN, INPUT_PULLUP);
  lcd.begin(LCDWIDTH, 2);
  
  displayGreeting();

  int list_size = sizeof(disp_list)/sizeof(disp_list[0]);
  {
    int first_char = 65;
    for (int i = 0; i < list_size; i++) {
      disp_list[i] = first_char + i;
    }
  }
  lcd.setCursor(cross_pos_X, cross_pos_Y);
}

void loop() {
  int xcoord, ycoord;
  xcoord = analogRead(XAXIS);
  if (xcoord != 512) {
    changePos(xcoord);
    updateCursor(); 
  }
  ycoord = analogRead(YAXIS);
  if (ycoord != 512) {
    changeChar(ycoord);
    updateDisplay();
  }
  JoystickButton();
}