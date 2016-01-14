#ifndef INPUT_APP_H
#define INPUT_APP_H

#include "DeviceSet.h"
#include "AppMode.h"
#include "TestMode.h"
#include "BlinkTest.h"

class InputApp {
public:
  // コンストラクタ
  InputApp();
  // 設定を行う
  void setup();
  // メインループ
  void loop();
  void shiftToBlinkTest();
  void shiftToTestMode();
private:
  // モードの設定を行うかどうか
  bool mode_setup_;
  // デバイス集合
  DeviceSet devices_;
  TestMode test_mode_;
  BlinkTest blink_test_;
  AppMode* mode_;
};

#endif
