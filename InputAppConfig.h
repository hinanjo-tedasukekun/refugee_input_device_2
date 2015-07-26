#ifndef INPUT_APP_CONFIG_H
#define INPUT_APP_CONFIG_H

struct InputAppConfig {
  static const int LEADER_ID_LENGTH = 8;

  static const int PIN_LED_SUCCESS;
  static const int PIN_LED_ERROR;

  static const int PIN_SW_1;
  static const int PIN_SW_2;
  static const int PIN_SW_PLUS;
  static const int PIN_SW_MINUS;
  static const int PIN_SW_SEND;

  static const int PIN_SW_RESET;

  static const int SW_SHORT_PUSH_COUNT;
  static const int SW_LONG_PUSH_COUNT;
};

#endif
