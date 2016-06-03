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
        this->rMode = Continous;
      case 2:
        this->rMode = Dosing;
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


  if (this->isRunning == false)
  {
    analogWrite(this->pwm_pin, _setPwm);
    lastPass = millis();
    this->isRunning = true;
  }

  if (this->isRunning == true)
  {
    if (this->_setDir == 1)
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
  this->calibration_status = init;
  this->input_cal = "";

  SerialUSB.println("Please put the hoe in an empty waste container and");
  SerialUSB.println("press OK and when ready. The pump will pump all");
  SerialUSB.println("the air out. Press stop when no air is coming");
  SerialUSB.println("out.");
  SerialUSB.print('\n');
  
  while (this->calibration_status == init)
  {

    loop();

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
      break;
    }
    if (this->input_cal == "cancel")
    {
      SerialUSB.println("Canceling calibration");
      this->input_cal = "";
      return;
    }
  }

  SerialUSB.print('\n');
  SerialUSB.println("Please put the hoe in to an cylindrical flask and");
  SerialUSB.println("press ok to start pumping for 60 seconds.");


  while (this->calibration_status == pump60sec_1)
  {
    loop();

    if (this->input_cal == "ok")
    {
      this->setPwm(20);
      this->on();
      delay(200);
      SerialUSB.println((millis() - this->lastPass) / 1000);
      if (this->oncePerTime(6000))
      {
        this->off();
        SerialUSB.println("pumped for 60 seconds");
        input_cal = "";
        break;
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


