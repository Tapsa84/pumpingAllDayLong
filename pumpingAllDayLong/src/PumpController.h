#pragma once
#ifndef PumpController_h
#define PumpController_h

#include <Arduino.h>
#include "PumpMotor.h"

class PumpController {
  private:

  public:
    PumpController() {
    }
    PumpController(PumpMotor *motor) {
      this->motor = motor;
    }
    PumpMotor *motor;
    String input_cmd;
    void adjustPh();
    void calflow();
    void calibrate_pump();
};

#endif
