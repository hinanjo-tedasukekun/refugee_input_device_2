#include "Arduino.h"
#include "InputAppConfig.h"

// バーコードリーダー電源制御ピン
const int InputAppConfig::PIN_READER_VCC = A1;
// バーコードリーダー RX ピン
const int InputAppConfig::PIN_READER_RX = A3;
// バーコードリーダー TX ピン
const int InputAppConfig::PIN_READER_TX = A2;

// 送信成功 LED ピン
const int InputAppConfig::PIN_LED_SUCCESS = 4;
// エラー LED ピン
const int InputAppConfig::PIN_LED_ERROR = 3;

// 「1人」ボタンピン
const int InputAppConfig::PIN_SW_1 = 5;
// 「2人」ボタンピン
const int InputAppConfig::PIN_SW_2 = 12;
// 「3人」ボタンピン
const int InputAppConfig::PIN_SW_3 = 6;
// 「4人」ボタンピン
const int InputAppConfig::PIN_SW_4 = 10;
// 「＋」ボタンピン
const int InputAppConfig::PIN_SW_PLUS = 13;
// 「＋」ボタンピン
const int InputAppConfig::PIN_SW_MINUS = 11;
// 「入室」ボタンピン
const int InputAppConfig::PIN_SW_ENTER = 7;
// 「退室」ボタンピン
const int InputAppConfig::PIN_SW_LEAVE = 8;
// 「送信」ボタンピン
const int InputAppConfig::PIN_SW_SEND = 9;

// リセットボタンピン
const int InputAppConfig::PIN_SW_RESET = A0;

// ボタンが押されたと判断するまでのカウント数
const int InputAppConfig::SW_SHORT_PUSH_COUNT = 5;
// ボタンが長押しされたと判断するまでのカウント数
const int InputAppConfig::SW_LONG_PUSH_COUNT = 50;

// 代表者番号入力の制限時間（ミリ秒単位）
const unsigned long InputAppConfig::INPUT_LEADER_ID_TIME_LIMIT = 15 * 1000;
