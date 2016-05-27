#pragma once
#ifndef PumpMotor_h
#define PumpMotor_h


class PumpMotor {


    private:
         int pwm_pin;
         int direction_pin = 1;
         int enable_pin = 0;

         int _setPwm = 0;

         public:

         PumpMotor(int pwm_pin, int direction_pin, int enable_pin);
         PumpMotor();
         void setPwm(int _setPwm);
         int getPwm(void);

         
};

#endif
