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

    boolean _isCalibrating = false;
    boolean _isReading = false;
    boolean _cont_read_mode = false;
    phUnit(HardwareSerial *serial);
    phUnit();

    void setTemp(float _setTemp);
    void ContinousReadMode(char mode);
    float getTemp(void);
    float getpH();
    
    
    bool isCalibrated(void);

    void Calibrate(CalibMode *CalMode);
    void setCalibMode(CalibMode *CalMode);
    



};
#endif

