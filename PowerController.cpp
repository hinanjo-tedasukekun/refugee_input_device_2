#include <Arduino.h>
#include "PowerController.h"

// コンストラクタ
PowerController::PowerController(int pin) :
  pin_(pin)
{
}
// 電源を入れる
void PowerController::turnOn() {
  digitalWrite(pin_, HIGH);
}

// 電源を切る
void PowerController::turnOff() {
  digitalWrite(pin_, LOW);
}
