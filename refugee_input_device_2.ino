// vim: filetype=cpp

/*
 * 薄型避難者人数入力端末
 */

#include <avr/sleep.h>
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
