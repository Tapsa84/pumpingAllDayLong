#include "arduino.h"
#include "HardwareSerial.h"
#include "phUnit.h"

phUnit::phUnit(HardwareSerial *serial) {
  this->serial = serial;
}

phUnit::phUnit(){
  
}

