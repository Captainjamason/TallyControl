// Library Includes
#include <BMDSDIControl.h>

// Define our  outward tally pins.
#define CAM1 6
#define CAM2 7

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
  
  sdiTallyControl.begin();
  sdiTallyControl.setOverride(true);

  pinMode(CAM1, OUTPUT);
  pinMode(CAM2, OUTPUT);
}

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
      out.concat("OFF   Cam 2: ");
    }
  }
  if(sdiTallyControl.getCameraTally(2, cam2_prog, cam2_prev)) {
    if(cam2_prog) {
     digitalWrite(CAM2, HIGH);
      out.concat("ON\r");
    } else {
      out.concat("OFF\r");
    }
  }
  Serial.println(out);
}
