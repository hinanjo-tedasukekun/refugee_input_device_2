#include <Arduino.h>
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"

// コンストラクタ
DeviceSet::DeviceSet() :
  led_success(PIN_LED_SUCCESS),
  led_error(PIN_LED_ERROR),
  sw_1(PIN_SW_1, SW_PUSH_COUNT),
  sw_2(PIN_SW_2, SW_PUSH_COUNT),
  sw_3(PIN_SW_3, SW_PUSH_COUNT),
  sw_4(PIN_SW_4, SW_PUSH_COUNT),
  sw_plus(PIN_SW_PLUS, SW_PUSH_COUNT),
  sw_minus(PIN_SW_MINUS, SW_PUSH_COUNT),
  sw_enter(PIN_SW_ENTER, SW_PUSH_COUNT),
  sw_leave(PIN_SW_LEAVE, SW_PUSH_COUNT),
  sw_send(PIN_SW_SEND, SW_PUSH_COUNT),
  sw_reset(PIN_SW_RESET, SW_PUSH_COUNT),
  lcd(LCD_CONTRAST, (bool)false),
  reader_serial(PIN_READER_RX, PIN_READER_TX)
{
}

// デバイスの初期設定を行う
void DeviceSet::setup() {
  int output_pins[] = {
    PIN_XBEE_SLEEP,
    PIN_READER_SW,
    PIN_LED_SUCCESS,
    PIN_LED_ERROR
  };

  int pull_up_pins[] = {
    PIN_SW_1,
    PIN_SW_2,
    PIN_SW_3,
    PIN_SW_4,
    PIN_SW_PLUS,
    PIN_SW_MINUS,
    PIN_SW_ENTER,
    PIN_SW_LEAVE,
    PIN_SW_SEND,
    PIN_SW_RESET
  };

  for (auto pin : output_pins) {
    pinMode(pin, OUTPUT);
  }

  for (auto pin : pull_up_pins) {
    digitalWrite(pin, HIGH);
  }

  led_success.turnOff();
  led_error.turnOff();

  resetAllSwitches();

  Serial.begin(SERIAL_BAUD_RATE);
  reader_serial.begin(READER_BAUD_RATE);

  lcd.begin(16, 2);
}

// すべてのスイッチの状態をリセットする
void DeviceSet::resetAllSwitches() {
  TactSwitch* switches[] = {
    &sw_1,
    &sw_2,
    &sw_3,
    &sw_4,
    &sw_plus,
    &sw_minus,
    &sw_enter,
    &sw_leave,
    &sw_send,
    &sw_reset
  };

  for (auto sw : switches) {
    sw->reset();
  }
}
