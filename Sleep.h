#ifndef SLEEP_H
#define SLEEP_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// スリープモードのクラス
class Sleep : public AppState {
public:
  // コンストラクタ
  Sleep(InputApp* app, DeviceSet* devices);
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
};

#endif
