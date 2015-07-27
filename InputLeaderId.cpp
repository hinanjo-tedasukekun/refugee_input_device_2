#include <Arduino.h>
#include "LiquidCrystal.h"
#include "SoftwareSerial.h"
#include <stdio.h>
#include <string.h>

#include "InputAppConfig.h"
#include "InputApp.h"
#include "TactSwitchWithLongPush.h"
#include "InputLeaderId.h"

InputLeaderId::InputLeaderId(
  InputApp* app, LiquidCrystal* lcd, SoftwareSerial* reader_serial
) :
  ring_buffer_(),
  leader_id_changed_(false),
  app_(app),
  lcd_(lcd),
  reader_serial_(reader_serial),
  input_sw_(
    InputAppConfig::PIN_SW_RESET,
    InputAppConfig::SW_SHORT_PUSH_COUNT
  )
{
}

void InputLeaderId::reset() {
  ring_buffer_.clear();
  leader_id_changed_ = false;

  input_sw_.reset();
}

void InputLeaderId::setupPorts() {
  digitalWrite(InputAppConfig::PIN_READER_VCC, LOW);
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

  if (reader_serial_->available() > 0) {
    char c = reader_serial_->read();

    if (c == '\n') {
      app_->setLeaderId(ring_buffer_.toString());
      delay(100);
      digitalWrite(InputAppConfig::PIN_READER_VCC, LOW);

      return;
    }

    ring_buffer_.pushBack(c);
    updateLeaderIdOnLcd();
  }
}

void InputLeaderId::handleInputSwEvent(TactSwitch::SwitchState state) {
  switch (state) {
  case TactSwitch::SW_PUSHED:
    inputSwPushed();
    break;
  default:
    break;
  }
}

void InputLeaderId::inputSwPushed() {
}

void InputLeaderId::updateLeaderIdOnLcd() {
  lcd_->setCursor(7, 0);
  lcd_->print(ring_buffer_.toString());
}
