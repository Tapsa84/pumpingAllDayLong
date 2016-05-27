#ifndef UnitController_h
#define UnitController_h
#include "phUnit.h"

class UnitController {

  private:

  
  
    



  public:
    PumpMotor pumpA;
    PumpMotor pumpB;
    phUnit _phUnit;
    
    
    UnitController(PumpMotor pumpA, PumpMotor pumpB, phUnit _phUnit);


};

#endif

