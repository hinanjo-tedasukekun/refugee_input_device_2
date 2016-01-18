#ifndef READ_REFUGEE_NUM_H
#define READ_REFUGEE_NUM_H

#include "AppState.h"
#include "RingBuffer8.h"
#include "DeviceSet.h"

class InputApp;

// 避難者番号読み取りクラス
class ReadRefugeeNum : public AppState {
public:
  // 読み取りの制限時間 [ms]
  static constexpr unsigned long TIME_LIMIT = 15 * 1000;

  // コンストラクタ
  ReadRefugeeNum(InputApp* app, DeviceSet* devices);
protected:
  // 設定を行う
  virtual void doSetup();
  // メインループ
  virtual void doLoop();
private:
  // 代表者番号の文字列を格納するリングバッファ
  RingBuffer8 ring_buffer_;
  // 読み取りを強制終了させる時刻 [ms]
  unsigned long ms_end_;

  // アプリケーション
  InputApp* app_;
  // デバイス集合
  DeviceSet* devices_;

  // スイッチのイベントを処理する
  void handleSwitchEvents();
};

#endif
