#include <Arduino.h>
#include "I2CLiquidCrystal.h"

#include "InputAppConfig.h"
#include "InputApp.h"
#include "TactSwitch.h"
#include "Waiting.h"

// コンストラクタ
Waiting::Waiting(InputApp* app, I2CLiquidCrystal* lcd) :
  app_(app),
  lcd_(lcd),
  sw_send_(InputAppConfig::PIN_SW_SEND, InputAppConfig::SW_SHORT_PUSH_COUNT)
{
}

// 状態をリセットする
void Waiting::reset() {
  sw_send_.reset();
}

// IO ポートを初期状態にする
void Waiting::setupPorts() {
  // バーコードリーダーの電源を切る
  digitalWrite(InputAppConfig::PIN_READER_VCC, LOW);

  // LED を消灯する
  digitalWrite(InputAppConfig::PIN_LED_SUCCESS, HIGH);
  digitalWrite(InputAppConfig::PIN_LED_ERROR, HIGH);
}

// LCD を初期状態にする
void Waiting::setupLcd() {
  lcd_->setCursor(0, 0);
  // "ヨミトリボタンヲ"
  lcd_->print("\xD6\xD0\xC4\xD8\xCE\xDE\xC0\xDD\xA6      ");

  lcd_->setCursor(0, 1);
  // "オシテクダサイ"
  lcd_->print("\xB5\xBC\xC3\xB8\xC0\xDE\xBB\xB2       ");
}

// メインループ
void Waiting::loop() {
  if (sw_send_.readState() == TactSwitch::SW_PUSHED) {
    app_->startInputLeaderId();
  }
}
