#ifndef CONFIRM_CONNECTION_H
#define CONFIRM_CONNECTION_H

#include "I2CLiquidCrystal.h"

#include "XBeeSleepController.h"
#include "TactSwitch.h"

class InputApp;

class ConfirmConnection {
public:
  // 最大リトライ回数
  static constexpr int MAX_RETRY = 2;

  // メッセージ切り替え間隔
  static constexpr int MESSAGE_INTERVAL = 2000;

private:
  InputApp* app_;
  // LCD
  I2CLiquidCrystal* lcd_;
  // XBee スリープ制御
  XBeeSleepController xbee_;
  // リセットボタン
  TactSwitch sw_reset_;

public:
  // コンストラクタ
  ConfirmConnection(InputApp* app, I2CLiquidCrystal* lcd);
  // サーバーとの接続を確認する
  void execute();

private:
  // 状態をリセットする
  void reset();
  // 通信の準備を行う
  void prepareForCommunication();

  // ACK を送信する
  // OK が返ってきたら true を返す
  // 制限時間内に OK が返ってこなかったら false を返す
  bool sendAcks();

  // リセットを待つ
  void waitForReset();

  // 接続中表示
  void printConnecting();
  // サーバー確認表示
  void printConfirmServer();
  // リセットボタン押下指示表示
  void printPressResetButton();
};

#endif
