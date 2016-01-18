#ifndef POWER_CONTROLLER_H
#define POWER_CONTROLLER_H

// 電源制御クラス
class PowerController {
public:
  // コンストラクタ
  PowerController(int pin);
  // 電源を入れる
  void turnOn();
  // 電源を切る
  void turnOff();
private:
  // ピン
  int pin_;
};

#endif
