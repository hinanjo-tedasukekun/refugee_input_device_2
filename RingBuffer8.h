#ifndef RING_BUFFER_8_H
#define RING_BUFFER_8_H

// 8 文字分のリングバッファのクラス
class RingBuffer8 {
public:
  // バッファの大きさ
  static const int BUFFER_SIZE = 8;

private:
  // 現在のデータの長さ
  int length_;
  // 現在の挿入位置
  int index_;
  // バッファ内データ
  char data_[BUFFER_SIZE + 1];
  // 文字列への変換後文字が追加されたかどうか
  bool pushed_after_to_string_;
  // 文字列への変換結果
  String converted_str_;

public:
  RingBuffer8();
  // バッファをクリアする
  void clear();
  // 現在のデータの長さを返す
  int getLength();
  // 末尾に文字を追加する
  void pushBack(char c);
  // 文字列に変換する
  String toString();

private:
  String convertLongCharsToString(const char* data);
};

#endif
