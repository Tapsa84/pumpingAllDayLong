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

      if (this->rMode == Continous) {
        SerialUSB.println("Mode is Continous");
      }
      break;

    case 1:
      this->rMode = Dosing;
      if (this->rMode == Dosing) {
        SerialUSB.println("Mode is Dosing");
      }
      break;
  }

  if (this->pump_settings->y1 != 0 && this->pump_settings->y2 != 0) {
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

void PumpMotor::get_input() {
  if (SerialUSB.available() > 0) {
    this->input_cal = SerialUSB.readStringUntil('\n');
  }
}

bool PumpMotor::air_out() {

  get_input();

  if (this->input_cal == "ok") {
    SerialUSB.println("Starting to pump air out, press stop when all");
    SerialUSB.println("the air is out.");
    this->setPwm(200);
    this->on();
    this->input_cal = "";

  }
  if (this->input_cal == "stop") {
    SerialUSB.println("Stopping pump.");
    this->off();
    this->input_cal = "";
    this->calibration_status = pump60sec_1;
    return true;
  }

}

bool PumpMotor::pump60sec(int pwm) {

  get_input();

  if (this->input_cal == "ok") {
    SerialUSB.println("Starting to pump for 1 minute.");
    this->setPwm(pwm);
    this->on();
    this->input_cal = "";

  }
  if (oncePerTime(10000)) {
    this->off();
    return true;
  }
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


