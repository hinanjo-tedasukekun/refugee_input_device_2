#ifndef APP_MODE_H
#define APP_MODE_H

// モードの抽象クラス
class AppMode {
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
