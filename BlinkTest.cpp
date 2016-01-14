#include "InputApp.h"
#include "DeviceSet.h"
#include "BlinkTest.h"

BlinkTest::BlinkTest(InputApp* app, DeviceSet* devices) :
  count_(0),
  app_(app),
  devices_(devices)
{
}

// 設定を行う
void BlinkTest::doSetup() {
  count_ = 0;

  devices_->led_success.turnOff();
  devices_->led_error.turnOff();

  devices_->lcd.setCursor(0, 0);
  devices_->lcd.print("LED Blink Test  ");
  devices_->lcd.setCursor(0, 1);
  devices_->lcd.print("                ");
}

// メインループ
void BlinkTest::doLoop() {
  switch (count_) {
  case 0:
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Success         ");
    devices_->led_success.turnOn();
    delay(1000);
    break;
  case 1:
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Error           ");
    devices_->led_success.turnOff();
    devices_->led_error.turnOn();
    delay(1000);
    break;
  case 2:
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Success blink   ");
    devices_->led_error.turnOff();
    devices_->led_success.blink(150);
    break;
  case 3:
    devices_->lcd.setCursor(0, 1);
    devices_->lcd.print("Error blink     ");
    devices_->led_error.blink(300);
    break;
  default:
    app_->shiftToTestMode();
    break;
  }

  ++count_;
}
