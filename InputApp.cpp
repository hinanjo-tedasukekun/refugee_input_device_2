#include "DeviceSet.h"
#include "InputApp.h"

// コンストラクタ
InputApp::InputApp() :
  mode_setup_(true),
  devices_(),
  test_mode_(this, &devices_),
  blink_test_(this, &devices_),
  mode_(&blink_test_)
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

void InputApp::shiftToBlinkTest() {
  mode_ = &blink_test_;
  mode_setup_ = true;
}

void InputApp::shiftToTestMode() {
  mode_ = &test_mode_;
  mode_setup_ = true;
}
