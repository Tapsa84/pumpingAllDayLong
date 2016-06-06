#include "Arduino.h"
#include "UnitController.h"
#include "phUnit.h"
#include "PumpMotor.h"
#include "HardwareSerial.h"

UnitController::UnitController(PumpMotor *pumpA, PumpMotor *pumpB, phUnit *_phUnit, String unit_name) {
  this->pumpA = pumpA;
  this->pumpB = pumpB;
  this->_phUnit = _phUnit;
  this->unit_name = unit_name;

}

void UnitController::unit_off() {
  this->pumpA->off();
  this->pumpB->off();

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

  // eli iffin sisällöt tänne.
  bool phTooHigh = this->dummy_pH < this->desired_pH - 0.1;
  bool phTooLow = this->dummy_pH > this->desired_pH + 0.1;

  if (this->pH_dir == up)
  {

    bool increasePumpTime = this->dummy_pH < this->desired_pH - 0.1;


    if (pump->rMode == pump->RunMode::Dosing)
    {
      //SerialUSB.println("Here I am! UP");
      if (pump->isOn())
      {
        if (phTooHigh) {
          if (pump->oncePerTime()) {
            this->lastPass = millis();
            this->lastPassA = millis();
            pump->pump_time = pump->pump_time * 1.1;
            pump->toggle();
            SerialUSB.println("pH under desired value, adding more pump time");
            SerialUSB.println(pump->pump_time);

          }
        }

        if (phTooLow) {
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


void UnitController::get_input() {
  if (SerialUSB.available() > 0) {
    this->input_cmd = SerialUSB.readStringUntil('\n');
  }
}





void UnitController::calibrate_phUnit(phUnit *phunit) {

  if (phunit->isCalibratingHigh == true) {
    
    if (this->ph_cal_state == init_mid) {
      SerialUSB.println("Please enter mid point pH:");
      input_cmd = "";
      this->ph_cal_state = get_pH_mid;
    }

    if (this->ph_cal_state == get_pH_mid) {
      if (input_cmd != "") {
        this->mid_pH = this->input_cmd.toFloat();
        SerialUSB.println("Saving " + input_cmd + " as midpoint");
        SerialUSB.println("Put the meter in the standard and once");
        SerialUSB.println("the pH has stabilized, type ok.");
        input_cmd = "";
        phunit->ContinousReadMode('1');
        this->ph_cal_state = cal_mid;
        
      }
    }

    if(this->ph_cal_state == cal_mid){
      if(input_cmd == "ok") {
        phunit->calMid(this->mid_pH);
        SerialUSB.println("Midpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_high;
        
      }
    }

    if (this->ph_cal_state == init_high) {
      SerialUSB.println("Please enter highpoint pH:");
      input_cmd = "";
      this->ph_cal_state = get_pH_high;
    }

    if (this->ph_cal_state == get_pH_high) {
      if (input_cmd != "") {
        this->high_pH = this->input_cmd.toFloat();
        SerialUSB.println("Saving " + input_cmd + " as highpoint");
        SerialUSB.println("Put the meter in the standard and once");
        SerialUSB.println("the pH has stabilized, type ok.");
        input_cmd = "";
        phunit->ContinousReadMode('1');
        this->ph_cal_state = cal_high;
        
      }
    }

    if(this->ph_cal_state == cal_high){
      if(input_cmd == "ok") {
        phunit->calHigh(this->high_pH);
        SerialUSB.println("Highpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_mid;
        phunit->isCalibratingHigh = false;
        
      }
    }
}

if (phunit->isCalibratingLow = true) {
    
    if (this->ph_cal_state == init_mid) {
      SerialUSB.println("Please enter mid point pH:");
      input_cmd = "";
      this->ph_cal_state = get_pH_mid;
    }

    if (this->ph_cal_state == get_pH_mid) {
      if (input_cmd != "") {
        this->mid_pH = this->input_cmd.toFloat();
        SerialUSB.println("Saving " + input_cmd + " as midpoint");
        SerialUSB.println("Put the meter in the standard and once");
        SerialUSB.println("the pH has stabilized, type ok.");
        input_cmd = "";
        phunit->ContinousReadMode('1');
        this->ph_cal_state = cal_mid;
        
      }
    }
    
    if(this->ph_cal_state == cal_mid){
      if(input_cmd == "ok") {
        phunit->calMid(this->mid_pH);
        SerialUSB.println("Midpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_low;
        
      }
    }

    if (this->ph_cal_state == init_low) {
      SerialUSB.println("Please enter lowpoint pH:");
      input_cmd = "";
      this->ph_cal_state = get_pH_low;
    }

    if (this->ph_cal_state == get_pH_low) {
      if (input_cmd != "") {
        this->low_pH = this->input_cmd.toFloat();
        SerialUSB.println("Saving " + input_cmd + " as lowpoint");
        SerialUSB.println("Put the meter in the standard and once");
        SerialUSB.println("the pH has stabilized, type ok.");
        input_cmd = "";
        phunit->ContinousReadMode('1');
        this->ph_cal_state = cal_low;
        
      }
    }

    if(this->ph_cal_state == cal_low){
      if(input_cmd == "ok") {
        phunit->calHigh(this->low_pH);
        SerialUSB.println("Lowpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_mid;
        phunit->isCalibratingLow = false;
        
      }
    }
  }

  if (phunit->isCalibratingTri = true) {
    
    if (this->ph_cal_state == init_mid) {
      SerialUSB.println("Please enter mid point pH:");
      input_cmd = "";
      this->ph_cal_state = get_pH_mid;
    }

    if (this->ph_cal_state == get_pH_mid) {
      if (input_cmd != "") {
        this->mid_pH = this->input_cmd.toFloat();
        SerialUSB.println("Saving " + input_cmd + " as midpoint");
        SerialUSB.println("Put the meter in the standard and once");
        SerialUSB.println("the pH has stabilized, type ok.");
        input_cmd = "";
        phunit->ContinousReadMode('1');
        this->ph_cal_state = cal_mid;
        
      }
    }

    if(this->ph_cal_state == cal_mid){
      if(input_cmd == "ok") {
        phunit->calMid(this->mid_pH);
        SerialUSB.println("Midpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_high;
        
      }
    }

    if (this->ph_cal_state == init_high) {
      SerialUSB.println("Please enter highpoint pH:");
      input_cmd = "";
      this->ph_cal_state = get_pH_high;
    }

    if (this->ph_cal_state == get_pH_high) {
      if (input_cmd != "") {
        this->high_pH = this->input_cmd.toFloat();
        SerialUSB.println("Saving " + input_cmd + " as highpoint");
        SerialUSB.println("Put the meter in the standard and once");
        SerialUSB.println("the pH has stabilized, type ok.");
        input_cmd = "";
        phunit->ContinousReadMode('1');
        this->ph_cal_state = cal_high;
        
      }
    }

    if(this->ph_cal_state == cal_high){
      if(input_cmd == "ok") {
        phunit->calHigh(this->high_pH);
        SerialUSB.println("Highpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_low;
        phunit->isCalibratingHigh = false;
        
      }
    }
    
    if (this->ph_cal_state == init_low) {
      SerialUSB.println("Please enter lowpoint pH:");
      input_cmd = "";
      this->ph_cal_state = get_pH_low;
    }

    if (this->ph_cal_state == get_pH_low) {
      if (input_cmd != "") {
        this->low_pH = this->input_cmd.toFloat();
        SerialUSB.println("Saving " + input_cmd + " as lowpoint");
        SerialUSB.println("Put the meter in the standard and once");
        SerialUSB.println("the pH has stabilized, type ok.");
        input_cmd = "";
        phunit->ContinousReadMode('1');
        this->ph_cal_state = cal_low;
        
      }
    }

    if(this->ph_cal_state == cal_low){
      if(input_cmd == "ok") {
        phunit->calHigh(this->low_pH);
        SerialUSB.println("Lowpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_mid;
        phunit->isCalibratingTri = false;
        
      }
    }
  }

}

void UnitController::calibrate_pump(PumpMotor *pump) {




  if (this->cal_state == air) {
    if (input_cmd == "ok") {
      SerialUSB.println("Starting to pump air out");
      pump->setPwm(20);
      pump->on();
      input_cmd = "";
    }
    if (input_cmd == "stop") {
      SerialUSB.println("Stopping pump");
      pump->off();
      input_cmd = "";
      this->cal_state = pump1;
    }
  }

  if (this->cal_state == pump1) {
    if (input_cmd == "ok") {
      SerialUSB.println("Starting to pump for 1 minute");
      pump->setPwm(20);
      pump->on();
      input_cmd = "pump";

    }
    if (pump->oncePerTime(6000) && input_cmd == "pump") {
      pump->off();
      SerialUSB.println("Pumped for 1 minute,");
      SerialUSB.println("please type the amount pumped.");
      this->cal_state = getY1;
      input_cmd = "";
    }
  }

  if (this->cal_state == getY1) {
    if (input_cmd != "") {
      SerialUSB.println("Saving " + input_cmd + "ml to memory");
      pump->pump_settings->y1 = input_cmd.toFloat();
      input_cmd = "";
      this->cal_state = pump2;
    }
  }

  if (this->cal_state == pump2) {
    if (input_cmd == "ok") {
      SerialUSB.println("Starting to pump for 1 minute");
      pump->setPwm(200);
      pump->on();
      input_cmd = "pump";
    }
    if (pump->oncePerTime(6000) && input_cmd == "pump") {
      pump->off();
      SerialUSB.println("Pumped for 1 minute, please type");
      SerialUSB.println("the amount pumped.");
      this->cal_state = getY2;
      input_cmd = "";
    }
  }

  if (this->cal_state == getY2) {
    if (input_cmd != "") {
      SerialUSB.println("Saving " + input_cmd + "ml to memory");
      pump->pump_settings->y2 = input_cmd.toFloat();
      this->cal_state = air;
      pump->isCalibrating = false;
      input_cmd = "";
      pump->calflow();
      return;
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
      if (this->timeStall()) {
        SerialUSB.println("Please check pump and pH calibration.");
        return;
      }

    }

  }

  if (this->controller_state == off)
  {
    if (this->pumpA->isCalibrating) {
      this->calibrate_pump(pumpA);
    }
    if (this->pumpB->isCalibrating) {
      this->calibrate_pump(pumpB);
    }
    if (this->_phUnit->isCalibratingHigh) {
      this->calibrate_phUnit(_phUnit);
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



