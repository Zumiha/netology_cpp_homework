#define XAXIS A0
#define YAXIS A1
#define BUTTON 8

#define TIMEDEL 100

int ledPins[] = {3, 5, 6, 9, 10, 11};
auto led_count = sizeof(ledPins)/sizeof(ledPins[0]);
int brightness = 150;
int firefly_position = (led_count/2 - 1);

int lastButton = LOW;
int curButton = LOW;


void JoystickControls() {
  int xcoord, ycoord;
  xcoord = analogRead(XAXIS);
  ycoord = analogRead(YAXIS); 
  
  if (xcoord > 512) {
    firefly_position = min(firefly_position + 1, led_count - 1);
  } else if (xcoord < 512) {
    firefly_position = max(firefly_position - 1, 0);
  }

  if (ycoord < 512) {
    brightness = max(brightness - 10, 0);
  } else if (ycoord > 512) {
    brightness = min(brightness + 10, 250);
  }
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
  curButton = debounce(lastButton, BUTTON);
  if (lastButton == LOW && curButton == HIGH) {
    firefly_position = led_count - 1; 
    brightness = 150;
  }
  
  lastButton = curButton;
}

void UpdateFirefly() {
  for (int it = 0; it < led_count; it++) {
    if (it == firefly_position) {
      analogWrite(ledPins[it], brightness);
    } else {
      analogWrite(ledPins[it], 0);
    }
  }
}

void setup() {
  Serial.begin(9600);
  for (int it = 0; it < led_count; it++) {
    pinMode(ledPins[it], OUTPUT);
    // digitalWrite(ledPins[it], LOW);
  }

  pinMode(XAXIS, INPUT);
  pinMode(YAXIS, INPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(ledPins[firefly_position], 150);
}

void loop() {
  JoystickControls();
  JoystickButton();
  UpdateFirefly();
  delay(TIMEDEL);

}
