#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"

// コンストラクタ
SelectCommand::SelectCommand(InputApp* app, DeviceSet* devices) :
  selected_(REGISTER_NUM_OF_MEMBERS),
  lcd_update_(true),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void SelectCommand::doSetup() {
  lcd_update_ = true;

  devices_->xbee.sleep();
  devices_->led_success.turnOff();
  devices_->led_error.turnOff();
  devices_->resetAllSwitches();

  devices_->lcd.setCursor(0, 1);
  // "+・-デエランデクダサイ"
  devices_->lcd.print("+\xA5-\xC3\xDE\xB4\xD7\xDD\xC3\xDE\xB8\xC0\xDE\xBB\xB2 ");
}

// メインループ
void SelectCommand::doLoop() {
  handleSwitchEvents();

  if (lcd_update_) {
    lcd_update_ = false;

    devices_->lcd.setCursor(0, 0);
    devices_->lcd.print(COMMAND_NAME[selected_]);
  }

  delay(10);
}

// スイッチのイベントを処理する
void SelectCommand::handleSwitchEvents() {
  if (devices_->sw_minus.readState() == TactSwitch::SW_PUSHED) {
    if (selected_ > 0) {
      --selected_;
      lcd_update_ = true;
      return;
    }
  }

  if (devices_->sw_plus.readState() == TactSwitch::SW_PUSHED) {
    if (selected_ < N_COMMANDS - 1) {
      ++selected_;
      lcd_update_ = true;
      return;
    }
  }
}
