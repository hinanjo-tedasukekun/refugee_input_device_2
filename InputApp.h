#ifndef INPUT_APP_H
#define INPUT_APP_H

#include "DeviceSet.h"
#include "AppState.h"
#include "ConfirmConnection.h"
#include "ConnectionError.h"
#include "SelectCommand.h"
#include "Sleep.h"
#include "ReadRefugeeNum.h"
#include "RegisterFamilyData.h"
#include "SetPresence.h"
#include "SendData.h"

class InputApp {
public:
  // コンストラクタ
  InputApp();
  // 設定を行う
  void setup();
  // メインループ
  void loop();
  // 状態をリセットする
  void reset();

  // 避難者番号を取得する
  String getRefugeeNum();
  // 避難者番号を設定する
  void setRefugeeNum(String new_refugee_num);

  // 送信するデータを取得する
  String getSendData();
  // 送信するデータを設定する
  void setSendData(String new_send_data);

  void shiftToConfirmConnection();
  void shiftToConnectionError();
  void shiftToSelectCommand();
  void shiftToSleep();
  void shiftToRegisterFamilyData();
  void shiftToSetPresence();
  void shiftToSendData();
  // 避難者番号の読み取りを終える
  void finishReadRefugeeNum();
private:
  // モードの設定を行うかどうか
  bool state_setup_;
  // 避難者番号
  String refugee_num_;
  // 送信するデータ
  String send_data_;

  // デバイス集合
  DeviceSet devices_;

  ConfirmConnection confirm_connection_;
  ConnectionError connection_error_;
  SelectCommand select_command_;
  Sleep sleep_;
  ReadRefugeeNum read_refugee_num_;
  RegisterFamilyData register_family_data_;
  SetPresence set_presence_;
  SendData send_data_state_;

  // 現在の状態
  AppState* state_;
  // 避難者番号読み取り後の状態
  AppState* state_after_read_refugee_num_;

  // モードを変える
  void shiftState(AppState* new_state);
};

#endif
