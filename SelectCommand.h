#ifndef SELECT_COMMAND_H
#define SELECT_COMMAND_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// コマンド選択のクラス
class SelectCommand : public AppState {
public:
  // コマンド
  static const char* COMMANDS[];
  // コマンドの総数
  static const int N_COMMANDS;

  // コンストラクタ
  SelectCommand(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  // 選択されているコマンド
  int selected_;
  // 選択されているコマンドが変化したかどうか
  bool command_changed_;

  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // スイッチのイベントを処理する
  void handleSwitchEvents();
};

#endif
