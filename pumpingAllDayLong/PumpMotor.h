#pragma once
#ifndef PumpMotor_h
#define PumpMotor_h


struct Pump_Settings {
 
      float y1 = 0;
      float y2 = 0;  
      int pump_flow = 17;
      int rMode = 0;
      int _setDir = 0;

};

class PumpMotor {


  private:
    int pwm_pin;
    int dir_pin;
    int ena_pin;
    boolean isRunning = false;
    boolean isCalibrated = false;
    int runMode; 
    float pump_flow;  
    float y1;
    float y2;
    float slope;
    float yintercept;

    int _setPwm = 0;
    int _setDir = 0;
    
    int lastPassA = 0;

  public:

    int lastPass = 0;
    bool isCalibrating = false;
    Pump_Settings *pump_settings;
    String input_cal = "";
    String input_cal_value = "";

    

    int pump_time = 1000;
    enum RunMode {Continous, Dosing, Custom};
    RunMode rMode = Continous;
    
    enum Calibration_Status {pump60sec_1,pump60sec_2,init, getY1, getY2};
    Calibration_Status calibration_status = init;
    

    PumpMotor(int pwm_pin, int dir_pin, int ena_pin);

    void setSettings(Pump_Settings *pump_settings);
    void setPumpTime(int pump_time);
    void setPwm(int _setPwm);
    int getPwm(void);
    void setRunMode();
    void set_direction(int p_direction);
    void on();
    void off();
    bool isOn();
    void toggle();
    void get_input();
    bool air_out();
    bool pump60sec(int pwm);
    void calflow();
    bool isCalib();
    bool oncePerTimePH();
    bool oncePerTime(int _time);
    bool getOk();
    bool getOk(int pumptime);


};

#endif
