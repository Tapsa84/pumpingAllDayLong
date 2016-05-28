#pragma once
#ifndef PumpMotor_h
#define PumpMotor_h


class PumpMotor {


<<<<<<< HEAD
<<<<<<< HEAD
  private:
    int pwm_pin;
    int dir_pin;
    int ena_pin;
    bool isRunning = false;
    bool isCalibrated = false;
    enum RunMode {Continous, Dosing, Custom};
    RunMode rMode;


    float pump_time = 5000;
    float pump_flow;

    float y1;
    float y2;
    float slope;
    float yintercept;
  
    int _setPwm = 0;
    int _setDir = 1;
    float lastPass;
=======
  private:
    int pwm_pin;
    int dir_pin;
    int ena_pin;;
    bool isRunning = false;
    enum RunMode {Continous, Dosing, Custom};
    RunMode *rMode;

    int _setPwm = 0;
    int _setDir = 1;
>>>>>>> refs/remotes/origin/pumpingAllDayLong

  public:

    PumpMotor(int pwm_pin, int dir_pin, int ena_pin);
    PumpMotor();
<<<<<<< HEAD

    void getSettings(int _setPwm, int _setDir, int rMode,float pump_flow, float y1, float y2);
    void setPumpTime(float pump_time);
    void setPwm(int _setPwm);
    int getPwm(void);
    void setRunMode();
=======
    void setPwm(int _setPwm);
    int getPwm(void);
    void setRunMode(RunMode *rMode);
>>>>>>> refs/remotes/origin/pumpingAllDayLong
    void set_direction(int p_direction);
    void on();
    void off();
    bool isOn();
    void toggle();
<<<<<<< HEAD
    void calibrate();
    void calflow();
    bool oncePerTime();
    

=======
    private:
         int pwm_pin;
         int direction_pin = 1;
         int enable_pin = 0;

         int _setPwm = 0;

         public:

         PumpMotor(int pwm_pin, int direction_pin, int enable_pin);
         PumpMotor();
         void setPwm(int _setPwm);
         int getPwm(void);

         
>>>>>>> refs/remotes/origin/pumpingAllDayLong
=======

>>>>>>> refs/remotes/origin/pumpingAllDayLong
};

#endif
