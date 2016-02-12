#ifndef SELECT_COMMAND_H
#define SELECT_COMMAND_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// コマンド選択のクラス
class SelectCommand : public AppState {
public:
  // 入力の制限時間 [ms]
  static constexpr unsigned long TIME_LIMIT = 15 * 1000;

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
  // スリープモードに移行する時刻 [ms]
  unsigned long ms_sleep_;

  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // スイッチのイベントを処理する
  void handleSwitchEvents();
};

#endif
