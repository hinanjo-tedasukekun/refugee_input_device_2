#ifndef TACT_SWITCH_WITH_LONG_PUSH_H
#define TACT_SWITCH_WITH_LONG_PUSH_H

class TactSwitchWithLongPush {
public:
  // スイッチの状態を表す型
  enum SwitchState {
    SW_UP,           // 上がっている
    SW_DOWN,         // 下がっている
    SW_PUSHED_SHORT, // 短く押された
    SW_PUSHED_LONG   // 長く押された
  };
private:
  const int pin_; // ピン番号

  // 短く押されたと認識されるのに必要なカウント数
  const int short_push_count_; 
  // 長く押されたと認識されるのに必要なカウント数
  const int long_push_count_;

  int down_count_; // 下がっている状態のカウント数
public:
  TactSwitchWithLongPush(
    const int pin,
    const int short_push_count,
    const int long_push_count
  );
  // 状態をリセットする
  void reset();
  // 押下状態を読み込む
  SwitchState readState();
};

#endif
