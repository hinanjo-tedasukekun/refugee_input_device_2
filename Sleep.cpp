#include <Arduino.h>
#include <avr/sleep.h>
#include "I2CLiquidCrystal.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"
#include "InputApp.h"
#include "Sleep.h"

// スリープ解除時の割り込み関数
static void sleepInt() {
  // 何もしない
}

// コンストラクタ
Sleep::Sleep(InputApp* app, DeviceSet* devices) :
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void Sleep::doSetup() {
  // 各デバイスをオフにする
  devices_->reader.turnOff();
  devices_->xbee.sleep();
  devices_->led_success.turnOff();
  devices_->led_error.turnOff();

  devices_->lcd.setCursor(0, 0);
  // "スリープモード"
  devices_->lcd.print(F("\xBD\xD8\xB0\xCC\xDF\xD3\xB0\xC4\xDE       "));

  devices_->lcd.setCursor(0, 1);
  // "「ツギヘ」でカイジョシマス
  devices_->lcd.print(F("\xA2\xC2\xB7\xDE\xCD\xA3\xC3\xDE\xB6\xB2\xBC\xDE\xAE\xBC\xCF\xBD"));

  // スリープモードと割り込みを設定する
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // 割り込み設定の際は割り込みを無効にしておく
  noInterrupts();
  attachInterrupt(digitalPinToInterrupt(DeviceSet::PIN_INT), sleepInt, LOW);
  sleep_enable();

  // 割り込みを有効にしてからスリープモードに入る
  interrupts();
}

// メインループ
void Sleep::doLoop() {
  // スリープする
  sleep_cpu();

  // スリープを無効にし、割り込み関数を除く
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(DeviceSet::PIN_INT));

  // 接続確認から再開する
  app_->shiftToConfirmConnection();
}
