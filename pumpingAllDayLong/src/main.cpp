#include "UnitController.h"
#include "PumpMotor.h"
#include "phUnit.h"
#include "HardwareSerial.h"
#include <Arduino.h>
#include <DueFlashStorage.h>


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


struct Pump_Settings {

      float y1 = 0;
      float y2 = 0;
      int pump_flow = 17;
      int rMode = 0;
      int _setDir = 0;

};

DueFlashStorage dueFlashStorage;

Pump_Settings *pumpA_settings = new Pump_Settings;
Pump_Settings *pumpB_settings = new Pump_Settings;

Unit_Settings *unit1_settings = new Unit_Settings;


PumpMotor *pumpA = new PumpMotor(pA_pwm, pA_dir, pA_ena);
PumpMotor *pumpB = new PumpMotor(pB_pwm, pB_dir, pB_ena);

//PumpMotor *pumpC = new PumpMotor(pC_pwm, pC_dir, pC_ena);
//PumpMotor *pumpD = new PumpMotor(pD_pwm, pD_dir, pD_ena);



phUnit *phUnit1 = new phUnit(&Serial1);
//phUnit *phUnit2 = new phUnit(&Serial2);

PhAdjustingPumpController *pcA = new PhAdjustingPumpController(pumpA);
PhAdjustingPumpController *pcB = new PhAdjustingPumpController(pumpB);


UnitController *Unit1 = new UnitController(pcA, pcB, phUnit1, "Unit1", unit1_settings);
//UnitController *Unit2 = new UnitController(pumpC, pumpD, phUnit2, "Unit2");

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
  while (!SerialUSB);

  delay(200);

  pinMode(pA_pwm, OUTPUT); //u1 pA:n pwm ulostulo
  pinMode(pB_pwm, OUTPUT); //u1 pB:n pwm ulostulo
  pinMode(pA_dir, OUTPUT); //u1 pA:n pyÃ¶rimissuunta
  pinMode(pB_dir, OUTPUT); //u1 pB:n pyÃ¶rimissuunta
  pinMode(pA_ena, OUTPUT); //pin 26 on u1 pA:n kanavan kÃ¤ynnistys
  pinMode(pB_ena, OUTPUT); //pin 26 on u1 pA:n kanavan kÃ¤ynnistys

  delay(200);

  //codeRunningForTheFirstTime();

  delay(200);




  pumpA_settings->rMode = 0;
  pumpB_settings->rMode = 1;
  pumpA_settings->y1 = 17;
  pumpA_settings->y2 = 28;
  pumpB_settings->y1 = 23;
  pumpB_settings->y2 = 41;
  pumpB_settings->pump_flow = 23;

  // int rMode, float y1, float y2, int _setDir
  Unit1->pumpA->setSettings(pumpA_settings->rMode, pumpA_settings->y1, pumpA_settings->y2, pumpA_settings->_setDir, pumpA_settings->pump_flow);
  Unit1->pumpB->setSettings(pumpB_settings->rMode, pumpB_settings->y1, pumpB_settings->y2, pumpB_settings->_setDir, pumpB_settings->pump_flow);



  SerialUSB.println("hyvin menee");
  Serial1.print(" ");
  delay(1500);
}


void getSettings() {
  //Asetusten hakeminen pumpuille
  byte* b = dueFlashStorage.readAddress(4); //pumppu A:n osoite

  memcpy(&pumpA_settings, b, sizeof(Pump_Settings));

  byte* b2 = dueFlashStorage.readAddress(28); //pumppu B:n osoite

  memcpy(&pumpB_settings, b2, sizeof(Pump_Settings));

}

