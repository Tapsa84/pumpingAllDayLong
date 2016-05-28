#include "UnitController.h"
#include "PumpMotor.h"
#include "phUnit.h"
#include "HardwareSerial.h"

#define pA_pwm 13
#define pA_dir 24
#define pA_ena 25

#define pB_pwm 12
#define pB_dir 26
#define pB_ena 27

#define pC_pwm 11
#define pC_dir 28
#define pC_ena 29

#define pD_pwm 10
#define pD_dir 30
#define pD_ena 31

PumpMotor *pumpA = new PumpMotor(pA_pwm, pA_dir, pA_ena );
PumpMotor *pumpB = new PumpMotor(pB_pwm, pB_dir, pB_ena );
PumpMotor *pumpC = new PumpMotor(pC_pwm, pC_dir, pC_ena );
PumpMotor *pumpD = new PumpMotor(pD_pwm, pD_dir, pD_ena );

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
  
  Serial.print(pin1);
  delay(1000);
  
  
  Serial.print(pin1);




}

void loop() {
  // put your main code here, to run repeatedly:

}
