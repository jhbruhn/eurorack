#ifndef MIDI2CV_DRIVERS_GPIO_H
#define MIDI2CV_DRIVERS_GPIO_H


#include "stmlib/stmlib.h"

class GPIO {
  public:
    GPIO() { }
    ~GPIO() {}

    void Init();
    void Write();
  private:
    DISALLOW_COPY_AND_ASSIGN(GPIO);
};

extern GPIO gpio;

#endif

