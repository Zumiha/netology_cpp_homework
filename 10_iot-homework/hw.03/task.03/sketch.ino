// #define RED 13
// #define GREEN 12
// #define BLUE 11

enum LEDLIGHT {
  BLUE = 11,
  GREEN,
  RED
};

byte rows_pins[]= { 9, 8, 7, 6 };
byte cols_pins[]= { 5, 4, 3, 2 };

char k4x4[4][4] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#','D'}
};



class LedMode {
  enum ledname {
    REDLED = 0,
    GREENLED,
    BLUELED
  };
  public:
  LedMode () {
    this->blink_delay = 0;
  }
  void setState(bool red_val, bool green_val, bool blue_val) {
    this->led_active_state[REDLED] = !red_val;
    this->led_active_state[GREENLED] = !green_val;
    this->led_active_state[BLUELED] = !blue_val;
  }
  bool getState(int led_pos) {
    return this->led_active_state[led_pos];
  }

  void setDelay (int val) {
    this->blink_delay = val;
  }
  int blinkDelay() {
    return this->blink_delay;
  }

  private:
  bool led_active_state[3] = {!true, !true, !true};
  bool red_led_active;
  bool green_led_active;
  bool blue_led_active;

  int blink_delay;
};

LedMode LedState;

char GetKey4x4() {
  static unsigned long timer; // для подавления дребезга
  static char olda; //старый код нажатой клавиши
  char a = 0; //код нажатой клавиши
  if ((timer + 50) > millis()) return 0; // пауза для подавления дребезга
  for (byte p = 0; p <= 3; p++) // последовательно выставляем по одной строке в LOW
  {
    digitalWrite(rows_pins[p], LOW);
      for (byte m = 0; m <= 3; m++) // и считываем столбцы, анализируя, где LOW происходит
      {
        if (!digitalRead(cols_pins[m]))
        {
          a = k4x4[p][m]; // считываем соотвествующий символ для комбинации столбца и строки
        }
      }
    digitalWrite(rows_pins[p], HIGH); // возвращем строку в HIGH и крутим дальше
  }
  timer = millis();
  if (a == olda) return 0; //маскируем удержание
  olda = a;
  return a;
}

void ChangeLedMode(const char &inpt) {
  switch (inpt) {
    case 'A':
      LedState.setDelay(0); 
      // Serial.println(inpt);   
      break;
    case 'B':
      LedState.setDelay(500); 
    // Serial.println(inpt);
      break;
    case 'C':
      LedState.setDelay(250); 
    // Serial.println(inpt);
      break;
    case 'D':
      LedState.setDelay(125); 
    // Serial.println(inpt);
      break;
    case '0':
      Serial.println(inpt);
      LedState.setState(0, 0, 0);

      // for (auto it: led_active_state) {
      //   led_active_state[it] = 1;
      //   Serial.println(static_cast<String>(led_active_state[it]) + " ");
      // }        
      break;
    case '1':
      Serial.println(inpt);
      LedState.setState(0, 0, 1);
      break;
    case '2':
      Serial.println(inpt);
      LedState.setState(0, 1, 0);
      break;
    case '3':
      Serial.println(inpt);      
      LedState.setState(1, 0, 0);
      break;
    case '4':
      Serial.println(inpt);
      LedState.setState(1, 0, 1);
      break;
    case '5':
      Serial.println(inpt);
      LedState.setState(0, 1, 1);
      break;
    case '6':
      Serial.println(inpt);
      LedState.setState(1, 1, 0);
      break;
    case '7':  
      Serial.println(inpt);
      LedState.setState(1, 1, 1);
      break;
    case '8':
    case '9':
    default:
      break;
  }
}

void UpdateLed(LedMode &LedState) {
  delay(LedState.blinkDelay());
  
  int j = 0;
  for (int it = BLUE; it != 14; it++) {
    digitalWrite(it, LedState.getState(j));
    j++;
  }

  delay(LedState.blinkDelay());
  
  if (LedState.blinkDelay() != 0) {
    for (int it = BLUE; it != 14; it++) {
      digitalWrite(it, HIGH);
    }
  }
}


void setup() {
  for (int it = BLUE; it != 14; it++) {
    pinMode(it, OUTPUT);
    digitalWrite(it, 0);
  } 

  for (int i = 0; i <= 3; i++) {
    pinMode(rows_pins[i], OUTPUT);
    pinMode(cols_pins[i], INPUT_PULLUP);
    digitalWrite(rows_pins[i], HIGH);
  }
  Serial.begin(9600);
}


void loop() {
  UpdateLed(LedState);
  char a = GetKey4x4();
  ChangeLedMode(a);
  // if (a != 0) UpdateLed(LedState);
}
