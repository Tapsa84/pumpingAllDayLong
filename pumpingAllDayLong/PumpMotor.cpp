#include "Arduino.h"
#include "PumpMotor.h"


PumpMotor::PumpMotor(int pwm_pin, int dir_pin, int ena_pin) {
  this->pwm_pin = pwm_pin;
  this->dir_pin = dir_pin;
  this->ena_pin = ena_pin;
}

PumpMotor::PumpMotor() {

}

void PumpMotor::getSettings(int rMode, float pump_flow, float y1, float y2) {
  
  if (y1 && y2) {
    this->y1 = y1;
    this->y2 = y2;
    this->calflow();
    switch (rMode) {
      case 1:
      this->runMode = rMode;
      case 2:
      this->runMode = rMode;
    }
  }
  else {
    this->isCalibrated = false;
  }
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


void PumpMotor::on() {
  Serial.println("pump is on");
  this->isRunning = true;
  analogWrite(this->ena_pin, 1);
  analogWrite(this->dir_pin, _setDir);
  analogWrite(this->pwm_pin, _setPwm);
  

}

void  PumpMotor::off() {
  this->isRunning = false;
  analogWrite(this->ena_pin, 0);
  analogWrite(this->pwm_pin, 0);
  Serial.println("pump is off");
}

bool PumpMotor::isOn(void) {
  
  return this->isRunning;
  
}

void PumpMotor::setRunMode() {
  this->rMode = rMode;
}



void PumpMotor::toggle() {
  if (this->isOn()) {
    //Serial.println("pump off");
    this->off();
  } 
  else {
    //Serial.println("pump on");
    this->on();
  }
    
    
  }


void PumpMotor::calibrate() {
  this->off();
}

bool PumpMotor::isCalib() {
  return this->isCalibrated;
}


 void PumpMotor::calflow() {
  this->slope = (y2 - y1) / (220 - 20);
  this->yintercept = this->y1 - (this->slope * 20);
  this->_setPwm = (this->pump_flow - this->yintercept) / slope;
  this->isCalibrated = true;
}

void PumpMotor::setPumpTime(int pump_time) {
  this->pump_time = pump_time;
}

bool PumpMotor::oncePerTime() {
  
  if (millis() > this->lastPass + this->pump_time) {
    this->lastPass = millis();
    return true;
  }
  return false;
}

