/*
 * XBee スリープ制御クラス
 */

#ifndef X_BEE_SLEEP_CONTROLLER_H
#define X_BEE_SLEEP_CONTROLLER_H

class XBeeSleepController {
public:
  // XBee のスリープ解除待ち時間 [ms]
  static constexpr int WAIT_TIME_FOR_WAKE_UP = 100;

  // コンストラクタ
  XBeeSleepController(int pin);
  // スリープモードにする
  void sleep();
  // スリープモードを解除する
  void wakeUp();
private:
  int pin_;
};

#endif
