#include <Arduino.h>
#include "Led.h"

Led::Led(int pin) :
  pin_(pin)
{
}

// 点灯させる
void Led::turnOn() {
  digitalWrite(pin_, LOW);
}

// 消灯させる
void Led::turnOff() {
  digitalWrite(pin_, HIGH);
}

// 点滅させる
void Led::blink(int interval) {
  for (int i = 0; i < 6; ++i) {
    if (i & 1) {
      turnOff();
    } else {
      turnOn();
    }

    delay(interval);
  }
}
