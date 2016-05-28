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

<<<<<<< HEAD
PumpMotor *pumpA = new PumpMotor(pA_pwm, pA_dir, pA_ena );
PumpMotor *pumpB = new PumpMotor(pB_pwm, pB_dir, pB_ena );
PumpMotor *pumpC = new PumpMotor(pC_pwm, pC_dir, pC_ena );
PumpMotor *pumpD = new PumpMotor(pD_pwm, pD_dir, pD_ena );

=======
PumpMotor *pumpA = new PumpMotor(pA_pwm_pin, pA_direction_pin, );
PumpMotor *pumpB = new PumpMotor(13, 14, 15);
PumpMotor *pumpC = new PumpMotor(16, 17, 18);
PumpMotor *pumpD = new PumpMotor(19, 20, 21);
>>>>>>> refs/remotes/origin/pumpingAllDayLong
phUnit *phUnit1 = new phUnit(&Serial1);
phUnit *phUnit2 = new phUnit(&Serial2);

UnitController *Unit1 = new UnitController(pumpA, pumpB, phUnit1);
UnitController *Unit2 = new UnitController(pumpC, pumpD, phUnit2);



<<<<<<< HEAD
=======





>>>>>>> refs/remotes/origin/pumpingAllDayLong
void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.print("JEE");
  delay(1000);




  // put your setup code here, to run once:
  int pin1;
  //Unit1->_phUnit->serial->begin(9600);
<<<<<<< HEAD
  
  Serial.print(pin1);
  delay(1000);
  
  
=======
  pin1 = Unit1->pumpA->getPin1();
  Serial.print(pin1);
  delay(1000);
  Unit1->pumpA->setPin1(9);
  pin1 = Unit1->pumpA->getPin1();
>>>>>>> refs/remotes/origin/pumpingAllDayLong
  Serial.print(pin1);




}

void loop() {
  // put your main code here, to run repeatedly:

}
