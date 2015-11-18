#include <Arduino.h>
#include <string.h>

#include "InputAppConfig.h"
#include "InputApp.h"
#include "XBeeSleepController.h"
#include "TactSwitch.h"
#include "ConfirmConnection.h"

// コンストラクタ
ConfirmConnection::ConfirmConnection(InputApp* app, I2CLiquidCrystal* lcd) :
  app_(app),
  lcd_(lcd),
  xbee_(InputAppConfig::PIN_XBEE_SLEEP),
  sw_reset_(InputAppConfig::PIN_SW_RESET, InputAppConfig::SW_SHORT_PUSH_COUNT)
{
}

// サーバーとの接続を確認する
void ConfirmConnection::execute() {
  while (1) {
    // 準備
    printConnecting();
    prepareForCommunication();

    if (sendAcks()) {
      // 接続が確認できたら終了する
      return;
    }

    // 接続確認失敗
    waitForReset();
    reset();
  }
}

// 状態をリセットする
void ConfirmConnection::reset() {
  digitalWrite(InputAppConfig::PIN_LED_ERROR, HIGH);
  sw_reset_.reset();
}

// 通信の準備を行う
void ConfirmConnection::prepareForCommunication() {
  xbee_.wakeUp();
  delay(InputAppConfig::WAIT_TIME_FOR_XBEE_WAKE_UP);

  // シリアル通信の読み残しがあれば、すべて読んで残りデータを空にする
  while (Serial.available() > 0) {
    Serial.read();
  }
}

// ACK を送信する
// OK が返ってきたら true を返す
// 制限時間内に OK が返ってこなかったら false を返す
bool ConfirmConnection::sendAcks() {
  for (int i = 0; i <= MAX_RETRY; ++i) {
    char reply[4] = {};

    Serial.println("ACK");
    Serial.readBytesUntil('\r', reply, 3);

    if (strcmp(reply, "OK") == 0) {
      // OK が返ってきたら接続確認成功
      return true;
    }
  }

  // 接続確認失敗
  return false;
}

// リセットを待つ
void ConfirmConnection::waitForReset() {
  xbee_.sleep();
  digitalWrite(InputAppConfig::PIN_LED_ERROR, LOW);
  printConfirmServer();

  bool message_sw = false;
  unsigned long current_time = millis();
  unsigned long message_sw_time = current_time + MESSAGE_INTERVAL;

  while (1) {
    if (sw_reset_.readState() == TactSwitch::SW_PUSHED) {
      // リセットボタンが押されたら状態リセットに移行する
      return;
    }

    current_time = millis();
    if (current_time >= message_sw_time) {
      // LCD に表示するメッセージを切り替える
      message_sw_time = current_time + MESSAGE_INTERVAL;
      message_sw = !message_sw;

      if (message_sw) {
        printPressResetButton();
      } else {
        printConfirmServer();
      }
    }

    delay(10);
  }
}

// 接続中表示
void ConfirmConnection::printConnecting() {
  lcd_->setCursor(0, 0);
  // サーバーニセツゾクチュウ
  lcd_->print("\xBB\xB0\xCA\xDE\xB0\xC6\xBE\xC2\xBF\xDE\xB8\xC1\xAD\xB3 ");

  lcd_->setCursor(0, 1);
  lcd_->print("               ");
}

// サーバー確認表示
void ConfirmConnection::printConfirmServer() {
  lcd_->setCursor(0, 0);
  // サーバーヲカクニン
  lcd_->print("\xBB\xB0\xCA\xDE\xB0\xA6\xB6\xB8\xC6\xDD     ");

  lcd_->setCursor(0, 1);
  // シテクダサイ
  lcd_->print("\xBC\xC3\xB8\xC0\xDE\xBB\xB2        ");
}

// リセットボタン押下指示表示
void ConfirmConnection::printPressResetButton() {
  lcd_->setCursor(0, 0);
  // リセットボタンデ
  lcd_->print("\xD8\xBE\xAF\xC4\xCE\xDE\xC0\xDD\xC3\xDE     ");

  lcd_->setCursor(0, 1);
  // サイセツゾクシマス
  lcd_->print("\xBB\xB2\xBE\xC2\xBF\xDE\xB8\xBC\xCF\xBD     ");
}
