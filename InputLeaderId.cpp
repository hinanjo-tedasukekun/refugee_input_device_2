#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "SoftwareSerial.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "InputAppConfig.h"
#include "InputApp.h"
#include "TactSwitchWithLongPush.h"
#include "InputLeaderId.h"

InputLeaderId::InputLeaderId(
  InputApp* app, I2CLiquidCrystal* lcd, SoftwareSerial* reader_serial
) :
  ring_buffer_(),
  leader_id_changed_(false),
  ms_end_(ULONG_MAX),
  app_(app),
  lcd_(lcd),
  reader_serial_(reader_serial),
  sw_reset_(InputAppConfig::PIN_SW_RESET, InputAppConfig::SW_SHORT_PUSH_COUNT),
  sw_read_(
    InputAppConfig::PIN_SW_SEND,
    InputAppConfig::SW_SHORT_PUSH_COUNT,
    InputAppConfig::SW_LONG_PUSH_COUNT
  )
{
}

void InputLeaderId::reset() {
  ring_buffer_.clear();
  leader_id_changed_ = false;

  sw_reset_.reset();
  sw_read_.reset();

  // シリアル通信の読み残しがあれば、すべて読んで残りデータを空にする
  while (reader_serial_->available() > 0) {
    reader_serial_->read();
  }

  ms_end_ = millis() + InputAppConfig::INPUT_LEADER_ID_TIME_LIMIT;
}

void InputLeaderId::setupPorts() {
  // バーコードリーダーの電源を入れる
  digitalWrite(InputAppConfig::PIN_READER_VCC, HIGH);
}

void InputLeaderId::setupLcd() {
  lcd_->setCursor(0, 0);
  lcd_->print("\xCA\xDE\xDD\xBA\xDE\xB3         "); // "バンゴウ"

  lcd_->setCursor(0, 1);
  // "バーコードヨミトリ"
  lcd_->print("\xCA\xDE\xB0\xBA\xB0\xC4\xDE\xD6\xD0\xC4\xD8    ");
}

void InputLeaderId::loop() {
  if (millis() > ms_end_) {
    // 制限時間を過ぎた場合、節電のため強制終了する
    app_->reset();
    return;
  }

  if (sw_reset_.readState() == TactSwitch::SW_PUSHED) {
    app_->reset();
    return;
  }

  if (sw_read_.readState() == TactSwitchWithLongPush::SW_PUSHED_LONG) {
    readSampleLeaderId();
    app_->setLeaderId(ring_buffer_.toString());
    updateLeaderIdOnLcd();

    return;
  }

  if (reader_serial_->available() > 0) {
    char c = reader_serial_->read();

    if (c == '\n') {
      app_->setLeaderId(ring_buffer_.toString());
      return;
    }

    ring_buffer_.pushBack(c);
    updateLeaderIdOnLcd();
  }
}

// 代表者番号の例を読み込む
void InputLeaderId::readSampleLeaderId() {
  ring_buffer_.clear();

  ring_buffer_.pushBack('0');
  ring_buffer_.pushBack('1');
  ring_buffer_.pushBack('9');
  ring_buffer_.pushBack('0');
  ring_buffer_.pushBack('0');
  ring_buffer_.pushBack('0');
  ring_buffer_.pushBack('1');
  ring_buffer_.pushBack('9');
}

void InputLeaderId::updateLeaderIdOnLcd() {
  lcd_->setCursor(7, 0);
  lcd_->print(ring_buffer_.toString());
}
