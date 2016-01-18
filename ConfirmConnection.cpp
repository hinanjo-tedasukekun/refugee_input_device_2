#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "XBeeSleepController.h"
#include "Led.h"
#include "InputApp.h"
#include "DeviceSet.h"
#include "ConfirmConnection.h"

// コンストラクタ
ConfirmConnection::ConfirmConnection(InputApp* app, DeviceSet* devices) :
  send_count_(0),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void ConfirmConnection::doSetup() {
  send_count_ = 0;

  devices_->reader.turnOff();

  devices_->led_success.turnOff();
  devices_->led_error.turnOff();
  printConnecting();

  devices_->xbee.wakeUp();
  Serial.setTimeout(1000);

  // シリアル通信の読み残しがあれば、すべて読んで残りデータを空にする
  while (Serial.available() > 0) {
    Serial.read();
  }
}

// メインループ
void ConfirmConnection::doLoop() {
  if (send_count_ > MAX_RETRY) {
    app_->shiftToConnectionError();
    return;
  }

  char reply[2] = {};

  Serial.print('C');
  // タイムアウトを考慮するため、readBytes を使う
  Serial.readBytes(reply, 1);

  if (reply[0] == 'A') {
    // Acknowledgement が返ってきたら接続確認成功
    app_->shiftToSelectCommand();
    return;
  }

  ++send_count_;
}

// 接続中表示
void ConfirmConnection::printConnecting() {
  devices_->lcd.setCursor(0, 0);
  // サーバーニセツゾクチュウ
  devices_->lcd.print("\xBB\xB0\xCA\xDE\xB0\xC6\xBE\xC2\xBF\xDE\xB8\xC1\xAD\xB3 ");

  devices_->lcd.setCursor(0, 1);
  devices_->lcd.print("                ");
}
