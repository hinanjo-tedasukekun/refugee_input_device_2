#include <Arduino.h>
#include "I2CLiquidCrystal.h"

#include "InputAppConfig.h"
#include "InputApp.h"
#include "TactSwitch.h"
#include "InputNumOfMembers.h"

// コンストラクタ
InputNumOfMembers::InputNumOfMembers(InputApp* app, I2CLiquidCrystal* lcd) :
  num_of_members_(1),
  num_of_members_changed_(false),
  app_(app),
  lcd_(lcd),
  sw_1_(InputAppConfig::PIN_SW_1, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_2_(InputAppConfig::PIN_SW_2, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_3_(InputAppConfig::PIN_SW_3, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_4_(InputAppConfig::PIN_SW_4, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_plus_(InputAppConfig::PIN_SW_PLUS, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_minus_(InputAppConfig::PIN_SW_MINUS, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_send_(InputAppConfig::PIN_SW_SEND, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_reset_(InputAppConfig::PIN_SW_RESET, InputAppConfig::SW_SHORT_PUSH_COUNT),
  switches_ {
    &sw_1_, &sw_2_, &sw_3_, &sw_4_,
    &sw_plus_, &sw_minus_, &sw_send_, &sw_reset_
  }
{
}

// 状態をリセットする
void InputNumOfMembers::reset() {
  num_of_members_ = 1;
  num_of_members_changed_ = false;

  for (TactSwitch* sw : switches_) {
    sw->reset();
  }
}

// IO ポートを初期状態にする
void InputNumOfMembers::setupPorts() {
  // バーコードリーダーの電源を切る
  digitalWrite(InputAppConfig::PIN_READER_VCC, LOW);
}

// LCD を初期状態にする
void InputNumOfMembers::setupLcd() {
  lcd_->setCursor(0, 1);
  lcd_->print("\xC6\xDD\xBD\xDE\xB3          "); // "ニンズウ"

  updateNumOnLcd();
}

// メインループ
void InputNumOfMembers::loop() {
  handleSwitchEvents();

  if (num_of_members_changed_) {
    num_of_members_changed_ = false;
    updateNumOnLcd();
  }
}

void InputNumOfMembers::handleSwitchEvents() {
  if (sw_reset_.readState() == TactSwitch::SW_PUSHED) {
    app_->reset();
    return;
  }

  if (sw_1_.readState() == TactSwitch::SW_PUSHED) {
    setNumOfMembers(1);
    return;
  }

  if (sw_2_.readState() == TactSwitch::SW_PUSHED) {
    setNumOfMembers(2);
    return;
  }

  if (sw_3_.readState() == TactSwitch::SW_PUSHED) {
    setNumOfMembers(3);
    return;
  }

  if (sw_4_.readState() == TactSwitch::SW_PUSHED) {
    setNumOfMembers(4);
    return;
  }

  if (sw_plus_.readState() == TactSwitch::SW_PUSHED) {
    if (num_of_members_ < 99) {
      setNumOfMembers(num_of_members_ + 1);
    }

    return;
  }

  if (sw_minus_.readState() == TactSwitch::SW_PUSHED) {
    if (num_of_members_ > 1) {
      setNumOfMembers(num_of_members_ - 1);
    }

    return;
  }

  if (sw_send_.readState() == TactSwitch::SW_PUSHED) {
    app_->setNumOfMembers(num_of_members_);
    return;
  }
}

void InputNumOfMembers::updateNumOnLcd() {
  char num_str[] = "NN";

  num_str[0] = '0' + (num_of_members_ / 10);
  num_str[1] = '0' + (num_of_members_ % 10);

  lcd_->setCursor(6, 1);
  lcd_->print(num_str);
}

void InputNumOfMembers::setNumOfMembers(int num) {
  num_of_members_ = num;
  num_of_members_changed_ = true;
}
