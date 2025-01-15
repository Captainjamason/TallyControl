//  TallyControl
//  Developed for RCC
//  JPD - 2025

// Library Includes
#include <BMDSDIControl.h>

// Define our  outward tally pins.
#define CAM1 7
#define CAM2 6

// BMD Shield i2c address and class init.
const int shieldAddress = 0x6E;
BMD_SDITallyControl_I2C sdiTallyControl(shieldAddress);

// Create our storage variables, for tally signals and for the debug output.
bool cam1_prog, cam1_prev;
bool cam2_prog, cam2_prev;
String out;

// One time setup() function.
void setup() {
  // Open our debug serial port.
  Serial.begin(9600);

  // Begin tally control with the shield.
  sdiTallyControl.begin();
  sdiTallyControl.setOverride(true);

  // Set pinouts.
  pinMode(CAM1, OUTPUT);
  pinMode(CAM2, OUTPUT);
}

// checkDebug function, utilized for Serial printout. 
bool checkDebug(int num) {
  if(Serial.available()) {
    char receivedChar = Serial.read();
    if(receivedChar == num) {
      return true;
    } else {
      return false;
    }
  }
}

//  This is pretty rudimentary programming, but we only have 2 cameras with tally support. Not much reason to change no?
void loop() {
  out = "";
  out.concat("Cam 1: ");
  if(sdiTallyControl.getCameraTally(1, cam1_prog, cam2_prev)) {
    if(cam1_prog) {
      digitalWrite(CAM1, HIGH);
      out.concat("ON    Cam 2: ");
    } else {
      digitalWrite(CAM1, LOW);
      out.concat("OFF   Cam 2: ");
    }
  }
  if(sdiTallyControl.getCameraTally(2, cam2_prog, cam2_prev)) {
    if(cam2_prog) {
     digitalWrite(CAM2, HIGH);
      out.concat("ON\r");
    } else {
      digitalWrite(CAM2, LOW);
      out.concat("OFF\r");
    }
  }
  Serial.println(out);
}
