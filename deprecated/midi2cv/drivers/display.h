#ifndef MIDI2CV_DRIVERS_DISPLAY_H
#define MIDI2CV_DRIVERS_DISPLAY_H

#include "stmlib/stmlib.h"
#include "base_display.h"
#include <U8g2lib.h>
#include <stm32f3xx_hal_conf.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

extern uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t* u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void* arg_ptr);

extern uint8_t u8x8_byte_4wire_stm32_spi(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int,
    void* arg_ptr);

class Display : public BaseDisplay {
  public:
  Display() {}
  ~Display() {}

  U8G2* u8g2();
  void Flush();
  void Swap();

  private:
  DISALLOW_COPY_AND_ASSIGN(Display);
  void InitGLib();
};

#endif
