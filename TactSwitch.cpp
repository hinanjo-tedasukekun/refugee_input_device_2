#include <Arduino.h>

#include "TactSwitch.h"

TactSwitch::TactSwitch(const int pin, const int push_count) :
  pin_(pin),
  push_count_(push_count),
  down_count_(0)
{
}

// 状態をリセットする
void TactSwitch::reset() {
  down_count_ = 0;
}

// 押下状態を読み込む
TactSwitch::State TactSwitch::readState() {
  if (digitalRead(pin_) == LOW) {
    // スイッチが下がっている場合
    if (down_count_ < push_count_) {
      ++down_count_;
    }

    return SW_DOWN;
  }

  // スイッチが上がっている場合
  State state = (down_count_ >= push_count_) ? SW_PUSHED : SW_UP;
  down_count_ = 0;
  return state;
}
