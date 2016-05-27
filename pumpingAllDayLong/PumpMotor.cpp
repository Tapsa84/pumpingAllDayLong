#include "Arduino.h"
#include "PumpMotor.h"

PumpMotor::PumpMotor(int pwm_pin, int direction_pin, int enable_pin) {
  this->pwm_pin = pwm_pin;
  this->direction_pin = direction_pin;
  this->enable_pin = enable_pin;
}

PumpMotor::PumpMotor(){

}

void PumpMotor::setPwm(int _setPwm) {
  this->_setPwm = _setPwm;
}

int PumpMotor::getPwm(void) {
  return _setPwm;
}

