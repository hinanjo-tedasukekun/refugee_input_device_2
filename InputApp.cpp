#include "DeviceSet.h"
#include "InputApp.h"

// コンストラクタ
InputApp::InputApp() :
  mode_setup_(true),
  devices_(),
  confirm_connection_(this, &devices_),
  connection_error_(this, &devices_),
  test_mode_(this, &devices_),
  blink_test_(this, &devices_),
  mode_(&confirm_connection_)
{
}

// 設定を行う
void InputApp::setup() {
  devices_.setup();
}

// メインループ
void InputApp::loop() {
  if (mode_setup_) {
    mode_setup_ = false;
    mode_->setup();
  }

  mode_->loop();
}

void InputApp::shiftToConfirmConnection() {
  shiftMode(&confirm_connection_);
}

void InputApp::shiftToConnectionError() {
  shiftMode(&connection_error_);
}

void InputApp::shiftToBlinkTest() {
  shiftMode(&blink_test_);
}

void InputApp::shiftToTestMode() {
  shiftMode(&test_mode_);
}

// モードを変える
void InputApp::shiftMode(AppMode* new_mode) {
  mode_ = new_mode;
  mode_setup_ = true;
}
