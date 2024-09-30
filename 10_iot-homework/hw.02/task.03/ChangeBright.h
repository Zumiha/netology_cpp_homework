#include "ChangeBright.h"

ColorLed::ColorLed (  int blue_led_out, 
                int green_led_out, 
                int red_led_out, 
                
                int _blue_down, 
                int _blue_up, 
                int _green_down, 
                int _green_up, 
                int _red_down, 
                int _red_up, 
                
                int blue_start_bright, 
                int green_start_bright, 
                int red_start_bright,
                
                int brightness_step) 
{
    pinMode(blue_led_out, OUTPUT);
    pinMode(green_led_out, OUTPUT);
    pinMode(red_led_out, OUTPUT);

    digitalWrite(blue_led_out, LOW);
    digitalWrite(green_led_out, LOW);
    digitalWrite(red_led_out, LOW);

    pinMode(_blue_down, INPUT);
    pinMode(_blue_up, INPUT);
    pinMode(_green_down, INPUT);
    pinMode(_green_up, INPUT);
    pinMode(_red_down, INPUT);
    pinMode(_red_up, INPUT);

    blue_powr = blue_start_bright;
    green_powr = green_start_bright;
    red_powr = red_start_bright;

    bright_step = brightness_step;

    blue_down_pin = _blue_down;
    blue_up_pin = _blue_up;
    green_down_pin = _green_down;
    green_up_pin = _green_up;
    red_down_pin = _red_down;
    red_up_pin = _red_up;

    blue_led_pin = blue_led_out; 
    green_led_pin = green_led_out; 
    red_led_pin = red_led_out; 
}

void ColorLed::IncreaseBlue(){
    debounce(blue_up_pin, blue_powr, blue_down_last);
    analogWrite(blue_led_pin, blue_powr);
}
void ColorLed::DecreaseBlue (){
    debounce(blue_down_pin, blue_powr, blue_down_last);
    analogWrite(blue_led_pin, blue_powr);
}
void ColorLed::IncreaseGreen (){
    debounce(green_up_pin, green_powr, green_down_last);
    analogWrite(green_led_pin, green_powr);
}
void ColorLed::DecreaseGreen (){
    debounce(green_down_pin, green_powr, green_down_last);
    analogWrite(green_led_pin, green_powr);
}
void ColorLed::IncreaseRed (){
    debounce(red_up_pin, red_powr, red_down_last);
    analogWrite(red_led_pin, red_powr);
}
void ColorLed::DecreaseRed (){
    debounce(red_down_pin, red_powr, red_down_last);
    analogWrite(red_led_pin, red_powr);
}

void ColorLed::debounce (int button, int& color_powr, int& last_button_state)  {
  int current = digitalRead(button);
  if(last_button_state != current) {
    delay(10);
    current = digitalRead(button);
  }

  if (last_button_state == HIGH && current == LOW) {
    if (button == blue_down_pin || button == green_down_pin || button == red_down_pin) {
        color_powr = constrain(color_powr + bright_step, 0, 250); 
    } else {
        color_powr = constrain(color_powr - bright_step, 0, 250);
    }
  }
  last_button_state = current;
}

