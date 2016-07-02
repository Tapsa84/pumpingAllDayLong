#pragma once
#ifndef phUnit_h
#define phUnit_h
#include "HardwareSerial.h"

class phUnit {


  private:

    float pH_value;
    float _getTemp;
    float _setTemp;
    
    
    
    String from_pH_meter = "";
    String from_host = "";
    enum CalibMode {hi, low};
    CalibMode *CalMode;
    HardwareSerial  *serial;



  public:

    boolean _isCalibrated = true;
    boolean isCalibratingHigh = false;
    boolean isCalibratingLow = false;
    boolean isCalibratingTri = false;
    boolean _isReading = false;
    boolean _cont_read_mode = false;
    
    phUnit(HardwareSerial *serial);

    void queryCal();
    void setTemp(float _setTemp);
    void ContinousReadMode(char mode);
    float getTemp(void);
    float getpH();
    void calMid(float pH);
    void calLow(float pH);
    void calHigh(float pH);
    
    
    bool isCalibrated(void);

    void Calibrate(CalibMode *CalMode);
    void setCalibMode(CalibMode *CalMode);
    



};
#endif

