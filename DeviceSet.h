#ifndef DEVICE_SET_H
#define DEVICE_SET_H

#include <Arduino.h>
#include "I2CLiquidCrystal.h"
#include "SoftwareSerial.h"
#include "PowerController.h"
#include "XBeeSleepController.h"
#include "Led.h"
#include "TactSwitch.h"

// デバイス集合クラス
struct DeviceSet {
  // 割り込みピン
  static constexpr int PIN_INT = 2;

  // XBee スリープ制御ピン
  static constexpr int PIN_XBEE_SLEEP = A3;

  // バーコードリーダー電源制御ピン
  static constexpr int PIN_READER_SW = 13;
  // RS-232C レベル変換 IC レシーバピン
  static constexpr int PIN_COM_RECEIVER = 12;
  // RS-232C レベル変換 IC シャットダウンピン
  static constexpr int PIN_COM_SHUTDOWN = 11;
  // バーコードリーダー RX ピン
  static constexpr int PIN_READER_RX = 9;
  // バーコードリーダー TX ピン
  static constexpr int PIN_READER_TX = 10;

  // 送信成功 LED ピン
  static constexpr int PIN_LED_SUCCESS = A0;
  // エラー LED ピン
  static constexpr int PIN_LED_ERROR = A1;

  // 「＋」ボタンピン
  static constexpr int PIN_SW_PLUS = 6;
  // 「−」ボタンピン
  static constexpr int PIN_SW_MINUS = 5;

  // 「次へ」ボタンピン
  static constexpr int PIN_SW_NEXT = 8;
  // 「戻る」ボタンピン
  static constexpr int PIN_SW_BACK = 7;

  // LCD のコントラスト
  static constexpr int LCD_CONTRAST = 30;

  // シリアル通信のボーレート
  static constexpr int SERIAL_BAUD_RATE = 9600;
  // バーコードリーダーのボーレート
  static constexpr int READER_BAUD_RATE = 9600;

  // ボタンが押されたと判断するまでのカウント数
  static constexpr int SW_PUSH_COUNT = 5;

  // バーコードリーダー電源制御
  PowerController reader;
  // XBee スリープ制御
  XBeeSleepController xbee;

  // 送信成功 LED
  Led led_success;
  // エラー LED
  Led led_error;

  // 「＋」ボタン
  TactSwitch sw_plus;
  // 「−」ボタン
  TactSwitch sw_minus;

  // 「次へ」ボタン
  TactSwitch sw_next;
  // 「戻る」ボタン
  TactSwitch sw_back;

  // LCD
  I2CLiquidCrystal lcd;
  // バーコードリーダーのシリアル通信
  SoftwareSerial reader_serial;

  // コンストラクタ
  DeviceSet();
  // デバイスの初期設定を行う
  void setup();
  // すべてのスイッチの状態をリセットする
  void resetAllSwitches();
};

#endif
