#include <Arduino.h>

#include "InputAppConfig.h"
#include "InputApp.h"
#include "XBeeSleepController.h"
#include "TactSwitch.h"
#include "SendData.h"

// コンストラクタ
SendData::SendData(InputApp* app, I2CLiquidCrystal* lcd) :
  app_(app),
  lcd_(lcd),
  xbee_(InputAppConfig::PIN_XBEE_SLEEP),
  sw_reset_(InputAppConfig::PIN_SW_RESET, InputAppConfig::SW_SHORT_PUSH_COUNT)
{
}

// データ送信を実行する
void SendData::execute(String leader_id, int num_of_members) {
  sw_reset_.reset();

  printPreparing();
  prepareForCommunication();

  printSending();
  send(leader_id, num_of_members);

  while (1) {
    if (sw_reset_.readState() == TactSwitch::SW_PUSHED) {
      // リセットボタンが押されたら何もしない
      return;
    }

    if (Serial.available() > 0) {
      char result_ch = Serial.read();

      xbee_.sleep();

      switch (result_ch) {
      case 'R':
        printRegistered();
        blinkLed(InputAppConfig::PIN_LED_SUCCESS);

        break;
      case 'U':
        printUpdated();
        blinkLed(InputAppConfig::PIN_LED_SUCCESS);

        break;
      default:
        printError();
        blinkLed(InputAppConfig::PIN_LED_ERROR);

        break;
      }

      delay(InputAppConfig::WAIT_TIME_AFTER_SEND);
      return;
    }

    delay(10);
  }
}

// 通信の準備を行う
void SendData::prepareForCommunication() {
  xbee_.wakeUp();
  delay(InputAppConfig::WAIT_TIME_FOR_XBEE_WAKE_UP);

  // シリアル通信の読み残しがあれば、すべて読んで残りデータを空にする
  while (Serial.available() > 0) {
    Serial.read();
  }
}

// データを送信する
void SendData::send(String leader_id, int num_of_members) {
  String data = leader_id + ',' + num_of_members;
  Serial.println(data);
}

// 通信準備中表示
void SendData::printPreparing() {
  lcd_->setCursor(0, 1);
  // "ツウシンジュンビチュウ"
  lcd_->print("\xC2\xB3\xBC\xDD\xBC\xDE\xAD\xDD\xCB\xDE\xC1\xAD\xB3  ");
}

// 送信中表示
void SendData::printSending() {
  lcd_->setCursor(0, 1);
  // "ソウシンチュウ"
  lcd_->print("\xBF\xB3\xBC\xDD\xC1\xAD\xB3        ");
}

// 登録完了表示
void SendData::printRegistered() {
  lcd_->setCursor(0, 1);
  // "トウロクシマシタ"
  lcd_->print("\xC4\xB3\xDB\xB8\xBC\xCF\xBC\xC0       ");
}

// 更新完了表示
void SendData::printUpdated() {
  lcd_->setCursor(0, 1);
  // "コウシンシマシタ"
  lcd_->print("\xBA\xB3\xBC\xDD\xBC\xCF\xBC\xC0       ");
}

// 登録失敗表示
void SendData::printError() {
  lcd_->setCursor(0, 1);
  // "トウロクデキマセンデシタ"
  lcd_->print("\xC4\xB3\xDB\xB8\xC3\xDE\xB7\xCF\xBE\xDD\xC3\xDE\xBC\xC0 ");
}

// LED を点滅させる
void SendData::blinkLed(int pin) {
  for (int i = 0; i < 2; ++i) {
    digitalWrite(pin, LOW);
    delay(150);
    digitalWrite(pin, HIGH);
    delay(150);
  }

  digitalWrite(pin, LOW);
}
