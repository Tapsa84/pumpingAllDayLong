#include "TriggerTimer.h"
#include "BasePumpController.cpp"

class PhAdjustingPumpController : public BasePumpController {

private:
  TriggerTimer pumpingFinishedTimer = TriggerTimer();
  TriggerTimer phReadDelayTimer = TriggerTimer();
  int readDelay = 0;
  int desiredPh = 0;
  int pump_time = 1000;
  boolean adjustPumpTime = false;

public:

  float measuredPh = -1;
  enum pHdirection {up, down};
  pHdirection pH_dir = up;

  PhAdjustingPumpController(PumpMotor *motor) :BasePumpController(motor) {
  }

  void adjustPh() {
    if (this->rMode == this->RunMode::Continous) {
      this->motor->on();
      return ;
    }

    boolean down = this->pH_dir == down;

    boolean overTargetPh = down ?
                  this->measuredPh > this->desiredPh :
                  this->measuredPh < this->desiredPh;

    boolean notOverTargetPh = !overTargetPh;

    boolean overTargetPhHysteresisWhilePumping = down ?
                  this->measuredPh >= this->desiredPh + 0.05 :
                  this->measuredPh <= this->desiredPh - 0.05;

    boolean phUnderSetPoint = down ?
                  this->measuredPh >= this->desiredPh - 0.01 :
                  this->measuredPh <= this->desiredPh - 0.01;

    if (this->motor->isOn()) {
      if (overTargetPh) {
        if (pumpingFinishedTimer.isTriggered()) {
          adjustPumpTime = true;
          this->motor->off();
          this->phReadDelayTimer.reset();
        }
      }

      if (overTargetPhHysteresisWhilePumping) {
        adjustPumpTime = false;
        this->pump_time = this->pump_time / 2;
        pumpingFinishedTimer.setTriggerTime(this->pump_time);
        this->motor->off();
        this->phReadDelayTimer.reset();
        SerialUSB.println("pH is over hysteresis limit while pumping");
      }
    }

    if (!this->motor->isOn()) {
      if (this->phReadDelayTimer.isTriggered()) {
        if (this->adjustPumpTime) {
          if (notOverTargetPh) {
            this->pump_time = this->pump_time * 0.98;
            pumpingFinishedTimer.setTriggerTime(this->pump_time);
            this->adjustPumpTime = false;
            SerialUSB.println("pH over desired value, subtracting pump time");
          }
          if (overTargetPh) {
            this->pump_time = this->pump_time * 1.02;
            pumpingFinishedTimer.setTriggerTime(this->pump_time);
            this->adjustPumpTime = false;
            SerialUSB.println("pH under desired value, adding more pump time");
          }
        }
        if (phUnderSetPoint) {
          SerialUSB.println("Switching pump on");
          this->motor->on();
          pumpingFinishedTimer.reset();
        }
      }
    }
  }
};
