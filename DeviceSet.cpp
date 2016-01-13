//#include <Arduino.h>
#include "TactSwitch.h"
#include "DeviceSet.h"

// すべてのスイッチの状態をリセットする
void DeviceSet::resetAllSwitches() {
  TactSwitch* switches[] = {
    &sw_1,
    &sw_2,
    &sw_3,
    &sw_4,
    &sw_plus,
    &sw_minus,
    &sw_enter,
    &sw_leave,
    &sw_send,
    &sw_reset
  };

  for (auto sw : switches) {
    sw->reset();
  }
}
