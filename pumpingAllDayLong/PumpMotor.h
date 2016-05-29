#pragma once
#ifndef PumpMotor_h
#define PumpMotor_h


class PumpMotor {


  private:
    int pwm_pin;
    int dir_pin;
    int ena_pin;
    bool isRunning = false;
    bool isCalibrated = false;
    int runMode;





    float pump_flow;

    float y1;
    float y2;
    float slope;
    float yintercept;

    int _setPwm = 0;
    int _setDir = 1;
    int lastPass = 0;

  public:

    int pump_time = 1000L;
    enum RunMode {Continous, Dosing, Custom};
    RunMode rMode;
    PumpMotor(int pwm_pin, int dir_pin, int ena_pin);
    PumpMotor();

    void getSettings(int rMode, float pump_flow, float y1, float y2);
    void setPumpTime(int pump_time);
    void setPwm(int _setPwm);
    int getPwm(void);
    void setRunMode();
    void set_direction(int p_direction);
    void on();
    void off();
    bool isOn();
    void toggle();
    void calibrate();
    void calflow();
    bool isCalib();
    bool oncePerTime();


};

#endif
