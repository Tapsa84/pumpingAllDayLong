#include "Arduino.h"
#include "PumpMotor.h"

PumpMotor::PumpMotor(int pin1, int pin2, int pin3) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pin3 = pin3;
}

PumpMotor::PumpMotor(){

}

void PumpMotor::setPin1(int pin1) {
  this->pin1 = pin1;
}

int PumpMotor::getPin1(void) {
  return pin1;
}

