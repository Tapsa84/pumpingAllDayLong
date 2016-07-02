
#include "TriggerTimer.h"

TriggerTimer::TriggerTimer() {
  this->triggerTime = 1000;
}

void TriggerTimer::setTriggerTime(int triggerTime) {
  this->triggerTime = triggerTime;
}

void TriggerTimer::reset() {
  this->lastPass = millis();
}

boolean TriggerTimer::isTriggered() {
  return millis() > (this->lastPass + this->triggerTime);
}
