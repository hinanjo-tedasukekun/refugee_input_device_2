#ifndef SEND_DATA_H
#define SEND_DATA_H

#include "AppState.h"

class InputApp;
class DeviceSet;

// テストモードのクラス
class SendData : public AppState {
public:
  // 制限時間 [ms]
  static constexpr int TIME_LIMIT = 5 * 1000;
  // 送信後リセットするまでの待ち時間 [ms]
  static constexpr int WAIT_TIME_AFTER_SEND = 750;
  // LED の点滅間隔 [ms]
  static constexpr int LED_BLINK_INTERVAL = 150;

  // コンストラクタ
  SendData(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  // 受信を強制終了させる時刻 [ms]
  unsigned long ms_end_;

  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // 通信の準備を行う
  void prepareForCommunication();
  // 返信を処理する
  void processReply(char result_ch);

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
  // タイムアウト表示
  void printTimeout();
};

#endif
