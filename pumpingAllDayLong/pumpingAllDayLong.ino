#include "PumpMotor.h"
#include "phUnit.h"
#include "UnitController.h"
#include "HardwareSerial.h"



PumpMotor pumpA(10,11,12);
PumpMotor pumpB(13,14,15);


//phUnit phUnit2(&Serial2);
phUnit phUnit1(&Serial1);


UnitController Unit1(pumpA,pumpB,phUnit1);

void setup() {
  // put your setup code here, to run once:
  int pin1;
  Unit1._phUnit.serial->begin(9600);
//Unit1.pumpA.setPin1(9);
//pin1 = Unit1.pumpA.getPin1();
//Serial.begin(9600);
//Serial.print(pin1);



}

void loop() {
  // put your main code here, to run repeatedly:

}
