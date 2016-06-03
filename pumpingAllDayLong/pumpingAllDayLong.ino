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
PumpMotor *pumpC = new PumpMotor(pC_pwm, pC_dir, pC_ena);
PumpMotor *pumpD = new PumpMotor(pD_pwm, pD_dir, pD_ena);




phUnit *phUnit1 = new phUnit(&Serial1);
phUnit *phUnit2 = new phUnit(&Serial2);

UnitController *Unit1 = new UnitController(pumpA, pumpB, phUnit1);
UnitController *Unit2 = new UnitController(pumpC, pumpD, phUnit2);

String input_data = "";
String input_data_2 = "";
String input_cmd = "";
String input_value = "";
boolean input_data_done = false;
boolean input_data_done_2 = false;

int i = 5;

void setup() {


  Serial.begin(9600);
  Serial1.begin(9600);
  SerialUSB.begin(9600);
  while(!SerialUSB);


  pinMode(pA_pwm, OUTPUT); //u1 pA:n pwm ulostulo
  pinMode(pB_pwm, OUTPUT); //u1 pB:n pwm ulostulo
  pinMode(pA_dir, OUTPUT); //u1 pA:n pyÃ¶rimissuunta
  pinMode(pB_dir, OUTPUT); //u1 pB:n pyÃ¶rimissuunta
  pinMode(pA_ena, OUTPUT); //pin 26 on u1 pA:n kanavan kÃ¤ynnistys
  pinMode(pB_ena, OUTPUT); //pin 26 on u1 pA:n kanavan kÃ¤ynnistys




  delay(1000);

  Unit1->pumpA->getSettings(2, 5, 10, 20);
  Unit1->pumpB->getSettings(1, 5, 10, 20);
  Unit2->pumpA->getSettings(2, 5, 10, 20);
  Unit2->pumpB->getSettings(1, 5, 10, 20);


  SerialUSB.println("hyvin menee");
  Serial1.print(" ");
  delay(1000);
  Serial1.print("C,0");
  Serial1.print("\r");



}

void loop() {

  //Unit1->tick();
  //Unit2->tick();

  serialEventUSB();

  if (input_data_done) {

    //Serial.print(input_data);
    commandParse();
    input_data = "";
    input_cmd = "";
    input_value = "";
    input_data_done = false;
  }

  if (input_data_done_2) {

    //Serial.print(input_data);
    //commandParse();
    input_data_2 = "";
    SerialUSB.println(input_data_2);
    input_data_done_2 = false;
  }

}




boolean commandParse() {


  int semicolon = input_data.indexOf(':');
  int lastchar = input_data.indexOf('\n');

  int index = 0;

  for (index; index < semicolon; index++) {
    input_cmd += input_data.charAt(index);

  }

  index = semicolon + 1;

  for (index; index < lastchar ; index++) {

    input_value += input_data.charAt(index);
  }

  //Serial.println(input_cmd);
  //Serial.println(input_value);

  if (input_cmd == "ID") {
    Serial.println("DS_pH_sys_1");
    SerialUSB.println("DS_pH_sys_1:1");
  }

  if (input_cmd == "pA")
  {

    Unit1->pumpA->input_cal = input_value;
    if (input_value == "is_cal")
    {

      if (Unit1->pumpA->isCalib())
      {
        SerialUSB.println("pA_isCalib:1");
      }
      else
      {
        SerialUSB.println("pA_isCalib:0");
      }
    }
    if (input_value == "cal")
    {
      Unit1->pumpA->calibrate();
    }
  }

  if (input_cmd == "pB") {
    if (input_value == "is_cal") {

      if (Unit1->pumpB->isCalib()) {
        SerialUSB.println("pB_isCalib:1");
      }
      else {
        SerialUSB.println("pB_isCalib:0");
      }
    }
  }

  if (input_cmd == "pH_1") {
    if (input_value == "is_cal") {

      if (Unit1->_phUnit->isCalibrated()) {
        SerialUSB.println("pH_1_is_cal:1");
      }
      else {
        SerialUSB.println("pH_1_is_cal:10");
      }
    }
  }
}

void serialEventUSB() {

  while (SerialUSB.available()) {

    char inChar = (char)SerialUSB.read();
    input_data += inChar;
    if (inChar == '\n')
    {
      input_data_done = true;
    }
  }

}

void serialEvent() {

  while (Serial.available()) {

    char inChar = (char)Serial.read();
    input_data += inChar;
    if (inChar == '\n') {
      input_data_done = true;
    }
  }
}

void serialEvent1() {

  while (Serial1.available()) {

    char inChar = (char)Serial1.read();
    input_data_2 += inChar;
    if (inChar == '\r') {
      input_data_done_2 = true;
    }
  }
}



union Unit_Settings {
  struct {
    float desired_pH;
    float y1;
    float y2;
    int pumpA_flow;
    int pumpB_flow;
    int calibmode;


  };
};















