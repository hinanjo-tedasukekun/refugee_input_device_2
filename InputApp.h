#ifndef INPUT_APP_H
#define INPUT_APP_H

#include "DeviceSet.h"
#include "AppState.h"
#include "ConfirmConnection.h"
#include "ConnectionError.h"
#include "SelectCommand.h"
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
  void shiftToSelectCommand();
  void shiftToBlinkTest();
  void shiftToTestMode();
private:
  // モードの設定を行うかどうか
  bool state_setup_;
  // デバイス集合
  DeviceSet devices_;

  ConfirmConnection confirm_connection_;
  ConnectionError connection_error_;
  SelectCommand select_command_;
  TestMode test_mode_;
  BlinkTest blink_test_;
  AppState* state_;

  // モードを変える
  void shiftState(AppState* new_state);
};

#endif
