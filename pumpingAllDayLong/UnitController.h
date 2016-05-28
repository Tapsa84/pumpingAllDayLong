#pragma once
#ifndef UnitController_h
#define UnitController_h
#include "PumpMotor.h"
#include "phUnit.h"


class UnitController {

  private:
<<<<<<< HEAD
    PumpMotor *pumpA;
    PumpMotor *pumpB;
    phUnit *_phUnit;
    int lastPassA = 0;
    int lastPassB = 0;
    
  
  public:
    
=======

  
  public:
    PumpMotor *pumpA;
    PumpMotor *pumpB;
    phUnit *_phUnit;
>>>>>>> refs/remotes/origin/pumpingAllDayLong
    
    
    UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit);
    UnitController();
<<<<<<< HEAD
    void tick();
    
=======
>>>>>>> refs/remotes/origin/pumpingAllDayLong


};

#endif

