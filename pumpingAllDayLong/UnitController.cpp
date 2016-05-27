#include "Arduino.h"
#include "PumpMotor.h"
#include "UnitController.h"
#include "phUnit.h"
#include "HardwareSerial.h"


UnitController::UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit) {
  this->pumpA = pumpA;
  this->pumpB = pumpB;
  this->_phUnit = _phUnit;
  
}
