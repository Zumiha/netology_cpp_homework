class StepDriver {
  public:
    StepDriver(int step_pin, int dir_pin) : m_steppin(step_pin), m_dirpin(dir_pin) {}
    ~StepDriver() {}
    void setSpeed(int speed) {
      this->m_speed = speed;
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