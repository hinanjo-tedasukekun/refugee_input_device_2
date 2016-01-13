#ifndef LED_H
#define LED_H

// LED を表すクラス
class Led {
public:
  // コンストラクタ
  Led(int pin);
  // 点灯させる
  void turnOn();
  // 消灯させる
  void turnOff();
  // 点滅させる
  void blink(int interval);
private:
  // ピン
  int pin_;
};

#endif
