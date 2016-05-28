#pragma once
#ifndef PumpMotor_h
#define PumpMotor_h


class PumpMotor {


  private:
    int pwm_pin;
    int dir_pin;
    int ena_pin;;
    bool isRunning = false;
    enum RunMode {Continous, Dosing, Custom};
    RunMode *rMode;

    int _setPwm = 0;
    int _setDir = 1;

  public:

    PumpMotor(int pwm_pin, int dir_pin, int ena_pin);
    PumpMotor();
    void setPwm(int _setPwm);
    int getPwm(void);
    void setRunMode(RunMode *rMode);
    void set_direction(int p_direction);
    void on();
    void off();
    bool isOn();
    void toggle();

};

#endif
