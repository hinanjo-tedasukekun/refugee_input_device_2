#ifndef TEST_MODE_H
#define TEST_MODE_H

#include "AppMode.h"
#include "DeviceSet.h"

class InputApp;

// テストモードのクラス
class TestMode : public AppMode {
public:
  // コンストラクタ
  TestMode(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // スイッチのイベントを処理する
  void handleSwEvents();
};

#endif
