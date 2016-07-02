#pragma once
#ifndef UnitController_h
#define UnitController_h
#include "PumpMotor.h"
#include "PumpController.h"
#include "phUnit.h"
#include "PhAdjustingPumpController.cpp"


struct Unit_Settings {
    float desired_pH = 8.5;
    float setTemp = 25;
    int timeStall = 5500;
};

class UnitController {

  private:
    String unit_name = "";
    float low_pH = 0;
    float mid_pH = 0;
    float high_pH = 0;
  public:


    boolean stall_complete = true;
    String input_cmd = "";
    int lastPass = 0;
    String from_ph_meter = "";
    enum Controller_state {on, off, cal_pumpA, cal_pumpB, cal_pH};
    Controller_state controller_state = off;
    void setMeasuredPh(float measuredPh);

    enum ph_Cal_state {init_mid,init_low,init_high, cal_mid, cal_low, cal_high, get_pH_mid, get_pH_low, get_pH_high};
    ph_Cal_state ph_cal_state = init_mid;

    PhAdjustingPumpController *pumpA;
    PhAdjustingPumpController *pumpB;
    phUnit *_phUnit;
    Unit_Settings *unit_settings;

    enum pHdirection {up, down};
    pHdirection pH_dir = up;


    UnitController(PhAdjustingPumpController *pumpA, PhAdjustingPumpController *pumpB, phUnit *_phUnit, String unit_name, Unit_Settings *unit_settings);
    void setSettings(Unit_Settings *unit_settings);
    void calibrate_phUnit(phUnit *phunit);
    bool calCheck();
    void start();
    void tick();
    void unit_off();
};

#endif
