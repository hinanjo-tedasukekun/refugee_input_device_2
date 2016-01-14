#ifndef INPUT_APP_H
#define INPUT_APP_H

#include "DeviceSet.h"
#include "AppMode.h"
#include "ConfirmConnection.h"
#include "ConnectionError.h"
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

  void shiftToConfirmConnection();
  void shiftToConnectionError();
  void shiftToBlinkTest();
  void shiftToTestMode();
private:
  // モードの設定を行うかどうか
  bool mode_setup_;
  // デバイス集合
  DeviceSet devices_;

  ConfirmConnection confirm_connection_;
  ConnectionError connection_error_;
  TestMode test_mode_;
  BlinkTest blink_test_;
  AppMode* mode_;

  // モードを変える
  void shiftMode(AppMode* new_mode);
};

#endif
