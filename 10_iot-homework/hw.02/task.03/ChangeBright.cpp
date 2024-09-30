#ifndef ChangeBright
#define ChangeBright

#include "Arduino.h"

#define OUTPUT 1
#define INPUT 0

#define LOW 1
#define HIGH 0


class ColorLed {
    public:
    ColorLed (  int blue_led_out, 
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
                
                int brightness_step);

    ColorLed(const ColorLed &) = delete;
    ColorLed(ColorLed &&) = delete; 

    void IncreaseBlue();
    void IncreaseGreen();
    void IncreaseRed();
    void DecreaseBlue();
    void DecreaseGreen();
    void DecreaseRed();

    protected:
    void debounce (int button, int& color_powr, int& last_button_state);
    void ChangeBrightness (int button_type);

    private: 
    int blue_powr;  
    int green_powr; 
    int red_powr;   

    int bright_step;

    int blue_down_last = LOW;
    int blue_up_last = LOW;
    int green_down_last = LOW;
    int green_up_last = LOW;
    int red_down_last = LOW;
    int red_up_last = LOW;

    int blue_down_pin;
    int blue_up_pin;
    int green_down_pin;
    int green_up_pin;
    int red_down_pin;
    int red_up_pin;

    int blue_led_pin;
    int green_led_pin;
    int red_led_pin;


};

#endif