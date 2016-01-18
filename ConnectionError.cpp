#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "XBeeSleepController.h"
#include "Led.h"
#include "TactSwitch.h"
#include "InputApp.h"
#include "DeviceSet.h"
#include "ConnectionError.h"

// コンストラクタ
ConnectionError::ConnectionError(InputApp* app, DeviceSet* devices) :
  switch_message_time_(),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void ConnectionError::doSetup() {
  devices_->xbee.sleep();
  devices_->led_success.turnOff();
  devices_->led_error.turnOn();

  message_ = 0;
  switch_message_time_ = millis() + MESSAGE_INTERVAL;

  printConfirmServer();
}

// メインループ
void ConnectionError::doLoop() {
  if (devices_->sw_reset.readState() == TactSwitch::SW_PUSHED) {
    app_->shiftToConfirmConnection();
    return;
  }

  unsigned long current_time = millis();
  if (current_time >= switch_message_time_) {
    switch_message_time_ = current_time + MESSAGE_INTERVAL;
    message_ = (message_ + 1) % 2;

    if (message_ == 0) {
      printConfirmServer();
    } else {
      printPressResetButton();
    }
  }
}

// サーバー確認表示
void ConnectionError::printConfirmServer() {
  devices_->lcd.setCursor(0, 0);
  // サーバーヲカクニン
  devices_->lcd.print("\xBB\xB0\xCA\xDE\xB0\xA6\xB6\xB8\xC6\xDD     ");

  devices_->lcd.setCursor(0, 1);
  // シテクダサイ
  devices_->lcd.print("\xBC\xC3\xB8\xC0\xDE\xBB\xB2        ");
}

// リセットボタン押下指示表示
void ConnectionError::printPressResetButton() {
  devices_->lcd.setCursor(0, 0);
  // リセットボタンデ
  devices_->lcd.print("\xD8\xBE\xAF\xC4\xCE\xDE\xC0\xDD\xC3\xDE     ");

  devices_->lcd.setCursor(0, 1);
  // サイセツゾクシマス
  devices_->lcd.print("\xBB\xB2\xBE\xC2\xBF\xDE\xB8\xBC\xCF\xBD     ");
}
