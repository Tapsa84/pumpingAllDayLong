#include "arduino.h"
#include "HardwareSerial.h"
#include "phUnit.h"

phUnit::phUnit(HardwareSerial *serial) {
  this->serial = serial;
}

phUnit::phUnit() {

}

void phUnit::calMid(float pH) {
  SerialUSB.print("Calibrating mid with ");
  SerialUSB.println(pH);
  this->serial->print("Cal,mid,");
  this->serial->print(pH);
  this->serial->print("\r");
}

void phUnit::calLow(float pH) {
  SerialUSB.print("Calibrating low with ");
  SerialUSB.println(pH);
  this->serial->print("Cal,low,");
  this->serial->print(pH);
  this->serial->print("\r");
}
void phUnit::calHigh(float pH) {
  SerialUSB.print("Calibrating high with ");
  SerialUSB.println(pH);
  this->serial->print("Cal,high,");
  this->serial->print(pH);
  this->serial->print("\r");
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

void phUnit::ContinousReadMode(char mode) {
  if (mode == '1') {
    this->serial->print("C,1");
    this->serial->print("\r");
  }
  if (mode == '0') {
    this->serial->print("C,0");
    this->serial->print("\r");
  }

  if (mode == '?') {
    this->serial->print("C,?");
    this->serial->print("\r");
  }

}

float phUnit::getpH(void) {
  this->serial->print("R");
  this->serial->print("\r");
  if (serial->available() > 0) {
    this->from_pH_meter = this->serial->readStringUntil('\r');
    this->pH_value = from_pH_meter.toFloat();
    return this->pH_value;
  }
}

void phUnit::Calibrate(CalibMode *CalMode) {
  this->CalMode = CalMode;
}

void phUnit::setCalibMode(CalibMode *CalMode) {
  this->CalMode = CalMode;
}

bool phUnit::isCalibrated(void) {

  return this->_isCalibrated;

}




