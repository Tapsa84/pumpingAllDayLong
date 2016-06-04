#include "Arduino.h"
#include "PumpMotor.h"


PumpMotor::PumpMotor(int pwm_pin, int dir_pin, int ena_pin) {
  this->pwm_pin = pwm_pin;
  this->dir_pin = dir_pin;
  this->ena_pin = ena_pin;
}


void PumpMotor::setSettings(Pump_Settings *pump_settings) {

  this->pump_settings = pump_settings;

  switch (this->pump_settings->rMode) {
      case 0:
        this->rMode = Continous;
        
        if(this->rMode == Continous){
          SerialUSB.println("Mode is Continous");        
        }
        break;
        
      case 1:
        this->rMode = Dosing;
        if(this->rMode == Dosing){
          SerialUSB.println("Mode is Dosing");
        }
        break;
    }
  
  if (this->pump_settings->y1 != 0 && this->pump_settings->y2 !=0) {
    this->calflow();    
  }
  else {
    this->isCalibrated = false;
  }

  switch (this->pump_settings->_setDir) {
    case 0:
      this->_setDir = _setDir;
      break;
    case 1:
      this->_setDir = _setDir;
  }
}




int PumpMotor::getPwm(void) {
  return _setPwm;
}

void PumpMotor::setPwm(int _setPwm) {
  this->_setPwm = _setPwm;

}

void PumpMotor::set_direction(int new_dir) {
  this->pump_settings->_setDir = new_dir;
}


void PumpMotor::on() {

  Serial.println("pump is on");


  if (this->isRunning == false)
  {
    analogWrite(this->pwm_pin, _setPwm);
    lastPass = millis();
    this->isRunning = true;
  }

  if (this->isRunning == true)
  {
    if (this->pump_settings->_setDir == 1)
    {
      analogWrite(this->ena_pin, 1);
      analogWrite(this->dir_pin, 0);
    }
    else
    {
      analogWrite(this->ena_pin, 0);
      analogWrite(this->dir_pin, 1);
    }
  }
}

void  PumpMotor::off() {
  this->isRunning = false;
  analogWrite(this->pwm_pin, 0);
  Serial.println("pump is off");
}

bool PumpMotor::isOn(void) {
  return this->isRunning;
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
  this->calibration_status = init;
  this->input_cal = "";
 
  if (this->calibration_status == init)
  {
    if (this->input_cal == "ok")
    {
      SerialUSB.println("Starting to pump air out.");
      SerialUSB.println("Press stop when no more");
      SerialUSB.println("air is coming out.");
      this->setPwm(200);
      this->on();
      this->input_cal = "";
    }
    if (this->input_cal == "stop")
    {
      SerialUSB.print("Stopping pump.");
      this->off();
      this->calibration_status = pump60sec_1;
      this->input_cal = "";
    }
    if (this->input_cal == "cancel")
    {
      SerialUSB.println("Canceling calibration");
      this->input_cal = "";
      return;
    }
  }

  if (this->calibration_status == pump60sec_1)
  {
    if (this->input_cal == "ok")
    {
      this->setPwm(20);
      this->on();
      if (this->oncePerTime(6000))
      {
        this->off();
        SerialUSB.println("pumped for 60 seconds");
        input_cal = "";
        this->calibration_status = getY1;
      }
    }

    if (this->input_cal == "stop")
    {
      this->off();
      SerialUSB.println("Canceling calibration.");
      input_cal = "";
      return;
    }

    if (this->input_cal == "cancel")
    {
      this->off();
      SerialUSB.println("Canceling calibration.");
      input_cal = "";
      return;
    }
  }


  
  


  SerialUSB.println("Please input the amount of liquid pumped");

}

float getFlow() {

}



bool PumpMotor::isCalib() {
  return this->isCalibrated;
}


void PumpMotor::calflow() {
  this->slope = (this->pump_settings->y2 - this->pump_settings->y1) / (220 - 20);
  this->yintercept = this->pump_settings->y1 - (this->slope * 20);
  this->_setPwm = (this->pump_settings->pump_flow - this->yintercept) / slope;
  this->isCalibrated = true;
}

void PumpMotor::setPumpTime(int pump_time) {
  this->pump_time = pump_time;
}

bool PumpMotor::oncePerTime() {

  if (millis() > this->lastPass + this->pump_time) {
    //this->lastPass = millis();
    return true;
  }
  return false;
}

bool PumpMotor::oncePerTime(int _time) {

  if (millis() > this->lastPass + _time) {
    //this->lastPass = millis();
    return true;
  }
  return false;
}


