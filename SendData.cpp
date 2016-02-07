#include <Arduino.h>
#include <limits.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"
#include "SendData.h"

// コンストラクタ
SendData::SendData(InputApp* app, DeviceSet* devices) :
  ms_end_(ULONG_MAX),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void SendData::doSetup() {
  devices_->reader.turnOff();
  devices_->led_success.turnOff();
  devices_->led_error.turnOff();
  devices_->resetAllSwitches();

  // 通信の準備を行う
  printPreparing();
  prepareForCommunication();

  // データを送信する
  printSending();
  Serial.println(app_->getSendData());

  ms_end_ = millis() + TIME_LIMIT;
}

// メインループ
void SendData::doLoop() {
  if (millis() >= ms_end_) {
    // タイムアウトした場合
    devices_->xbee.sleep();

    printTimeout();
    devices_->led_error.blink(LED_BLINK_INTERVAL);
    delay(WAIT_TIME_AFTER_SEND);

    app_->reset();

    return;
  }

  if (devices_->sw_back.readState() == TactSwitch::SW_PUSHED) {
    app_->reset();
    return;
  }

  if (Serial.available() > 0) {
    char result_ch = Serial.read();

    devices_->xbee.sleep();
    processReply(result_ch);
    delay(WAIT_TIME_AFTER_SEND);

    app_->reset();

    return;
  }
}

// 通信の準備を行う
void SendData::prepareForCommunication() {
  devices_->xbee.wakeUp();

  // シリアル通信の読み残しがあれば、すべて読んで残りデータを空にする
  while (Serial.available() > 0) {
    Serial.read();
  }
}

// 返信を処理する
void SendData::processReply(char result_ch) {
  switch (result_ch) {
  case 'R':
    printRegistered();
    devices_->led_success.blink(LED_BLINK_INTERVAL);

    break;
  case 'U':
    printUpdated();
    devices_->led_success.blink(LED_BLINK_INTERVAL);

    break;
  default:
    printError();
    devices_->led_error.blink(LED_BLINK_INTERVAL);

    break;
  }
}

// 通信準備中表示
void SendData::printPreparing() {
  devices_->lcd.setCursor(0, 1);
  // "ツウシンジュンビチュウ"
  devices_->lcd.print(F("\xC2\xB3\xBC\xDD\xBC\xDE\xAD\xDD\xCB\xDE\xC1\xAD\xB3   "));
}

// 送信中表示
void SendData::printSending() {
  devices_->lcd.setCursor(0, 1);
  // "ソウシンチュウ"
  devices_->lcd.print(F("\xBF\xB3\xBC\xDD\xC1\xAD\xB3         "));
}

// 登録完了表示
void SendData::printRegistered() {
  devices_->lcd.setCursor(0, 1);
  // "トウロクシマシタ"
  devices_->lcd.print(F("\xC4\xB3\xDB\xB8\xBC\xCF\xBC\xC0        "));
}

// 更新完了表示
void SendData::printUpdated() {
  devices_->lcd.setCursor(0, 1);
  // "コウシンシマシタ"
  devices_->lcd.print(F("\xBA\xB3\xBC\xDD\xBC\xCF\xBC\xC0        "));
}

// 登録失敗表示
void SendData::printError() {
  devices_->lcd.setCursor(0, 1);
  // "トウロクデキマセンデシタ"
  devices_->lcd.print(F("\xC4\xB3\xDB\xB8\xC3\xDE\xB7\xCF\xBE\xDD\xC3\xDE\xBC\xC0  "));
}

// タイムアウト表示
void SendData::printTimeout() {
  devices_->lcd.setCursor(0, 1);
  // "タイムアウト"
  devices_->lcd.print(F("\xC0\xB2\xD1\xB1\xB3\xC4          "));
}
