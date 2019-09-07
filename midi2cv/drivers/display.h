#ifndef MIDI2CV_DRIVERS_DISPLAY_H
#define MIDI2CV_DRIVERS_DISPLAY_H

#include <stm32f37x_conf.h>
#include "stmlib/stmlib.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64



class Display {
  public:
    Display() { }
    ~Display() {}

    void Init();
    void WritePixel(uint8_t x, uint8_t  y, bool color);
    void Clear();
    void Update();
  private:
    DISALLOW_COPY_AND_ASSIGN(Display);
    void WriteCommand(uint8_t byte);
    void WriteData(uint8_t* data, uint8_t length);
    
    uint8_t buffer[DISPLAY_WIDTH*DISPLAY_HEIGHT / 8];
};

#endif
