#include <Arduino.h>
#include "PumpMotor.h"


PumpMotor::PumpMotor(int pwm_pin, int dir_pin, int ena_pin) {
  this->pwm_pin = pwm_pin;
  this->dir_pin = dir_pin;
  this->ena_pin = ena_pin;
  this->pwm = 0;
}

int PumpMotor::getPwm() {
  return this->pwm;
}

void PumpMotor::setPwm(int pwm) {
  this->pwm = pwm;

}

void PumpMotor::set_direction(int direction) {
  if (direction == 1)
  {
    digitalWrite(this->ena_pin, 1);
    digitalWrite(this->dir_pin, 0);
  }
  else
  {
    digitalWrite(this->ena_pin, 0);
    digitalWrite(this->dir_pin, 1);
  }
}

void PumpMotor::on() {
  if (this->isOff()) {
    Serial.println("pump was not on");
    analogWrite(this->pwm_pin, this->pwm);
    this->isRunning = true;
  }
}

void  PumpMotor::off() {
  this->isRunning = false;
  analogWrite(this->pwm_pin, 0);
  Serial.println("pump is off");
}

bool PumpMotor::isOn() {
  return this->isRunning;
}

bool PumpMotor::isOff() {
  return !this->isRunning;
}
