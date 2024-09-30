#define BLUE 11
#define GREEN 12
#define RED 13
#define BUTTON 2

#define BLUE_DOWN 2  
#define BLUE_UP 3    
#define GREEN_DOWN 4 
#define GREEN_UP 5  
#define RED_DOWN 6    
#define RED_UP 7      

#define STEP 50

int blue_powr = 250;  
int green_powr = 250; 
int red_powr = 250;   

int blue_down_last = LOW;
int blue_up_last = LOW;
int green_down_last = LOW;
int green_up_last = LOW;
int red_down_last = LOW;
int red_up_last = LOW;

void debounce (int button, int& color_powr, int& last_button_state)  {
  int current = digitalRead(button);
  if(last_button_state != current) {
    delay(10);
    current = digitalRead(button);
  }

  if (last_button_state == HIGH && current == LOW) {
    switch(button) {
      case BLUE_DOWN:
      case GREEN_DOWN:
      case RED_DOWN:
        color_powr = constrain(color_powr + STEP, 0, 250); break;
      default:
        color_powr = constrain(color_powr - STEP, 0, 250); break;
    }
  }
  last_button_state = current;
}

void setup()
{
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);

  pinMode(BLUE_DOWN, INPUT_PULLUP);
  pinMode(BLUE_UP, INPUT_PULLUP);
  pinMode(GREEN_DOWN, INPUT_PULLUP);
  pinMode(GREEN_UP, INPUT_PULLUP);
  pinMode(RED_DOWN, INPUT_PULLUP);
  pinMode(RED_UP, INPUT_PULLUP);
  
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);

  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
}

void loop() {

  debounce(BLUE_DOWN, blue_powr, blue_down_last);
  debounce(BLUE_UP, blue_powr, blue_up_last);

  debounce(GREEN_DOWN, green_powr, green_down_last);
  debounce(GREEN_UP, green_powr, green_up_last);

  debounce(RED_DOWN, red_powr, red_down_last);
  debounce(RED_UP, red_powr, red_up_last);

  analogWrite(BLUE, blue_powr);
  analogWrite(GREEN, green_powr);
  analogWrite(RED, red_powr);

}
