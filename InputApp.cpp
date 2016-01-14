#include "DeviceSet.h"
#include "AppState.h"
#include "ConfirmConnection.h"
#include "ConnectionError.h"
#include "SelectCommand.h"
#include "TestMode.h"
#include "BlinkTest.h"
#include "InputApp.h"

// コンストラクタ
InputApp::InputApp() :
  state_setup_(true),
  devices_(),
  confirm_connection_(this, &devices_),
  connection_error_(this, &devices_),
  select_command_(this, &devices_),
  test_mode_(this, &devices_),
  blink_test_(this, &devices_),
  state_(&confirm_connection_)
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
}

void InputApp::shiftToConfirmConnection() {
  shiftState(&confirm_connection_);
}

void InputApp::shiftToConnectionError() {
  shiftState(&connection_error_);
}

void InputApp::shiftToBlinkTest() {
  shiftState(&blink_test_);
}

void InputApp::shiftToTestMode() {
  shiftState(&test_mode_);
}

// モードを変える
void InputApp::shiftState(AppState* new_state) {
  state_ = new_state;
  state_setup_ = true;
}
