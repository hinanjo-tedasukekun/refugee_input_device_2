#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"
#include "SetPresence.h"

// コンストラクタ
SetPresence::SetPresence(InputApp* app, DeviceSet* devices) :
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void SetPresence::doSetup() {
  devices_->reader.turnOff();
  devices_->xbee.sleep();
  devices_->led_success.turnOff();
  devices_->led_error.turnOff();
  devices_->resetAllSwitches();

  devices_->lcd.setCursor(0, 0);
  // "バンゴウ"
  devices_->lcd.print("\xCA\xDE\xDD\xBA\xDE\xB3  ");
  devices_->lcd.print(app_->getRefugeeNum());

  devices_->lcd.setCursor(0, 1);
  // "ニュウシツ・タイシツ"
  devices_->lcd.print("\xC6\xAD\xB3\xBC\xC2\xA5\xC0\xB2\xBC\xC2      ");
}

// メインループ
void SetPresence::doLoop() {
  handleSwitchEvents();
}

// スイッチのイベントを処理する
void SetPresence::handleSwitchEvents() {
  if (devices_->sw_reset.readState() == TactSwitch::SW_PUSHED) {
    app_->reset();
    return;
  }
}
