#include "Arduino.h"
#include "PumpMotor.h"

<<<<<<< HEAD
PumpMotor::PumpMotor(int pwm_pin, int dir_pin, int ena_pin) {
  this->pwm_pin = pwm_pin;
  this->dir_pin = dir_pin;
  this->ena_pin = ena_pin;
}

PumpMotor::PumpMotor() {

}

void PumpMotor::getSettings(int _setPwm, int _setDir, int rMode, float pump_flow, float y1, float y2) {
  this->_setPwm = _setPwm;
  this->_setDir = _setDir;
  if (y1 && y2) {
    this->y1 = y1;
    this->y2 = y2;
    this->calflow();
  }
  else {
    this->isCalibrated = false;
  }
=======
PumpMotor::PumpMotor(int pwm_pin, int direction_pin, int enable_pin) {
  this->pwm_pin = pwm_pin;
  this->direction_pin = direction_pin;
  this->enable_pin = enable_pin;
}

PumpMotor::PumpMotor(){

}

void PumpMotor::setPwm(int _setPwm) {
  this->_setPwm = _setPwm;
>>>>>>> refs/remotes/origin/pumpingAllDayLong
}

int PumpMotor::getPwm(void) {
  return _setPwm;
}

<<<<<<< HEAD
void PumpMotor::setPwm(int _setPwm) {
  this->_setPwm = _setPwm;
}

void PumpMotor::set_direction(int new_dir) {
  this->_setDir = new_dir;
}

void PumpMotor::setRunMode() {
  this->rMode = rMode;

}

void PumpMotor::on() {

  this->isRunning = true;
  analogWrite(this->ena_pin, 1);
  analogWrite(this->dir_pin, _setDir);
  analogWrite(this->pwm_pin, _setPwm);

}

void  PumpMotor::off() {
  this->isRunning = false;
  analogWrite(this->ena_pin, 0);
  analogWrite(this->pwm_pin, 0);
}

bool PumpMotor::isOn() {
  return this->isRunning;
}

void PumpMotor::toggle() {
  if (this->rMode == Continous) {
    return;
  }
  if (this->rMode == Dosing) {
    this->off();
  }
}

void PumpMotor::calibrate() {
  this->off();


} void PumpMotor::calflow() {
  this->slope = (y2 - y1) / (220 - 20);
  this->yintercept = this->y1 - (this->slope * 20);
  this->_setPwm = (this->pump_flow - this->yintercept) / slope;
  this->isCalibrated = true;
}

void PumpMotor::setPumpTime(float pump_time) {
  this->pump_time = pump_time;
}

bool PumpMotor::oncePerTime() {
  if(millis() > lastPass + this->pump_time) {
    this->lastPass = millis();
    return true;
  }
  return false;
}
=======
>>>>>>> refs/remotes/origin/pumpingAllDayLong
