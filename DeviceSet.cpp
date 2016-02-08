#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "SoftwareSerial.h"
#include "BarcodeReaderPowerController.h"
#include "XBeeSleepController.h"
#include "Led.h"
#include "TactSwitch.h"
#include "DeviceSet.h"

// コンストラクタ
DeviceSet::DeviceSet() :
  reader(PIN_READER_SW, PIN_COM_RECEIVER_EN),
  xbee(PIN_XBEE_SLEEP),
  led_success(PIN_LED_SUCCESS),
  led_error(PIN_LED_ERROR),
  sw_plus(PIN_SW_PLUS, SW_PUSH_COUNT),
  sw_minus(PIN_SW_MINUS, SW_PUSH_COUNT),
  sw_next(PIN_SW_NEXT, SW_PUSH_COUNT),
  sw_back(PIN_SW_BACK, SW_PUSH_COUNT),
  lcd(LCD_CONTRAST, (bool)false),
  reader_serial(PIN_READER_RX, PIN_READER_TX)
{
}

// デバイスの初期設定を行う
void DeviceSet::setup() {
  int output_pins[] = {
    PIN_XBEE_SLEEP,
    PIN_READER_SW,
    PIN_COM_RECEIVER_EN,
    PIN_COM_SHUTDOWN,
    PIN_LED_SUCCESS,
    PIN_LED_ERROR
  };

  int pull_up_pins[] = {
    PIN_INT,
    PIN_SW_PLUS,
    PIN_SW_MINUS,
    PIN_SW_NEXT,
    PIN_SW_BACK
  };

  for (auto pin : output_pins) {
    pinMode(pin, OUTPUT);
  }

  for (auto pin : pull_up_pins) {
    digitalWrite(pin, HIGH);
  }

  // バーコードリーダーの TX は使わないので
  // トランスミッタは常にシャットダウンしておく
  digitalWrite(PIN_COM_SHUTDOWN, LOW);

  reader.turnOff();
  xbee.sleep();

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
    &sw_plus,
    &sw_minus,
    &sw_next,
    &sw_back
  };

  for (auto sw : switches) {
    sw->reset();
  }
}
