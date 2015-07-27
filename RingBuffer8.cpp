#include <Arduino.h>
#include <string.h>

#include "RingBuffer8.h"

RingBuffer8::RingBuffer8() :
  length_(0),
  index_(0),
  data_ {},
  pushed_after_to_string_(false),
  converted_str_()
{
}

void RingBuffer8::clear() {
  length_ = 0;
  index_ = 0;
  pushed_after_to_string_ = false;
  converted_str_ = "";

  for (char& c : data_) {
    c = '\0';
  }
}

int RingBuffer8::getLength() {
  return length_;
}

void RingBuffer8::pushBack(char c) {
  data_[index_] = c;

  if (length_ < BUFFER_SIZE) {
    ++length_;
  }

  // バッファ長が 2^n だから AND で余りをとれる
  index_ = (index_ + 1) & (BUFFER_SIZE - 1);

  pushed_after_to_string_ = true;
}

String RingBuffer8::toString() {
  if (!pushed_after_to_string_) {
    return converted_str_;
  }

  if (length_ < BUFFER_SIZE) {
    converted_str_ = String(data_);
    pushed_after_to_string_ = false;

    return converted_str_;
  }

  converted_str_ = convertLongCharsToString(data_);
  pushed_after_to_string_ = false;

  return converted_str_;
}

String RingBuffer8::convertLongCharsToString(const char* data) {
  char concatenated[BUFFER_SIZE + 1] = {};
  int i, j;

  for (i = 0, j = index_; j < BUFFER_SIZE; ++i, ++j) {
    concatenated[i] = data[j];
  }

  for (j = 0; j < index_; ++i, ++j) {
    concatenated[i] = data[j];
  }

  return String(concatenated);
}
