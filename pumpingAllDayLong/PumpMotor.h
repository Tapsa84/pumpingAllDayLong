#pragma once
#ifndef PumpMotor_h
#define PumpMotor_h


class PumpMotor {


  private:
    int pwm_pin;
    int dir_pin;
    int ena_pin;
    boolean isRunning = false;
    boolean isCalibrated = false;
    int runMode;
    boolean cmd_received = false;
    String cmd = "";

   
    




    float pump_flow;

    float y1;
    float y2;
    float slope;
    float yintercept;

    int _setPwm = 0;
    int _setDir = 1;
    int lastPass = 0;
    int lastPassA = 0;

  public:

    String input_cal = "";

    

    int pump_time = 1000UL;
    enum RunMode {Continous, Dosing, Custom};
    RunMode rMode = Continous;
    
    enum Calibration_Status {air_done,pump60sec_1,pump60sec_2,init};
//    enum Calibration_Status {init = 1; pump
    Calibration_Status calibration_status = init;
    

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
    bool oncePerTime(int _time);
    bool getOk();
    bool getOk(int pumptime);


};

#endif

