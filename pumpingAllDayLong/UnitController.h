#pragma once
#ifndef UnitController_h
#define UnitController_h
#include "PumpMotor.h"
#include "phUnit.h"


class UnitController {

  private:

    
    int lastPassA = 0;
    int lastPassB = 0;
    
    int stall_time = 1000UL;
    int lastPass = 0;

    
    
  
  public:
    float desired_pH =7;
    float dummy_pH = 6;
    PumpMotor *pumpA;
    PumpMotor *pumpB;
    phUnit *_phUnit;
    enum pHdirection {up, down};
    pHdirection pH_dir = up;
    
    
    
    
    UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit);
    UnitController();
    bool timeStall();
    bool calCheck();
    void start();
    void tick();
    float getDummy_pH(void);



};

#endif

