#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"
#include "RegisterFamilyData.h"

// コンストラクタ
RegisterFamilyData::RegisterFamilyData(InputApp* app, DeviceSet* devices) :
  num_of_members_(3),
  num_of_members_changed_(true),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void RegisterFamilyData::doSetup() {
  num_of_members_ = 3;
  num_of_members_changed_ = true;

  devices_->reader.turnOff();
  devices_->xbee.sleep();
  devices_->led_success.turnOff();
  devices_->led_error.turnOff();
  devices_->resetAllSwitches();

  devices_->lcd.setCursor(0, 0);
  // "バンゴウ"
  devices_->lcd.print(F("\xCA\xDE\xDD\xBA\xDE\xB3  "));
  devices_->lcd.print(app_->getRefugeeNum());

  devices_->lcd.setCursor(0, 1);
  // "セタイノニンズウ"
  devices_->lcd.print(F("\xBE\xC0\xB2\xC9\xC6\xDD\xBD\xDE\xB3       "));
}

// メインループ
void RegisterFamilyData::doLoop() {
  handleSwitchEvents();

  if (num_of_members_changed_) {
    num_of_members_changed_ = false;

    updateNumOnLcd();
  }
}

// スイッチのイベントを処理する
void RegisterFamilyData::handleSwitchEvents() {
  if (devices_->sw_back.readState() == TactSwitch::SW_PUSHED) {
    app_->reset();
    return;
  }

  if (devices_->sw_next.readState() == TactSwitch::SW_PUSHED) {
    setSendData();
    app_->shiftToSendData();

    return;
  }

  if (devices_->sw_plus.readState() == TactSwitch::SW_PUSHED) {
    if (num_of_members_ < 99) {
      setNumOfMembers(num_of_members_ + 1);
    }

    return;
  }

  if (devices_->sw_minus.readState() == TactSwitch::SW_PUSHED) {
    if (num_of_members_ > 1) {
      setNumOfMembers(num_of_members_ - 1);
    }

    return;
  }
}

// 世帯の人数を設定する
void RegisterFamilyData::setNumOfMembers(int num) {
  num_of_members_ = num;
  num_of_members_changed_ = true;
}

// LCD の人数表示を更新する
void RegisterFamilyData::updateNumOnLcd() {
  char num_str[] = "NN";

  num_str[0] = '0' + (num_of_members_ / 10);
  num_str[1] = '0' + (num_of_members_ % 10);

  devices_->lcd.setCursor(14, 1);
  devices_->lcd.print(num_str);
}

// 送信データを設定する
void RegisterFamilyData::setSendData() {
  String send_data("# ");

  send_data += app_->getRefugeeNum();
  send_data += ' ';
  send_data += num_of_members_;

  app_->setSendData(send_data);
}
