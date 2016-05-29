#include "Arduino.h"
#include "UnitController.h"
#include "phUnit.h"
#include "PumpMotor.h"
#include "HardwareSerial.h"






UnitController::UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit) {
  this->pumpA = pumpA;
  this->pumpB = pumpB;
  this->_phUnit = _phUnit;

}

UnitController::UnitController() {

}

bool UnitController::timeStall() {

  if (millis() > this->lastPass + stall_time) {
    this->lastPass = millis();
    return true;
  }
  return false;
}

void UnitController::start() {
  if (this->pumpA->isOn()) {
    return;
  }
  else {
    this->pumpA->on();
  }
  if (this->pumpB->isOn()) {
    return;
  }
  else {
    this->pumpB->on();
  }
}

float UnitController::getDummy_pH(void) {
  return this->dummy_pH;
}

void UnitController::tick() {


  this->getDummy_pH();

  if (this->pH_dir == up) {
    if (this->pumpB->isOn()) {
      if (this->dummy_pH < this->desired_pH - 0.1) {
        if (this->pumpB->oncePerTime()) {
          this->lastPass = millis();
          this->lastPassA = millis();
          this->pumpB->pump_time = this->pumpB->pump_time *1.1;
          this->pumpB->toggle();
          Serial.println("pH under desired value, adding more pump time");
          Serial.println(this->pumpB->pump_time);
          
        }
      }

      if (this->dummy_pH > this->desired_pH + 0.1) {
        if (this->pumpB->oncePerTime()) {
          this->lastPass = millis();
          this->lastPassA = millis();
          this->pumpB->pump_time = this->pumpB->pump_time *0.9;
          this->pumpB->toggle();
          Serial.println("pH over desired value, subtracting pump time");
          Serial.println(this->pumpB->pump_time);
        }
      }
    }

    if (!this->pumpB->isOn()) {
      if (this->timeStall()) {
        Serial.println(millis() - this->lastPassA);
        Serial.println("Waiting 1 second to equiblirate");
        //if (this->dummy_pH < this->desired_pH - 0.1) {
          this->pumpB->toggle();
       // }

      }

    }
  }

}









bool UnitController::calCheck() {
  if (this->_phUnit->isCalibrated()) {
    if (this->pumpA->isCalib()) {
      if (this->pumpB->isCalib()) {
        Serial.println("Everything calibrated");
        return true;
      }
      else {
        Serial.println("Please calibrate pump B before starting");
        return false;

      }
    }
    else {
      Serial.println("Please calibrate pump A before starting");
      return false;
    }
  }
  else {
    Serial.println("Please calibrate phUnit before starting");
    return false;
  }
}


