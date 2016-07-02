#include "PumpController.h"
#include "TriggerTimer.h"

class BasePumpController : public PumpController {

private:


  TriggerTimer pump60sec = TriggerTimer();

  float y1 = 0;
  float y2 = 0;
  int pump_flow = 17;
  int _setDir = 0;
  float yintercept = 0;
  float slope = 0;
  int _setPwm = 0;
  boolean isCalibrated = false;

public:

  enum Cal_state {air,pump1,pump2,getY1,getY2};
  Cal_state cal_state = air;
  
  boolean isCalibrating = false;

  enum RunMode {Continous, Dosing, Custom};
  RunMode rMode = Continous;

  BasePumpController(PumpMotor *motor) : PumpController(motor){
    this->pump60sec.setTriggerTime(60000);
  }

  bool isCalib() {
    return this->isCalibrated;
  }

  void setSettings(int rMode, float y1, float y2, int _setDir, int pump_flow) {
    switch (rMode) {
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

    if (y1 != 0 && y2 != 0) {
      this->calflow();
    } else {
      this->isCalibrated = false;
    }

    this->_setDir = _setDir;

    if (pump_flow != 0) {
      this->pump_flow = pump_flow;
    }
  }

  void calflow() {
    this->slope = (this->y2 - this->y1) / (220 - 150);
    this->yintercept = this->y1 - (this->slope * 150);
    this->_setPwm = (this->pump_flow - this->yintercept) / slope;
    SerialUSB.println(_setPwm);
    this->isCalibrated = true;
  }

  void calibrate_pump() {
    if (this->cal_state == air) {
      if (input_cmd == "ok") {
        SerialUSB.println("Starting to pump air out");
        this->motor->setPwm(150);
        this->motor->on();
        input_cmd = "";
      }
      if (input_cmd == "stop") {
        SerialUSB.println("Stopping pump");
        this->motor->off();
        input_cmd = "";
        this->cal_state = pump1;
      }
    }

    if (this->cal_state == pump1) {
      if (input_cmd == "ok") {
        SerialUSB.println("Starting to pump for 1 minute");
        this->motor->setPwm(150);
        this->motor->on();
        input_cmd = "pump";
        this->pump60sec.reset();
      }
      if (this->pump60sec.isTriggered() && input_cmd == "pump") {
        this->motor->off();
        SerialUSB.println("Pumped for 1 minute,");
        SerialUSB.println("please type the amount pumped.");
        this->cal_state = getY1;
        input_cmd = "";
      }
    }

    if (this->cal_state == getY1) {
      if (input_cmd != "") {
        SerialUSB.println("Saving " + input_cmd + "ml to memory");
        this->y1 = input_cmd.toFloat();
        input_cmd = "";
        this->cal_state = pump2;
      }
    }

    if (this->cal_state == pump2) {
      if (input_cmd == "ok") {
        SerialUSB.println("Starting to pump for 1 minute");
        this->motor->setPwm(220);
        this->motor->on();
        input_cmd = "pump";
        this->pump60sec.reset();
      }
      if (this->pump60sec.isTriggered() && input_cmd == "pump") {
        this->motor->off();
        SerialUSB.println("Pumped for 1 minute, please type");
        SerialUSB.println("the amount pumped.");
        this->cal_state = getY2;
        input_cmd = "";

      }
    }

    if (this->cal_state == getY2) {
      if (input_cmd != "") {
        SerialUSB.println("Saving " + input_cmd + "ml to memory");
        this->y2 = input_cmd.toFloat();
        this->cal_state = air;
        this->isCalibrating = false;
        input_cmd = "";
        this->calflow();
        return;
      }
    }

  }
};
