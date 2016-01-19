#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"
#include "SetPresence.h"

// コンストラクタ
SetPresence::SetPresence(InputApp* app, DeviceSet* devices) :
  present_(true),
  presence_changed_(true),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void SetPresence::doSetup() {
  present_ = true;
  presence_changed_ = true;

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
  // "ニュウシツ タイシツ"
  devices_->lcd.print(" \xC6\xAD\xB3\xBC\xC2      \xC0\xB2\xBC\xC2");
}

// メインループ
void SetPresence::doLoop() {
  handleSwitchEvents();

  if (presence_changed_) {
    presence_changed_ = false;

    updatePresenceOnLcd();
  }
}

// スイッチのイベントを処理する
void SetPresence::handleSwitchEvents() {
  if (devices_->sw_reset.readState() == TactSwitch::SW_PUSHED) {
    app_->reset();
    return;
  }

  if (devices_->sw_send.readState() == TactSwitch::SW_PUSHED) {
    setSendData();
    app_->shiftToSendData();

    return;
  }

  if (devices_->sw_enter.readState() == TactSwitch::SW_PUSHED) {
    present_ = true;
    presence_changed_ = true;

    return;
  }

  if (devices_->sw_leave.readState() == TactSwitch::SW_PUSHED) {
    present_ = false;
    presence_changed_ = true;

    return;
  }
}

// LCD の在室情報表示を更新する
void SetPresence::updatePresenceOnLcd() {
  // 反対側の '*' を消す
  devices_->lcd.setCursor((present_ ? 11 : 0), 1);
  devices_->lcd.print(' ');

  // '*' を表示する
  devices_->lcd.setCursor((present_ ? 0 : 11), 1);
  devices_->lcd.print('*');
}

// 送信データを設定する
void SetPresence::setSendData() {
  String send_data("P ");

  send_data += app_->getRefugeeNum();
  send_data += ' ';
  send_data += (present_ ? '1' : '0');

  app_->setSendData(send_data);
}
