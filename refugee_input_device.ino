// vim: filetype=cpp

/*
 * 避難者人数入力端末
 */

#include <Wire.h>
#include <I2CLiquidCrystal.h>
#include <SoftwareSerial.h>
#include "InputApp.h"

InputApp gApp;

void setup() {
  gApp.setup();
}

void loop() {
  gApp.loop();
}
