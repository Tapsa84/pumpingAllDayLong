#pragma once
#ifndef PumpMotor_h
#define PumpMotor_h


class PumpMotor {


    private:
         int pin1;
         int pin2;
         int pin3;

         public:

         PumpMotor(int pin1, int pin2, int pin3);
         PumpMotor();
         void setPin1(int pin1);
         int getPin1(void);

         
};

#endif
