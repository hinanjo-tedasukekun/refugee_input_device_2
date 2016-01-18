#ifndef SET_PRESENCE_H
#define SET_PRESENCE_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// 在室状況設定クラス
class SetPresence : public AppState {
public:
  // コンストラクタ
  SetPresence(InputApp* app, DeviceSet* devices);
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
  void handleSwitchEvents();
};

#endif
