// vim: fileencoding=utf-8

#include <Arduino.h>
#include "LiquidCrystal.h"
#include "SoftwareSerial.h"
#include <string.h>

#include "InputAppConfig.h"
#include "InputApp.h"
#include "InputLeaderId.h"

InputApp::InputApp() :
  lcd_(12, A4, A3, A2, A1, A0),
  reader_serial_(
    InputAppConfig::PIN_READER_RX, InputAppConfig::PIN_READER_TX
  ),
  input_leader_id_(this, &lcd_, &reader_serial_),
  input_num_of_members_(this, &lcd_),
  send_data_(this, &lcd_),
  state_(STATE_INPUT_LEADER_ID),
  prev_state_(STATE_INPUT_LEADER_ID),
  leader_id_(""),
  num_of_members_(1)
{
}

void InputApp::setup() {
  randomSeed(analogRead(5));

  Serial.begin(9600);
  reader_serial_.begin(9600);

  pinMode(InputAppConfig::PIN_READER_VCC, OUTPUT);
  pinMode(InputAppConfig::PIN_LED_SUCCESS, OUTPUT);
  pinMode(InputAppConfig::PIN_LED_ERROR, OUTPUT);
  input_leader_id_.setupPorts();

  lcd_.begin(16, 2);
  input_leader_id_.setupLcd();
}

void InputApp::reset() {
  state_ = STATE_INPUT_LEADER_ID;
  leader_id_ = "";
  num_of_members_ = 1;
}

void InputApp::loop() {
  AppState current_state = state_;

  switch (current_state) {
  case STATE_INPUT_LEADER_ID:
    if (current_state != prev_state_) {
      input_leader_id_.reset();
      input_leader_id_.setupPorts();
      input_leader_id_.setupLcd();
    }

    input_leader_id_.loop();

    break;
  case STATE_INPUT_NUM_OF_MEMBERS:
    if (current_state != prev_state_) {
      input_num_of_members_.reset();
      input_num_of_members_.setupLcd();
    }

    input_num_of_members_.loop();

    break;
  case STATE_SEND_DATA:
    send_data_.execute(leader_id_, num_of_members_);
    delay(2100);
    reset();

    break;
  default:
    break;
  }

  prev_state_ = current_state;
  delay(10);
}

void InputApp::setLeaderId(String leader_id) {
  leader_id_ = leader_id;
  state_ = STATE_INPUT_NUM_OF_MEMBERS;
}

void InputApp::setNumOfMembers(int num_of_members) {
  num_of_members_ = num_of_members;
  state_ = STATE_SEND_DATA;
}