void saveSettings(int i) {


  if (i == 0) {
    SerialUSB.println("Saving pumpA settings to flash.");
    byte b2[sizeof(Pump_Settings)];
    memcpy(b2, &pumpA_settings, sizeof(Pump_Settings));
    dueFlashStorage.write(4, b2, sizeof(Pump_Settings));

    SerialUSB.println("Saving pumpB settings to flash.");
    byte b3[sizeof(Pump_Settings)];
    memcpy(b2, &pumpB_settings, sizeof(Pump_Settings));
    dueFlashStorage.write(28, b2, sizeof(Pump_Settings));
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

  if (input_cmd == "ID") {
    Serial.println("DS_pH_sys_1");
    SerialUSB.println("DS_pH_sys_1");
  }

  if(input_cmd == "PH"){
    if(input_value != ""){
      Unit1->unit_settings->desired_pH = input_value.toFloat();
      SerialUSB.println(Unit1->unit_settings->desired_pH);
      SerialUSB.println("I am Here!");
    }
  }


  if (input_cmd == "U1") {
    if (input_value == "off") {
      Unit1->controller_state = Unit1->Controller_state::off;
      Unit1->unit_off();
      Unit1->_phUnit->ContinousReadMode('0');

    }
    if (input_value == "on") {
      Unit1->_phUnit->ContinousReadMode('1');
      Unit1->controller_state = Unit1->Controller_state::on;
      Unit1->lastPass = millis();
    }

    if (input_value == "save") {
      SerialUSB.println("Saving current settings");
      saveSettings(0);
    }
    if (input_value == "pA_cal") {
      Unit1->unit_off();
      if (Unit1->pumpB->isCalibrating == false) {
        Unit1->pumpA->cal_state = Unit1->pumpA->Cal_state::air;
        Unit1->pumpA->isCalibrating = true;
        Unit1->controller_state = Unit1->Controller_state::off;
      }
      else {
        SerialUSB.println("Error: Already calibrating pump B");
      }
    }
    if (input_value == "pB_cal") {
      Unit1->unit_off();
      if (Unit1->pumpA->isCalibrating == false) {
        Unit1->pumpB->cal_state = Unit1->pumpB->Cal_state::air;
        Unit1->pumpB->isCalibrating = true;
        Unit1->controller_state = Unit1->Controller_state::off;
      }
      else {
        SerialUSB.println("Error: Already calibrating pump A");
      }
    }
    if (input_value == "pH_cal_high") {
      Unit1->unit_off();
      Unit1->controller_state = Unit1->Controller_state::off;
      Unit1->ph_cal_state = Unit1->ph_Cal_state::init_mid;
      Unit1->_phUnit->ContinousReadMode('0');
      Unit1->_phUnit->isCalibratingHigh = true;
      Unit1->_phUnit->isCalibratingLow = false;
      Unit1->_phUnit->isCalibratingTri = false;
    }

    if (input_value == "pH_cal_low") {
      Unit1->unit_off();
      Unit1->controller_state = Unit1->Controller_state::off;
      Unit1->ph_cal_state = Unit1->ph_Cal_state::init_mid;
      Unit1->_phUnit->ContinousReadMode('0');
      Unit1->_phUnit->isCalibratingHigh = false;
      Unit1->_phUnit->isCalibratingLow = true;
      Unit1->_phUnit->isCalibratingTri = false;
    }

    if (input_value == "pH_cal_tri") {
      Unit1->unit_off();
      Unit1->controller_state = Unit1->Controller_state::off;
      Unit1->ph_cal_state = Unit1->ph_Cal_state::init_mid;
      Unit1->_phUnit->ContinousReadMode('0');
      Unit1->_phUnit->isCalibratingHigh = false;
      Unit1->_phUnit->isCalibratingLow = false;
      Unit1->_phUnit->isCalibratingTri = true;
    }

    if (input_value == "pH_cont_read_mode") {
      Unit1->_phUnit->ContinousReadMode('?');
    }

    if (input_value == "pH_cont_read_on") {
      Unit1->_phUnit->ContinousReadMode('1');
    }

    if (input_value == "pH_cont_read_off") {
      Unit1->_phUnit->ContinousReadMode('0');
    }

    else {
      Unit1->input_cmd = input_value;
    }
    /*    if (input_value == "ok") {
          Unit1->input_cmd = input_value;
        }
        if (input_value == "stop") {
          Unit1->input_cmd = input_value;
        }
        if(input_value == "cancel") {
          Unit1->input_cmd = input_value;
       }*/
  }







  if (input_cmd == "U1_pB") {
    if (input_value == "is_cal") {

      if (Unit1->pumpB->isCalib()) {
        SerialUSB.println("pB_isCalib:1");
      }
      else {
        SerialUSB.println("pB_isCalib:0");
      }
    }
  }

  if (input_cmd == "U1_pH") {
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

void codeRunningForTheFirstTime() {

  uint8_t codeRunningForTheFirstTime = dueFlashStorage.read(0); // luetaan flash osoitteesta 0
  SerialUSB.print("codeRunningForTheFirstTime: ");
  if (codeRunningForTheFirstTime == 255) {
    SerialUSB.println("yes");

    // tallennetaan pumppu A muistiin
    byte b2[sizeof(Pump_Settings)];
    memcpy(b2, &pumpA_settings, sizeof(Pump_Settings));
    dueFlashStorage.write(4, b2, sizeof(Pump_Settings));

    //tallennetaan pumppu B muistiin
    byte b3[sizeof(Pump_Settings)];
    memcpy(b2, &pumpB_settings, sizeof(Pump_Settings));
    dueFlashStorage.write(28, b3, sizeof(Pump_Settings));


    SerialUSB.println(sizeof(Pump_Settings));

    // kirjoitetaan flashiin 1 osoiteessa 0, että koodia ei ajeta enää ensimmäistä kertaa
    dueFlashStorage.write(0, 1);
  }
  else {
    SerialUSB.println("no");
    getSettings(); //haetaan flash-muistista pumppujen asetukset
  }
}

void loop() {

  Unit1->tick();
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
    SerialUSB.println(input_data_2);

    if (input_data_2 == "?C,1")
    {
      Unit1->_phUnit->_isReading = true;
    }

    if (input_data_2 == "?C,0")
    {
      Unit1->_phUnit->_isReading = false;
    }

    if (input_data_2 == "?CAL,1")
    {
      Unit1->_phUnit->_isCalibrated = true;
    }

    if (input_data_2 == "?CAL,2")
    {
      Unit1->_phUnit->_isCalibrated = true;
    }

    if (input_data_2 == "?CAL,3")
    {
      Unit1->_phUnit->_isCalibrated = true;
    }

    if (input_data_2 == "*OK") {
      //do nothing
    }

    else if (Unit1->_phUnit->_isReading == true)
    {
      Unit1->setMeasuredPh(input_data_2.toFloat());
    }


    input_data_2 = "";
    input_data_done_2 = false;
  }

}
