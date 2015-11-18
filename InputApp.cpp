// vim: fileencoding=utf-8

#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "SoftwareSerial.h"

#include "XBeeSleepController.h"
#include "InputAppConfig.h"
#include "InputApp.h"
#include "InputLeaderId.h"

InputApp::InputApp() :
  lcd_(30, (bool)false), // 第 2 引数: false => 3.3 V; true => 5 V
  reader_serial_(
    InputAppConfig::PIN_READER_RX, InputAppConfig::PIN_READER_TX
  ),
  xbee_(InputAppConfig::PIN_XBEE_SLEEP),
  confirm_connection_(this, &lcd_),
  waiting_(this, &lcd_),
  input_leader_id_(this, &lcd_, &reader_serial_),
  input_num_of_members_(this, &lcd_),
  send_data_(this, &lcd_),
  state_(STATE_CONFIRM_CONNECTION),
  prev_state_(STATE_UNKNOWN),
  leader_id_(""),
  num_of_members_(1)
{
}

void InputApp::setup() {
  Serial.begin(9600);
  reader_serial_.begin(9600);

  pinMode(InputAppConfig::PIN_XBEE_SLEEP, OUTPUT);
  pinMode(InputAppConfig::PIN_READER_VCC, OUTPUT);
  pinMode(InputAppConfig::PIN_LED_SUCCESS, OUTPUT);
  pinMode(InputAppConfig::PIN_LED_ERROR, OUTPUT);

  enablePullUpResistorOfSwitches();
  digitalWrite(InputAppConfig::PIN_LED_SUCCESS, HIGH);
  digitalWrite(InputAppConfig::PIN_LED_ERROR, HIGH);

  lcd_.begin(16, 2);
}

void InputApp::reset() {
  state_ = STATE_WAITING;
  leader_id_ = "";
  num_of_members_ = 1;
}

void InputApp::loop() {
  AppState current_state = state_;

  switch (current_state) {
  case STATE_CONFIRM_CONNECTION:
    confirm_connection_.execute();
    state_ = STATE_WAITING;

    break;
  case STATE_WAITING:
    if (current_state != prev_state_) {
      waiting_.reset();
      waiting_.setupPorts();
      waiting_.setupLcd();
    }

    waiting_.loop();

    break;
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
      input_num_of_members_.setupPorts();
      input_num_of_members_.setupLcd();
    }

    input_num_of_members_.loop();

    break;
  case STATE_SEND_DATA:
    send_data_.execute(leader_id_, num_of_members_);
    reset();

    break;
  default:
    break;
  }

  prev_state_ = current_state;
  delay(10);
}

// 代表者番号の入力を開始する
void InputApp::startInputLeaderId() {
  state_ = STATE_INPUT_LEADER_ID;
}

// 代表者番号を設定する
void InputApp::setLeaderId(String leader_id) {
  leader_id_ = leader_id;
  state_ = STATE_INPUT_NUM_OF_MEMBERS;
}

// 人数を設定する
void InputApp::setNumOfMembers(int num_of_members) {
  num_of_members_ = num_of_members;
  state_ = STATE_SEND_DATA;
}

// スイッチのプルアップ抵抗を有効にする
void InputApp::enablePullUpResistorOfSwitches() {
  int sw_pins[] = {
    InputAppConfig::PIN_SW_1,
    InputAppConfig::PIN_SW_2,
    InputAppConfig::PIN_SW_3,
    InputAppConfig::PIN_SW_4,
    InputAppConfig::PIN_SW_PLUS,
    InputAppConfig::PIN_SW_MINUS,
    InputAppConfig::PIN_SW_ENTER,
    InputAppConfig::PIN_SW_LEAVE,
    InputAppConfig::PIN_SW_SEND,
    InputAppConfig::PIN_SW_RESET
  };

  for (int pin : sw_pins) {
    digitalWrite(pin, HIGH);
  }
}
