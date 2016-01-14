#ifndef APP_MODE_H
#define APP_MODE_H

// 状態の抽象クラス
// Non-virtual interface イディオムで書く
class AppState {
public:
  // モードの設定を行う
  void setup() {
    doSetup();
  }

  // モードのメインループ
  void loop() {
    doLoop();
  }
protected:
  virtual void doSetup() = 0;
  virtual void doLoop() = 0;
};

#endif
