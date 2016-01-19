#include <Arduino.h>
#include "DeviceSet.h"
#include "AppState.h"
#include "ConfirmConnection.h"
#include "ConnectionError.h"
#include "SelectCommand.h"
#include "ReadRefugeeNum.h"
#include "RegisterFamilyData.h"
#include "SetPresence.h"
#include "InputApp.h"

// コンストラクタ
InputApp::InputApp() :
  state_setup_(true),
  refugee_num_(""),
  send_data_(""),
  devices_(),
  confirm_connection_(this, &devices_),
  connection_error_(this, &devices_),
  select_command_(this, &devices_),
  read_refugee_num_(this, &devices_),
  register_family_data_(this, &devices_),
  set_presence_(this, &devices_),
  state_(&confirm_connection_),
  state_after_read_refugee_num_(&select_command_)
{
}

// 設定を行う
void InputApp::setup() {
  devices_.setup();
}

// メインループ
void InputApp::loop() {
  if (state_setup_) {
    state_setup_ = false;
    state_->setup();
  }

  state_->loop();
  delay(10);
}

// 状態をリセットする
void InputApp::reset() {
  refugee_num_ = "";
  send_data_ = "";
  state_after_read_refugee_num_ = &select_command_;

  shiftToSelectCommand();
}

// 避難者番号を取得する
String InputApp::getRefugeeNum() {
  return refugee_num_;
}

// 避難者番号を設定する
void InputApp::setRefugeeNum(String new_refugee_num) {
  refugee_num_ = new_refugee_num;
}

void InputApp::shiftToConfirmConnection() {
  shiftState(&confirm_connection_);
}

void InputApp::shiftToConnectionError() {
  shiftState(&connection_error_);
}

void InputApp::shiftToSelectCommand() {
  shiftState(&select_command_);
}

void InputApp::shiftToRegisterFamilyData() {
  state_after_read_refugee_num_ = &register_family_data_;
  shiftState(&read_refugee_num_);
}

void InputApp::shiftToSetPresence() {
  state_after_read_refugee_num_ = &set_presence_;
  shiftState(&read_refugee_num_);
}

// 避難者番号の読み取りを終える
void InputApp::finishReadRefugeeNum() {
  shiftState(state_after_read_refugee_num_);
}

// モードを変える
void InputApp::shiftState(AppState* new_state) {
  state_ = new_state;
  state_setup_ = true;
}
