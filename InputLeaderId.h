#ifndef INPUT_LEADER_ID_H
#define INPUT_LEADER_ID_H

#include "LiquidCrystal.h"

#include "InputAppConfig.h"
#include "TactSwitchWithLongPush.h"

class InputApp;

class InputLeaderId {
private:
  const char* LEADER_ID_FORMAT;
  // 代表者番号の文字列
  char leader_id_[InputAppConfig::LEADER_ID_LENGTH + 1];
  // 代表者番号が変更されたかどうか
  bool leader_id_changed_;

  InputApp* app_;
  // LCD
  LiquidCrystal* lcd_;
  // 入力スイッチ
  TactSwitchWithLongPush input_sw_;

public:
  InputLeaderId(InputApp* app, LiquidCrystal* lcd);
  // 状態をリセットする
  void reset();
  // LED を初期状態にする
  void setupLeds();
  // LCD を初期状態にする
  void setupLcd();
  // メインループ
  void loop();

private:
  // 入力スイッチのイベントを処理する
  void handleInputSwEvent(TactSwitchWithLongPush::SwitchState state);
  // 入力スイッチが短く押されたときの処理
  void inputSwPushedShort();
  // 入力スイッチが長く押されたときの処理
  void inputSwPushedLong();
  // LCD の代表者番号表示を更新する
  void updateLeaderIdOnLcd();
};

#endif
