#ifndef SEND_DATA_H
#define SEND_DATA_H

#include "I2CLiquidCrystal.h"

#include "TactSwitch.h"

class InputApp;

class SendData {
private:
  // 送信後リセットするまでの待ち時間 [ms]
  static const int WAIT_TIME_AFTER_SEND = 2100;

  InputApp* app_;
  I2CLiquidCrystal* lcd_;
  TactSwitch sw_reset_;

public:
  SendData(InputApp* app, I2CLiquidCrystal* lcd);
  void execute(String leader_id_, int num_of_members);

private:
  void printSending();
  void printRegistered();
  void printUpdated();
  void printError();

  void blinkLed(int pin);
};

#endif
