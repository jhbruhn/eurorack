#ifndef MIDI2CV_DRIVERS_DISPLAY_H
#define MIDI2CV_DRIVERS_DISPLAY_H

#include <stm32f37x_conf.h>
#include "stmlib/stmlib.h"
#include <u8g2.h>


class Display {
  public:
    Display() { }
    ~Display() {}

    void Init();
    u8g2_t* u8g2();    
  private:
    DISALLOW_COPY_AND_ASSIGN(Display);
    void InitGLib();    
};
extern Display display;
#endif
