#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"
#include "RegisterFamilyData.h"

// コンストラクタ
RegisterFamilyData::RegisterFamilyData(InputApp* app, DeviceSet* devices) :
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void RegisterFamilyData::doSetup() {
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
  // "セタイノニンズウ"
  devices_->lcd.print("\xBE\xC0\xB2\xC9\xC6\xDD\xBD\xDE\xB3       ");
}

// メインループ
void RegisterFamilyData::doLoop() {
  handleSwitchEvents();
}

// スイッチのイベントを処理する
void RegisterFamilyData::handleSwitchEvents() {
  if (devices_->sw_reset.readState() == TactSwitch::SW_PUSHED) {
    app_->reset();
    return;
  }
}
