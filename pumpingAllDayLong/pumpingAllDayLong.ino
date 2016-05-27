#include "UnitController.h"
#include "PumpMotor.h"
#include "phUnit.h"
#include "HardwareSerial.h"

PumpMotor *pumpA = new PumpMotor(10, 11, 12);
PumpMotor *pumpB = new PumpMotor(13, 14, 15);
PumpMotor *pumpC = new PumpMotor(16, 17, 18);
PumpMotor *pumpD = new PumpMotor(19, 20, 21);
phUnit *phUnit1 = new phUnit(&Serial1);
phUnit *phUnit2 = new phUnit(&Serial2);

UnitController *Unit1 = new UnitController(pumpA, pumpB, phUnit1);
UnitController *Unit2 = new UnitController(pumpC, pumpD, phUnit2);








void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.print("JEE");
  delay(1000);




  // put your setup code here, to run once:
  int pin1;
  //Unit1->_phUnit->serial->begin(9600);
  pin1 = Unit1->pumpA->getPin1();
  Serial.print(pin1);
  delay(1000);
  Unit1->pumpA->setPin1(9);
  pin1 = Unit1->pumpA->getPin1();
  Serial.print(pin1);




}

void loop() {
  // put your main code here, to run repeatedly:

}
