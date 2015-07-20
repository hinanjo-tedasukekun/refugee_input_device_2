#ifndef _TACT_SWITCH_H
#define _TACT_SWITCH_H

class TactSwitch {
public:
  // スイッチの状態を表す型
  enum SwitchState {
    SW_UP,    // 上がっている
    SW_DOWN,  // 下がっている
    SW_PUSHED // 押された
  };

private:
  const int pin_; // ピン番号
  // 押されたと認識されるのに必要なカウント数
  const unsigned int push_count_;
  unsigned int down_count_; // 下がっている状態のカウント数

public:
  TactSwitch(const int pin, const unsigned int push_count);
  // 状態をリセットする
  void reset();
  // 押下状態を読み込む
  SwitchState readState();
};

#endif
