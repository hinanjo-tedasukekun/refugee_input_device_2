#ifndef SET_PRESENCE_H
#define SET_PRESENCE_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// 在室情報設定クラス
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
  // 在室情報
  bool present_;
  // 在室情報が変化したかどうか
  bool presence_changed_;

  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // スイッチのイベントを処理する
  void handleSwitchEvents();
  // LCD の在室情報表示を更新する
  void updatePresenceOnLcd();
  // 送信データを設定する
  void setSendData();
};

#endif
