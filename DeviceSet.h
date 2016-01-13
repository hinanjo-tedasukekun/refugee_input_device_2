#ifndef DEVICE_SET_H
#define DEVICE_SET_H

#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "SoftwareSerial.h"
#include "TactSwitch.h"

// デバイス集合クラス
struct DeviceSet {
  // XBee スリープ制御ピン
  static constexpr int PIN_XBEE_SLEEP = 2;

  // バーコードリーダー電源制御ピン
  static constexpr int PIN_READER_VCC = A1;
  // バーコードリーダー RX ピン
  static constexpr int PIN_READER_RX = A3;
  // バーコードリーダー TX ピン
  static constexpr int PIN_READER_TX = A2;

  // 送信成功 LED ピン
  static constexpr int PIN_LED_SUCCESS = 4;
  // エラー LED ピン
  static constexpr int PIN_LED_ERROR = 3;

  // 「1人」ボタンピン
  static constexpr int PIN_SW_1 = 5;
  // 「2人」ボタンピン
  static constexpr int PIN_SW_2 = 12;
  // 「3人」ボタンピン
  static constexpr int PIN_SW_3 = 6;
  // 「4人」ボタンピン
  static constexpr int PIN_SW_4 = 10;
  // 「＋」ボタンピン
  static constexpr int PIN_SW_PLUS = 13;
  // 「−」ボタンピン
  static constexpr int PIN_SW_MINUS = 11;
  // 「入室」ボタンピン
  static constexpr int PIN_SW_ENTER = 7;
  // 「退室」ボタンピン
  static constexpr int PIN_SW_LEAVE = 8;
  // 「送信」ボタンピン
  static constexpr int PIN_SW_SEND = 9;

  // リセットボタンピン
  static constexpr int PIN_SW_RESET = A0;

  // 「1人」ボタン
  TactSwitch sw_1;
  // 「2人」ボタン
  TactSwitch sw_2;
  // 「3人」ボタン
  TactSwitch sw_3;
  // 「4人」ボタン
  TactSwitch sw_4;
  // 「＋」ボタン
  TactSwitch sw_plus;
  // 「−」ボタン
  TactSwitch sw_minus;
  // 「入室」ボタン
  TactSwitch sw_enter;
  // 「退室」ボタン
  TactSwitch sw_leave;
  // 「送信」ボタン
  TactSwitch sw_send;
  // リセットボタン
  TactSwitch sw_reset;

  // すべてのスイッチの状態をリセットする
  void resetAllSwitches();
};

#endif
