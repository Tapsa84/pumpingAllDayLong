#include "Arduino.h"
#include "UnitController.h"
#include "phUnit.h"
#include "PumpMotor.h"
#include "HardwareSerial.h"

UnitController::UnitController(PhAdjustingPumpController *pumpA, PhAdjustingPumpController *pumpB, phUnit *_phUnit, String unit_name, Unit_Settings *unit_settings) {
  this->pumpA = pumpA;
  this->pumpB = pumpB;
  this->_phUnit = _phUnit;
  this->unit_name = unit_name;
  this->unit_settings = unit_settings;

}

void UnitController::unit_off() {
  this->pumpA->motor->off();
  this->pumpB->motor->off();
}

void UnitController::setSettings(Unit_Settings *unit_settings) {
  this->unit_settings = unit_settings;
  this->_phUnit->setTemp(this->unit_settings->setTemp);
}

void UnitController::setMeasuredPh(float measuredPh) {
  this->pumpA->measuredPh = measuredPh;
  this->pumpB->measuredPh = measuredPh;
}

void UnitController::start() {
  if (this->pumpA->motor->isOn()) {
    return;
  }
  else {
    this->pumpA->motor->on();
  }
  if (this->pumpB->motor->isOn()) {
    return;
  }
  else {
    this->pumpB->motor->on();
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

    if (this->ph_cal_state == cal_mid) {
      if (input_cmd == "ok") {
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

    if (this->ph_cal_state == cal_high) {
      if (input_cmd == "ok") {
        phunit->calHigh(this->high_pH);
        SerialUSB.println("Highpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_mid;
        phunit->isCalibratingHigh = false;

      }
    }
  }

  if (phunit->isCalibratingLow == true) {

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

    if (this->ph_cal_state == cal_mid) {
      if (input_cmd == "ok") {
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

    if (this->ph_cal_state == cal_low) {
      if (input_cmd == "ok") {
        phunit->calLow(this->low_pH);
        SerialUSB.println("Lowpoint calibrated");
        input_cmd == "";
        phunit->ContinousReadMode('0');
        this->ph_cal_state = init_mid;
        phunit->isCalibratingLow = false;

      }
    }
  }

  if (phunit->isCalibratingTri == true) {

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

    if (this->ph_cal_state == cal_mid) {
      if (input_cmd == "ok") {
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

    if (this->ph_cal_state == cal_high) {
      if (input_cmd == "ok") {
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

    if (this->ph_cal_state == cal_low) {
      if (input_cmd == "ok") {
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

void UnitController::tick() {
  if (this->controller_state == on) {
    if (this->calCheck()) {
      this->pumpA->adjustPh();
      this->pumpB->adjustPh();
    } else {
      SerialUSB.println("Please check pump and pH calibration.");
      this->controller_state = off;
      return;
    }
  }

  if (this->controller_state == off)
  {
    if (this->pumpA->isCalibrating) {
      this->pumpA->calibrate_pump();
    }
    if (this->pumpB->isCalibrating) {
      this->pumpB->calibrate_pump();
    }
    if (this->_phUnit->isCalibratingHigh) {
      this->calibrate_phUnit(_phUnit);
    }

    if (this->_phUnit->isCalibratingLow) {
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
