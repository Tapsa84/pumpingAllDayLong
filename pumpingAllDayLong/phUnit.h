#pragma once
#ifndef phUnit_h
#define phUnit_h
#include "HardwareSerial.h"

class phUnit {


  private:

    float pH_value;
    float _getTemp;
    float _setTemp;
    boolean _isCalibrated = true;
    String from_pH_meter = "";
    String from_host = "";
    enum CalibMode {hi, low};
    CalibMode *CalMode;
    HardwareSerial  *serial;



  public:

    phUnit(HardwareSerial *serial);
    phUnit();

    void setTemp(float _setTemp);
    float getTemp(void);
    float getpH();
    
    bool isCalibrated(void);

    void Calibrate(CalibMode *CalMode);
    void setCalibMode(CalibMode *CalMode);
    



};
#endif

