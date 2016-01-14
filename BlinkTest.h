#ifndef BLINK_TEST_H
#define BLINK_TEST_H

#include "AppMode.h"
#include "DeviceSet.h"

class InputApp;

// テストモードのクラス
class BlinkTest : public AppMode {
public:
  // コンストラクタ
  BlinkTest(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  int count_;
  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;
};

#endif
