#ifndef BARCODE_READER_POWER_CONTROLLER_H
#define BARCODE_READER_POWER_CONTROLLER_H

// バーコードリーダー電源制御クラス
class BarcodeReaderPowerController {
public:
  // コンストラクタ
  BarcodeReaderPowerController(int power_pin, int receiver_en_pin);
  // 電源を入れる
  void turnOn();
  // 電源を切る
  void turnOff();
private:
  // フォトカプラに出力する電源のピン
  int power_pin_;
  // ADM3222 のレシーバイネーブルピン
  int receiver_en_pin_;
};

#endif
