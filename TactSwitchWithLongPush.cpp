#include <Arduino.h>

#include "TactSwitchWithLongPush.h"

TactSwitchWithLongPush::TactSwitchWithLongPush(
  const int pin,
  const unsigned int short_push_count,
  const unsigned int long_push_count
) :
  pin_(pin),
  short_push_count_(short_push_count),
  long_push_count_(long_push_count),
  down_count_(0)
{
}

void TactSwitchWithLongPush::reset() {
  down_count_ = 0;
}

TactSwitchWithLongPush::SwitchState TactSwitchWithLongPush::readState() {
  if (digitalRead(pin_) == LOW) {
    // スイッチが下がっている場合
    if (down_count_ < long_push_count_) {
      ++down_count_;
    }

    return SW_DOWN;
  }

  // スイッチが上がっている場合
  SwitchState state;

  if (down_count_ >= long_push_count_) {
    state = SW_PUSHED_LONG;
  } else if (down_count_ >= short_push_count_) {
    state = SW_PUSHED_SHORT;
  } else {
    state = SW_UP;
  }

  down_count_ = 0;

  return state;
}
