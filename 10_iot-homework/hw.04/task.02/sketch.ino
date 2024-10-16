#include <SevSeg.h> 

SevSeg sevseg;

#define LAUNCH A0
#define RESET A1

bool watch_running = true;
unsigned long last_refresh = 0;
unsigned long seconds = 0;

int launch_last = LOW;
int reset_last = LOW;

void StopWatchDisplay() {
  if (watch_running) {
    unsigned long current = millis();
    if (current - last_refresh >= 1000) {
      last_refresh += 1000;
      seconds++;
      if (seconds >= 1000) {
        seconds = 0;
      }
    }
  }
  sevseg.setNumber(seconds, 0);
  sevseg.refreshDisplay(); // Must run repeatedly
}

void LaunchButton() {
  int current_state = digitalRead(LAUNCH);
  if (launch_last != current_state) {
    delay(50);
    current_state = digitalRead(LAUNCH);
    if (launch_last == HIGH && current_state == LOW) {
      watch_running = !watch_running;
      if (watch_running) last_refresh = millis();
    }
  }
  launch_last = current_state;
}

void ResetButton() {
  if (!watch_running) {  
    int current_state = digitalRead(RESET);
    if (reset_last != current_state) {
      delay(50);
      current_state = digitalRead(RESET);
      if (reset_last == HIGH && current_state == LOW) {
        last_refresh = millis();
        seconds = 0;     
      }
    }
  reset_last = current_state;
  }
}


void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  pinMode(LAUNCH, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
}

void loop() {
  StopWatchDisplay();
  LaunchButton();
  ResetButton();

}