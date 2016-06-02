#include "UnitController.h"
#include "PumpMotor.h"
#include "phUnit.h"
#include "HardwareSerial.h"
#include <Arduino.h>

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




PumpMotor *pumpA = new PumpMotor(pA_pwm, pA_dir, pA_ena);
PumpMotor *pumpB = new PumpMotor(pB_pwm, pB_dir, pB_ena);
//PumpMotor *pumpC = new PumpMotor(pC_pwm, pC_dir, pC_ena);
//PumpMotor *pumpD = new PumpMotor(pD_pwm, pD_dir, pD_ena);




phUnit *phUnit1 = new phUnit(&Serial1);
//phUnit *phUnit2 = new phUnit(&Serial2);

UnitController *Unit1 = new UnitController(pumpA, pumpB, phUnit1);
//UnitController *Unit2 = new UnitController(pumpC, pumpD, phUnit2);

int lastPass = 0;
const int sec10 = 1UL * 1;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {

  pinMode(pA_pwm, OUTPUT); //u1 pA:n pwm ulostulo
  pinMode(pB_pwm, OUTPUT); //u1 pB:n pwm ulostulo
  pinMode(pA_dir, OUTPUT); //u1 pA:n pyörimissuunta
  pinMode(pB_dir, OUTPUT); //u1 pB:n pyörimissuunta
  pinMode(pA_ena, OUTPUT); //pin 26 on u1 pA:n kanavan käynnistys
  pinMode(pB_ena, OUTPUT); //pin 26 on u1 pA:n kanavan käynnistys

  Serial.begin(9600);
  Unit1->pumpA->getSettings(1, 5, 10, 20);
  Unit1->pumpB->getSettings(2, 10, 10, 20);
  Unit1->start();

  if (Unit1->pumpA->isOn()) {
    Serial.println("pumpA is on");
  }
  if (Unit1->pumpB->isOn()) {
    Serial.println("pumpB is on");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Unit1->tick();

  if (stringComplete) {
    Unit1->dummy_pH = inputString.toFloat();
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    stringComplete = true;
  }
}

bool oncePer10Sec() {
  if (millis() > lastPass + sec10) {
    lastPass = millis();
    return true;
  }
  return false;
}

