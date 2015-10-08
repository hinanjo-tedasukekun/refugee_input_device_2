/*
 * XBee スリープ制御クラス
 */

#ifndef X_BEE_SLEEP_CONTROLLER_H
#define X_BEE_SLEEP_CONTROLLER_H

class XBeeSleepController {
private:
  int pin_;

public:
  // コンストラクタ
  XBeeSleepController(int pin);
  // スリープモードにする
  void sleep();
  // スリープモードを解除する
  void wakeUp();
};

#endif
