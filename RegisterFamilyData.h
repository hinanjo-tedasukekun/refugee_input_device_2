#ifndef REGISTER_FAMILY_DATA_H
#define REGISTER_FAMILY_DATA_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// 世帯情報登録クラス
class RegisterFamilyData : public AppState {
public:
  // コンストラクタ
  RegisterFamilyData(InputApp* app, DeviceSet* devices);
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
