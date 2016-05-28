#include "Arduino.h"
#include "PumpMotor.h"

PumpMotor::PumpMotor(int pwm_pin, int dir_pin, int ena_pin) {
  this->pwm_pin = pwm_pin;
  this->dir_pin = dir_pin;
  this->ena_pin = ena_pin;
}

PumpMotor::PumpMotor(){

}

int PumpMotor::getPwm(void) {
  return _setPwm;
}

void PumpMotor::setPwm(int _setPwm) {
  this->_setPwm = _setPwm;
}

void PumpMotor::set_direction(int new_dir) {
  this->_setDir = new_dir;
}

void PumpMotor::setRunMode(RunMode *rMode){
  this->rMode = rMode;
  
}

void PumpMotor::on() {
  
  this->isRunning = true;
  analogWrite(this->ena_pin, 1);
  analogWrite(this->dir_pin, _setDir);
  analogWrite(this->pwm_pin, _setPwm);
  
}

void  PumpMotor::off(){
  this->isRunning = false;
  analogWrite(this->ena_pin, 0);
  analogWrite(this->pwm_pin, 0);  
}

bool isOn(void) {
  return isRunning;
}

