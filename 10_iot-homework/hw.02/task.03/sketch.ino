#include "ChangeBright.h"

ColorLed rgb_light(11, 12, 13, 2, 3, 4, 5, 6, 7, 250, 250, 250, 10);

void setup() {

}

void loop() {
  rgb_light.DecreaseBlue();
  rgb_light.IncreaseBlue();
  rgb_light.DecreaseGreen();
  rgb_light.IncreaseGreen();
  rgb_light.DecreaseRed();
  rgb_light.IncreaseRed();
}