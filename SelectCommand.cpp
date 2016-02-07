#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"
#include "SelectCommand.h"

// コマンド
const char* SelectCommand::COMMANDS[] = {
  // "1. セタイノニンズウ"
  "1. \xBE\xC0\xB2\xC9\xC6\xDD\xBD\xDE\xB3    ",
  // "2. ニュウシツ・タイシツ"
  "2. \xC6\xAD\xB3\xBC\xC2\xA5\xC0\xB2\xBC\xC2   "
};

// コマンドの総数
const int SelectCommand::N_COMMANDS = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

// コンストラクタ
SelectCommand::SelectCommand(InputApp* app, DeviceSet* devices) :
  selected_(0),
  command_changed_(true),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void SelectCommand::doSetup() {
  command_changed_ = true;

  devices_->reader.turnOff();
  devices_->xbee.sleep();
  devices_->led_success.turnOff();
  devices_->led_error.turnOff();
  devices_->resetAllSwitches();

  devices_->lcd.setCursor(0, 1);
  // "+-デエランデクダサイ"
  devices_->lcd.print(F("+-\xC3\xDE\xB4\xD7\xDD\xC3\xDE\xB8\xC0\xDE\xBB\xB2  "));
}

// メインループ
void SelectCommand::doLoop() {
  handleSwitchEvents();

  if (command_changed_) {
    command_changed_ = false;

    devices_->lcd.setCursor(0, 0);
    devices_->lcd.print(COMMANDS[selected_]);
  }
}

// スイッチのイベントを処理する
void SelectCommand::handleSwitchEvents() {
  if (devices_->sw_minus.readState() == TactSwitch::SW_PUSHED) {
    if (selected_ > 0) {
      --selected_;
      command_changed_ = true;
      return;
    }
  }

  if (devices_->sw_plus.readState() == TactSwitch::SW_PUSHED) {
    if (selected_ < N_COMMANDS - 1) {
      ++selected_;
      command_changed_ = true;
      return;
    }
  }

  if (devices_->sw_next.readState() == TactSwitch::SW_PUSHED) {
    switch (selected_) {
    case 0:
      app_->shiftToRegisterFamilyData();
      break;
    case 1:
      app_->shiftToSetPresence();
      break;
    default:
      app_->reset();
      break;
    }

    return;
  }
}
