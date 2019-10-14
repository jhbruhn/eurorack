#ifndef MIDI2CV_DRIVERS_DISPLAY_H
#define MIDI2CV_DRIVERS_DISPLAY_H

#include "stmlib/stmlib.h"
#include <stm32f37x_conf.h>
#include <u8g2.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

class Display {
public:
    Display() {}
    ~Display() {}

    void Init();
    u8g2_t* u8g2();
    void Flush();
    void Swap();

private:
    DISALLOW_COPY_AND_ASSIGN(Display);
    void InitGLib();
};
extern Display display;
#endif
