#ifndef SEND_DATA_H
#define SEND_DATA_H

#include "I2CLiquidCrystal.h"

#include "XBeeSleepController.h"
#include "TactSwitch.h"

class InputApp;

class SendData {
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
  SendData(InputApp* app, I2CLiquidCrystal* lcd);
  // データ送信を実行する
  void execute(String leader_id_, int num_of_members);

private:
  // 通信の準備を行う
  void prepareForCommunication();
  // データを送信する
  void send(String leader_id, int num_of_members);

  // 通信準備中表示
  void printPreparing();
  // 送信中表示
  void printSending();
  // 登録完了表示
  void printRegistered();
  // 更新完了表示
  void printUpdated();
  // 登録失敗表示
  void printError();

  // LED を点滅させる
  void blinkLed(int pin);
};

#endif
