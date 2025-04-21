//hw.09.2
#include <SD.h>

#define DIRPIN 8
#define STEPPIN 9

const int CSPin = 10;

int steps_per_revolution; //количество шагов на один оборот
int delay_step;

class StepDriver { // используем класс драйвера из задания 07.02
  public:
    StepDriver(int step_pin, int dir_pin) : m_steppin(step_pin), m_dirpin(dir_pin) {}
    ~StepDriver() {}
    void setSpeed(int speed) {
      this->m_speed = speed;
    }

    void step(int _steps, bool dir) {
      digitalWrite(this->m_dirpin, dir);
      for(int i = 0; i < abs(_steps); i++) {
        digitalWrite(this->m_steppin, HIGH); delayMicroseconds(abs(m_speed));
        digitalWrite(this->m_steppin, LOW); delayMicroseconds(abs(m_speed));
      }
    }

    void step(int _steps) {
      this->m_speed > 0 ? _steps > 0 ? digitalWrite(this->m_dirpin, HIGH) : digitalWrite(this->m_dirpin, LOW) : _steps > 0 ? digitalWrite(this->m_dirpin, LOW) : digitalWrite(this->m_dirpin, HIGH);
      for(int i = 0; i < abs(_steps); i++) {
        digitalWrite(this->m_steppin, HIGH); delayMicroseconds(abs(m_speed));
        digitalWrite(this->m_steppin, LOW); delayMicroseconds(abs(m_speed));
      }
    }

  private:
    int m_steppin;
    int m_dirpin;
    int m_speed = 0;
};


StepDriver sdcardStepper (STEPPIN, DIRPIN);


void setup()
{
  pinMode(DIRPIN, OUTPUT);
  pinMode(STEPPIN, OUTPUT);

  Serial.begin(115200);
  Serial.print("Initializing SD card... ");
  if (!SD.begin(CSPin)) //Если ошибка инициализации, то блокирование работы
  {
    Serial.println("Card initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

}

void loop()
{
  sdcardStepper.setSpeed(2000);

  File textFile = SD.open("wokwi.txt");
  if (textFile)
  {
    Serial.println("wokwi.txt: ");
    while (textFile.available())
    {
      // File в Arduino имеет синтаксис Serial, поэтому можно использовать методы для чтения из потока 
      int steps = textFile.parseInt(); 
      bool dir = textFile.parseInt();
      int pause = textFile.parseInt();

      sdcardStepper.step(steps, !dir);
      delay(pause);
    }
    textFile.close();
    Serial.println("file end");
  } else {
    Serial.println("error opening wokwi.txt!");
  }

  Serial.println("Loop completed!!!"); delay(5000);

}