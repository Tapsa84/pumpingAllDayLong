#pragma once
#ifndef UnitController_h
#define UnitController_h
#include "PumpMotor.h"
#include "phUnit.h"


class UnitController {

  private:
    PumpMotor *pumpA;
    PumpMotor *pumpB;
    phUnit *_phUnit;
    int lastPassA = 0;
    int lastPassB = 0;
    
  
  public:
    
    
    
    UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit);
    UnitController();
    void tick();
    


};

#endif

