#pragma once
#ifndef UnitController_h
#define UnitController_h
#include "PumpMotor.h"
#include "phUnit.h"


class UnitController {

  private:
    int stall_time = 1000UL;
    int lastPass = 0;

    
    
    
  

    int lastPassA = 0;


  public:
    
    enum Controller_state {on, off, cal_pumpA, cal_pumpB, cal_pH};
    Controller_state controller_state = on;

    phUnit *_phUnit;
   
    
    float desired_pH =7;
    float dummy_pH = 8;
    PumpMotor *pumpA;
    PumpMotor *pumpB;

    
    
    
    


    enum pHdirection {up, down};
    pHdirection pH_dir = up;


    UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit);
    UnitController();
    bool timeStall();
    bool calCheck();
    void start();
    void tick();
    void adjust_pH(PumpMotor *pump);
    float getDummy_pH(void);



};

#endif


