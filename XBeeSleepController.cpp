/*
 * XBee スリープ制御クラス
 */

#include <Arduino.h>

#include "XBeeSleepController.h"

// コンストラクタ
XBeeSleepController::XBeeSleepController(int pin) :
  pin_(pin)
{
}

// スリープモードにする
void XBeeSleepController::sleep() {
  digitalWrite(pin_, HIGH);
}

// スリープモードを解除する
void XBeeSleepController::wakeUp() {
  digitalWrite(pin_, LOW);
  delay(WAIT_TIME_FOR_WAKE_UP);
}
