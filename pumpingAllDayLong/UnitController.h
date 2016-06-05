#pragma once
#ifndef UnitController_h
#define UnitController_h
#include "PumpMotor.h"
#include "phUnit.h"


class UnitController {

  private:
    String unit_name = "";
    int stall_time = 1000UL;
    
    int lastPassA = 0;
    


  public:

    String input_cmd = "";
    int lastPass = 0;
    enum Controller_state {on, off, cal_pumpA, cal_pumpB, cal_pH};
    Controller_state controller_state = on;

    enum Cal_state {air,pump1,pump2,getY1,getY2};
    Cal_state cal_state = air;

    phUnit *_phUnit;
   
    
    float desired_pH =7;
    float dummy_pH = 8;
    PumpMotor *pumpA;
    PumpMotor *pumpB;

    
    
    
    


    enum pHdirection {up, down};
    pHdirection pH_dir = up;


    UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit, String unit_name);
    void calibrate_pump(PumpMotor *pump);
    void get_input();
    bool timeStall();
    bool calCheck();
    void start();
    void tick();
    void adjust_pH(PumpMotor *pump);
    void unit_off();
    float getDummy_pH(void);



};

#endif


