#ifndef WAITING_H
#define WAITING_H

#include "I2CLiquidCrystal.h"

#include "XBeeSleepController.h"
#include "TactSwitch.h"

class InputApp;

class Waiting {
private:
  InputApp* app_;
  // LCD
  I2CLiquidCrystal* lcd_;
  // XBee スリープ制御
  XBeeSleepController xbee_;
  // 送信・受信ボタン
  TactSwitch sw_send_;

public:
  // コンストラクタ
  Waiting(InputApp* app, I2CLiquidCrystal* lcd);
  // 状態をリセットする
  void reset();
  // IO ポートを初期状態にする
  void setupPorts();
  // LCD を初期状態にする
  void setupLcd();
  // メインループ
  void loop();
};

#endif
