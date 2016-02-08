#include <Arduino.h>
#include "BarcodeReaderPowerController.h"

// コンストラクタ
BarcodeReaderPowerController::BarcodeReaderPowerController(
  int power_pin, int receiver_en_pin
) :
  power_pin_(power_pin),
  receiver_en_pin_(receiver_en_pin)
{
}
// 電源を入れる
void BarcodeReaderPowerController::turnOn() {
  digitalWrite(receiver_en_pin_, LOW);
  digitalWrite(power_pin_, HIGH);
}

// 電源を切る
void BarcodeReaderPowerController::turnOff() {
  digitalWrite(receiver_en_pin_, HIGH);
  digitalWrite(power_pin_, LOW);
}
