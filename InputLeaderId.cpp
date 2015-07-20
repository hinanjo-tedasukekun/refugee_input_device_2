#include <Arduino.h>
#include "LiquidCrystal.h"
#include <stdio.h>
#include <string.h>

#include "InputAppConfig.h"
#include "InputApp.h"
#include "TactSwitchWithLongPush.h"
#include "InputLeaderId.h"

InputLeaderId::InputLeaderId(InputApp* app, LiquidCrystal* lcd) :
  LEADER_ID_FORMAT("%08d"),
  leader_id_ {},
  leader_id_changed_(false),
  app_(app),
  lcd_(lcd),
  input_sw_(
    InputAppConfig::PIN_SW_RESET,
    InputAppConfig::SW_SHORT_PUSH_COUNT,
    InputAppConfig::SW_LONG_PUSH_COUNT
  )
{
}

void InputLeaderId::reset() {
  memset(leader_id_, '\0', 9);
  leader_id_changed_ = false;

  input_sw_.reset();
}

void InputLeaderId::setupLeds() {
  digitalWrite(InputAppConfig::PIN_LED_SUCCESS, HIGH);
  digitalWrite(InputAppConfig::PIN_LED_ERROR, HIGH);
}

void InputLeaderId::setupLcd() {
  lcd_->setCursor(0, 0);
  lcd_->print("\xCA\xDE\xDD\xBA\xDE\xB3         "); // "バンゴウ"

  lcd_->setCursor(0, 1);
  // "バーコードヨミトリ"
  lcd_->print("\xCA\xDE\xB0\xBA\xB0\xC4\xDE\xD6\xD0\xC4\xD8    ");
}

void InputLeaderId::loop() {
  handleInputSwEvent(input_sw_.readState());

  if (leader_id_changed_) {
    leader_id_changed_ = false;

    app_->setLeaderId(static_cast<const char*>(leader_id_));
    updateLeaderIdOnLcd();
  }
}

void InputLeaderId::handleInputSwEvent(
  TactSwitchWithLongPush::SwitchState state
) {
  switch (state) {
  case TactSwitchWithLongPush::SW_PUSHED_SHORT:
    inputSwPushedShort();
    break;
  case TactSwitchWithLongPush::SW_PUSHED_LONG:
    inputSwPushedLong();
    break;
  default:
    break;
  }
}

void InputLeaderId::inputSwPushedShort() {
  sprintf(leader_id_, LEADER_ID_FORMAT, 123);
  leader_id_changed_ = true;
}

void InputLeaderId::inputSwPushedLong() {
  sprintf(leader_id_, LEADER_ID_FORMAT, (int)random(1, 1000));
  leader_id_changed_ = true;
}

void InputLeaderId::updateLeaderIdOnLcd() {
  lcd_->setCursor(7, 0);
  lcd_->print(leader_id_);
}
