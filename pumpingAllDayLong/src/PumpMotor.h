
#ifndef PumpMotor_h
#define PumpMotor_h

#include <Arduino.h>

class PumpMotor {
  private:
    int pwm_pin;
    int dir_pin;
    int ena_pin;
    boolean isRunning = false;
    int pwm;

  public:
    PumpMotor(int pwm_pin, int dir_pin, int ena_pin);

    void setPwm(int pwm);
    int getPwm(void);
    void set_direction(int direction);
    void on();
    void off();
    bool isOn();
    bool isOff();
};

#endif
