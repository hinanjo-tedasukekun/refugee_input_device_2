// vim: filetype=cpp

/*
 * 避難者人数入力端末 試作版
 */

#include <Wire.h>
#include <I2CLiquidCrystal.h>
#include <SoftwareSerial.h>
#include "InputApp.h"

InputApp app;

void setup() {
  app.setup();
}

void loop() {
  app.loop();
}
