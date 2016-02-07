#ifndef CONNECTION_ERROR_H
#define CONNECTION_ERROR_H

#include "AppState.h"
#include "DeviceSet.h"

class InputApp;

// サーバーとの接続エラー表示
class ConnectionError : public AppState {
public:
  // メッセージ切り替え間隔 [ms]
  static constexpr int MESSAGE_INTERVAL = 2000;

  // コンストラクタ
  ConnectionError(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  // メッセージの種類
  int message_;
  // メッセージを切り替える時刻
  unsigned long switch_message_time_;
  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // サーバー確認表示
  void printConfirmServer();
  // 次へボタン押下指示表示
  void printPressNextButton();
};

#endif
