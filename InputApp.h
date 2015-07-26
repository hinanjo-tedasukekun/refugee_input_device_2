#ifndef INPUT_APP_H
#define INPUT_APP_H

#include "LiquidCrystal.h"

#include "InputAppConfig.h"
#include "InputLeaderId.h"
#include "InputNumOfMembers.h"
#include "SendData.h"

class InputLeaderId;

class InputApp {
public:
  // アプリケーションの状態を表す型
  enum AppState {
    STATE_INPUT_LEADER_ID,      // 代表者番号を入力する
    STATE_INPUT_NUM_OF_MEMBERS, // 家族の人数を入力する
    STATE_SEND_DATA             // 情報を送信する
  };

private:
  LiquidCrystal lcd_;

  InputLeaderId input_leader_id_;
  InputNumOfMembers input_num_of_members_;
  SendData send_data_;

  AppState state_;
  AppState prev_state_;

  String leader_id_;
  int num_of_members_;

public:
  InputApp();

  void setup();
  void reset();
  void loop();

  void setLeaderId(const char* leader_id);
  void setNumOfMembers(int num_of_members);
};

#endif
