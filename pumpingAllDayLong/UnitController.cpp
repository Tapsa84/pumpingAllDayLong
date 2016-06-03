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


  /*
    if (this->pH_dir == up)
    {


    if (this->pumpB->rMode == this->pumpB->RunMode::Dosing)
    {
      if (this->pumpB->isOn())
      {
        if (this->dummy_pH < this->desired_pH - 0.1) {
          if (this->pumpB->oncePerTime()) {
            this->lastPass = millis();
            this->lastPassA = millis();
            this->pumpB->pump_time = this->pumpB->pump_time * 1.1;
            this->pumpB->toggle();
            Serial.println("pH under desired value, adding more pump time");
            Serial.println(this->pumpB->pump_time);

          }
        }

        if (this->dummy_pH > this->desired_pH + 0.1) {
          if (this->pumpB->oncePerTime()) {
            this->lastPass = millis();
            this->lastPassA = millis();
            this->pumpB->pump_time = this->pumpB->pump_time * 0.9;
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
    else
    {
      this->pumpB->on();
    }
    }

    if (this->pH_dir == down)
    {
    if (this->pumpB->isOn())
    {
      if (this->dummy_pH > this->desired_pH + 0.1) {
        if (this->pumpB->oncePerTime()) {
          this->lastPass = millis();
          this->lastPassA = millis();
          this->pumpB->pump_time = this->pumpB->pump_time * 1.1;
          this->pumpB->toggle();
          Serial.println("pH under desired value, adding more pump time");
          Serial.println(this->pumpB->pump_time);

        }
      }

      if (this->dummy_pH < this->desired_pH - 0.1) {
        if (this->pumpB->oncePerTime()) {
          this->lastPass = millis();
          this->lastPassA = millis();
          this->pumpB->pump_time = this->pumpB->pump_time * 0.9;
          this->pumpB->toggle();
          Serial.println("pH over desired value, subtracting pump time");
          Serial.println(this->pumpB->pump_time);
        }
=======
  if (this->pH_dir == up) {
    bool turnPumpBOff = this->pumpB->isOn() && this->pumpB->oncePerTime();
    if (turnPumpBOff) {
      this->lastPass = millis();
      this->lastPassA = millis();
      this->pumpB->off();
      bool phTooLow = this->dummy_pH < this->desired_pH - 0.1;
      bool phTooHigh = this->dummy_pH > this->desired_pH + 0.1;

      if (phTooLow) {
        Serial.println("pH under desired value, adding more pump time");
        this->pumpB->pump_time = this->pumpB->pump_time * 1.1;
      }

      if (phTooHigh) {
        Serial.println("pH over desired value, subtracting pump time");
        this->pumpB->pump_time = this->pumpB->pump_time * 0.9;
>>>>>>> origin/master
      }
      Serial.println(this->pumpB->pump_time);
    }

<<<<<<< HEAD
    if (!this->pumpB->isOn()) {
      if (this->timeStall()) {
        Serial.println(millis() - this->lastPassA);
        Serial.println("Waiting 1 second to equiblirate");
        //if (this->dummy_pH < this->desired_pH - 0.1) {
        this->pumpB->toggle();
        // }

      }
=======
    bool turnPumpBOn = !this->pumpB->isOn() && this->timeStall();
>>>>>>> origin/master

    if (turnPumpBOn) {
      Serial.println(millis() - this->lastPassA);
      Serial.println("Waiting 1 second to equiblirate");
      this->pumpB->toggle();
    }
    }
    }

    /*
    if (this->controller_state == off)
    {

    }

    if (this->controller_state == pumpA_cal)
    {

    }

    if (this->controller_state == pumpB_cal)
    {

    }

    if (this->controller_state == ph_cal)
    {

    }


    this->getDummy_pH();

    if (this->pH_dir == up)
    {
    if (this->pumpB->isOn())
    {
    if (this->dummy_pH < this->desired_pH - 0.1) {
      if (this->pumpB->oncePerTime()) {
        this->lastPass = millis();
        this->lastPassA = millis();
        this->pumpB->pump_time = this->pumpB->pump_time * 1.1;
        this->pumpB->toggle();
        Serial.println("pH under desired value, adding more pump time");
        Serial.println(this->pumpB->pump_time);

      }
    }

    if (this->dummy_pH > this->desired_pH + 0.1) {
      if (this->pumpB->oncePerTime()) {
        this->lastPass = millis();
        this->lastPassA = millis();
        this->pumpB->pump_time = this->pumpB->pump_time * 0.9;
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
  */
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



