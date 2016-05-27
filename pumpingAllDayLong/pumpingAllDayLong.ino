#include "PumpMotor.h"
#include "phUnit.h"
#include "UnitController.h"
#include "HardwareSerial.h"



PumpMotor *pumpA = new PumpMotor(10, 11, 12);
PumpMotor *pumpB = new PumpMotor(13, 14, 15);
PumpMotor *pumpC = new PumpMotor(16, 17, 18);
PumpMotor *pumpD = new PumpMotor(19, 20, 21);

UnitController *Unit1;
UnitController *Unit2;


phUnit *phUnit1 = new phUnit(&Serial1);
phUnit *phUnit2 = new phUnit(&Serial2);




void setup() {
  Unit1 =  new  UnitController(pumpA, pumpB, phUnit1);
  Unit2 = new UnitController(pumpC, pumpD, phUnit2);
  // put your setup code here, to run once:
  int pin1;
  Unit1->_phUnit->serial->begin(9600);
  //Unit1.pumpA.setPin1(9);
  //pin1 = Unit1.pumpA.getPin1();
  //Serial.begin(9600);
  //Serial.print(pin1);



}

void loop() {
  // put your main code here, to run repeatedly:

}
