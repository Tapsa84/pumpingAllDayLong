#include "arduino.h"
#include "HardwareSerial.h"
#include "phUnit.h"

phUnit::phUnit(HardwareSerial *serial) {
  this->serial = serial;
}

phUnit::phUnit() {

}

void phUnit::setTemp(float _setTemp) {
  this->_setTemp = _setTemp;
  this->serial->print("T,");
  this->serial->print(_setTemp);
  this->serial->print('\r');
  this->getTemp();
}

float phUnit::getTemp(void) {
  this->serial->print("T,");
  this->serial->print('\r');
  if (serial->available() > 0) {
    this->from_pH_meter = this->serial->readStringUntil('\r');
    this->_getTemp = from_pH_meter.toFloat();
    Serial.println(_setTemp);
    return _getTemp;
  }
}

float phUnit::getpH(void) {
  this->serial->print("R");
  this->serial->print("\r");
  if (serial->available() > 0) {
    this->from_pH_meter = this->serial->readStringUntil('r');
    this->pH_value = from_pH_meter.toFloat();
    return this->pH_value;
  }
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> refs/remotes/origin/pumpingAllDayLong
void phUnit::Calibrate(CalibMode *CalMode){
   this->CalMode = CalMode;   
}

void phUnit::setCalibMode(CalibMode *CalMode) {
  this->CalMode = CalMode;
}
<<<<<<< HEAD
bool phUnit::isCalibrated(void) {
  
  return this->_isCalibrated;
  
}

=======
=======
>>>>>>> refs/remotes/origin/pumpingAllDayLong
bool phUnit::isCalibrated(void) {
  
  if (this->_isCalibrated){
    return true;
  }
  else {
    return false;
    }
  
}

<<<<<<< HEAD
void phUnit::setCalibMode(CalibMode *CalMode) {
  this->CalMode = CalMode;
}
>>>>>>> refs/remotes/origin/pumpingAllDayLong
=======
>>>>>>> refs/remotes/origin/pumpingAllDayLong

