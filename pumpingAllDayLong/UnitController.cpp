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


void UnitController::adjust_pH(PumpMotor *pump) {
  
  if (this->pH_dir == up)
  {
    bool increasePumpTime = this->dummy_pH < this->desired_pH - 0.1;
    if (pump->rMode == pump->RunMode::Dosing)
    {
      //SerialUSB.println("Here I am! UP");
      if (pump->isOn())
      {
        if (this->dummy_pH < this->desired_pH - 0.1) {
          if (pump->oncePerTime()) {
            this->lastPass = millis();
            this->lastPassA = millis();
            pump->pump_time = pump->pump_time * 1.1;
            pump->toggle();
            SerialUSB.println("pH under desired value, adding more pump time");
            SerialUSB.println(pump->pump_time);

          }
        }

        if (this->dummy_pH > this->desired_pH + 0.1) {
          if (pump->oncePerTime()) {
            this->lastPass = millis();
            this->lastPassA = millis();
            pump->pump_time = pump->pump_time * 0.9;
            pump->toggle();
            SerialUSB.println("pH over desired value, subtracting pump time");
            SerialUSB.println(pump->pump_time);
          }
        }
      }

      if (!pump->isOn()) {
        if (this->timeStall()) {
          SerialUSB.println(millis() - this->lastPassA);
          SerialUSB.println("Waiting 1 second to equiblirate");
          //if (this->dummy_pH < this->desired_pH - 0.1) {
          pump->toggle();
          // }

        }
      }
    }
    else
    {
      pump->on();
    }
  }

  if (this->pH_dir == down)
  {
    
    if (pump->rMode == pump->RunMode::Dosing)
    {
      
      if (pump->isOn())
      {
        if (this->dummy_pH > this->desired_pH + 0.1) {
          if (pump->oncePerTime()) {
            this->lastPass = millis();
            this->lastPassA = millis();
            pump->pump_time = pump->pump_time * 1.1;
            pump->toggle();
            SerialUSB.println("pH under desired value, adding more pump time");
            SerialUSB.println(pump->pump_time);

          }
        }

        if (this->dummy_pH < this->desired_pH - 0.1) {
          if (pump->oncePerTime()) {
            this->lastPass = millis();
            this->lastPassA = millis();
            pump->pump_time = pump->pump_time * 0.9;
            pump->toggle();
            SerialUSB.println("pH over desired value, subtracting pump time");
            SerialUSB.println(pump->pump_time);
          }
        }
      }

      if (!pump->isOn()) {
        if (this->timeStall()) {
          SerialUSB.println(millis() - this->lastPassA);
          SerialUSB.println("Waiting 1 second to equiblirate");
          //if (this->dummy_pH < this->desired_pH - 0.1) {
          pump->toggle();
          // }

        }
      }
    }
    else
    {
      
      pump->on();
    }
  }
}




void UnitController::tick() {



  if (this->controller_state == on)
  {
    if (this->calCheck())
    {
      this->adjust_pH(this->pumpA);
      this->adjust_pH(this->pumpB);
    }
    else 
    {
      SerialUSB.println("Please check pump and pH calibration.");
      return;
    }
    
  }


 
    if (this->controller_state == off)
    {

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



