#ifndef SELECT_COMMAND_H
#define SELECT_COMMAND_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// コマンド選択のクラス
class SelectCommand : public AppState {
public:
  // コマンドの列挙型
  enum Command {
    // 世帯人数を登録する
    REGISTER_NUM_OF_MEMBERS,
    // 入退室情報を設定する
    SET_PRESENCE,
    // ダミー：コマンドの総数
    N_COMMANDS
  };

  // コマンドの名前
  static constexpr const char* COMMAND_NAME[N_COMMANDS] = {
    // "1. セタイノニンズウ"
    "1. \xBE\xC0\xB2\xC9\xC6\xDD\xBD\xDE\xB3    ",
    // "2. ニュウシツ・タイシツ"
    "2. \xC6\xAD\xB3\xBC\xC2\xA5\xC0\xB2\xBC\xC2   "
  };

  // コンストラクタ
  SelectCommand(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  // 選択されているコマンド
  Command selected_;
  // LCD の表示を更新するかどうか
  bool lcd_update_;

  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // スイッチのイベントを処理する
  void handleSwitchEvents();
};
#endif
