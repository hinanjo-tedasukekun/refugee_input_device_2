#include "InputApp.h"
#include "DeviceSet.h"
#include "TactSwitch.h"
#include "TestMode.h"

TestMode::TestMode(InputApp* app, DeviceSet* devices) :
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void TestMode::doSetup() {
  devices_->lcd.setCursor(0, 0);
  devices_->lcd.print("SW Test         ");
  devices_->lcd.setCursor(0, 1);
  devices_->lcd.print("                ");

  devices_->resetAllSwitches();
}

// メインループ
void TestMode::doLoop() {
  handleSwEvents();
  delay(10);
}

// スイッチのイベントを処理する
void TestMode::handleSwEvents() {
  if (devices_->sw_reset.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed Reset    ");
    delay(500);
    app_->shiftToBlinkTest();
    return;
  }

  if (devices_->sw_1.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed 1        ");
    return;
  }

  if (devices_->sw_2.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed 2        ");
    return;
  }

  if (devices_->sw_3.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed 3        ");
    return;
  }

  if (devices_->sw_4.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed 4        ");
    return;
  }

  if (devices_->sw_plus.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed +        ");
    return;
  }

  if (devices_->sw_minus.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed -        ");
    return;
  }

  if (devices_->sw_enter.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed Enter    ");
    return;
  }

  if (devices_->sw_leave.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed Leave    ");
    return;
  }

  if (devices_->sw_send.readState() == TactSwitch::SW_PUSHED) {
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Pushed Send     ");
    return;
  }
}
