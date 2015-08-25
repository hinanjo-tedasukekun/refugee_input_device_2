#ifndef INPUT_LEADER_ID_H
#define INPUT_LEADER_ID_H

#include "I2CLiquidCrystal.h"
#include "SoftwareSerial.h"

#include "InputAppConfig.h"
#include "RingBuffer8.h"
#include "TactSwitch.h"

class InputApp;

class InputLeaderId {
private:
  // 代表者番号の文字列を格納するリングバッファ
  RingBuffer8 ring_buffer_;
  // 代表者番号が変更されたかどうか
  bool leader_id_changed_;

  InputApp* app_;
  // LCD
  I2CLiquidCrystal* lcd_;
  SoftwareSerial* reader_serial_;
  TactSwitch input_sw_;

public:
  InputLeaderId(
    InputApp* app, I2CLiquidCrystal* lcd, SoftwareSerial* reader_serial
  );
  // 状態をリセットする
  void reset();
  // IO ポートを初期状態にする
  void setupPorts();
  // LCD を初期状態にする
  void setupLcd();
  // メインループ
  void loop();

private:
  // 入力スイッチのイベントを処理する
  void handleInputSwEvent(TactSwitch::SwitchState state);
  // 入力スイッチが押されたときの処理
  void inputSwPushed();
  // LCD の代表者番号表示を更新する
  void updateLeaderIdOnLcd();
};

#endif
