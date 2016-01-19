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
  // 世帯の人数
  int num_of_members_;
  // 世帯の人数が変化したかどうか
  bool num_of_members_changed_;

  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // スイッチのイベントを処理する
  void handleSwitchEvents();
  // 世帯の人数を設定する
  void setNumOfMembers(int num);
  // LCD の人数表示を更新する
  void updateNumOnLcd();
};

#endif
