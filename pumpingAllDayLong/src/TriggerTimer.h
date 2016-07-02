#ifndef TriggerTimer_h
#define TriggerTimer_h
#include <Arduino.h>

class TriggerTimer {
  private:
    int triggerTime;
    int lastPass;
  public:
    TriggerTimer();
    void reset();
    void setTriggerTime(int triggerTime);
    boolean isTriggered();
};;

#endif
