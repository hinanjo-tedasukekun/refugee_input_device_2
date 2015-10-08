#ifndef INPUT_APP_CONFIG_H
#define INPUT_APP_CONFIG_H

struct InputAppConfig {
  static const int LEADER_ID_LENGTH = 8;

  // XBee スリープ制御ピン
  static const int PIN_XBEE_SLEEP;

  // バーコードリーダー電源制御ピン
  static const int PIN_READER_VCC;
  // バーコードリーダー RX ピン
  static const int PIN_READER_RX;
  // バーコードリーダー TX ピン
  static const int PIN_READER_TX;

  // 送信成功 LED ピン
  static const int PIN_LED_SUCCESS;
  // エラー LED ピン
  static const int PIN_LED_ERROR;

  // 「1人」ボタンピン
  static const int PIN_SW_1;
  // 「2人」ボタンピン
  static const int PIN_SW_2;
  // 「3人」ボタンピン
  static const int PIN_SW_3;
  // 「4人」ボタンピン
  static const int PIN_SW_4;
  // 「＋」ボタンピン
  static const int PIN_SW_PLUS;
  // 「−」ボタンピン
  static const int PIN_SW_MINUS;
  // 「入室」ボタンピン
  static const int PIN_SW_ENTER;
  // 「退室」ボタンピン
  static const int PIN_SW_LEAVE;
  // 「送信」ボタンピン
  static const int PIN_SW_SEND;

  // リセットボタンピン
  static const int PIN_SW_RESET;

  // ボタンが押されたと判断するまでのカウント数
  static const int SW_SHORT_PUSH_COUNT;
  // ボタンが長押しされたと判断するまでのカウント数
  static const int SW_LONG_PUSH_COUNT;

  // 代表者番号入力の制限時間 [ms]
  static const unsigned long INPUT_LEADER_ID_TIME_LIMIT;

  // XBee ネットワーク参加待ち時間 [ms]
  static const int WAIT_TIME_FOR_JOIN_TO_NETWORK;
  // XBee のスリープ解除待ち時間 [ms]
  static const int WAIT_TIME_FOR_XBEE_WAKE_UP;
  // 送信後リセットするまでの待ち時間 [ms]
  static const int WAIT_TIME_AFTER_SEND;
};

#endif
