#ifndef INPUT_LEADER_ID_H
#define INPUT_LEADER_ID_H

#include "I2CLiquidCrystal.h"
#include "SoftwareSerial.h"

#include "InputAppConfig.h"
#include "RingBuffer8.h"
#include "TactSwitch.h"
#include "TactSwitchWithLongPush.h"

class InputApp;

class InputLeaderId {
private:
  // 代表者番号の文字列を格納するリングバッファ
  RingBuffer8 ring_buffer_;
  // 代表者番号が変更されたかどうか
  bool leader_id_changed_;
  // 読み取りを強制終了させる時刻（ミリ秒単位）
  unsigned long ms_end_;

  InputApp* app_;
  // LCD
  I2CLiquidCrystal* lcd_;

  SoftwareSerial* reader_serial_;

  // リセットボタン
  TactSwitch sw_reset_;
  // 読み取りボタン
  TactSwitchWithLongPush sw_read_;

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
  // 代表者番号の例を読み込む
  void readSampleLeaderId();
  // LCD の代表者番号表示を更新する
  void updateLeaderIdOnLcd();
};

#endif
