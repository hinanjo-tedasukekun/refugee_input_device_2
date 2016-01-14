#ifndef CONFIRM_CONNECTION_H
#define CONFIRM_CONNECTION_H

#include "AppMode.h"
#include "DeviceSet.h"

class InputApp;

// サーバーとの接続確認
class ConfirmConnection : public AppMode {
public:
  // 最大リトライ回数
  static constexpr int MAX_RETRY = 2;

  // コンストラクタ
  ConfirmConnection(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  // 応答要求を送信した回数
  int send_count_;
  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // 接続中表示
  void printConnecting();
};

#endif
