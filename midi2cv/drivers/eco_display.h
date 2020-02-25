#pragma once

#include "base_display.h"
#include <U8x8lib.h>

class U8X8_SH1106_128X64_NONAME_4W_SW_SPI : public U8X8 {
  public:
  U8X8_SH1106_128X64_NONAME_4W_SW_SPI()
      : U8X8()
  {
    u8x8_Setup(getU8x8(), u8x8_d_sh1106_128x64_noname, u8x8_cad_001, u8x8_byte_4wire_stm32_spi, u8x8_stm32_gpio_and_delay);
  }
};

class EcoDisplay : public BaseDisplay {
  protected:
  void InitGLib() {
    this->u8x8()->begin();
  }

  public:
  U8X8* u8x8() {
    return &this->instance;
  }

  U8X8_SH1106_128X64_NONAME_4W_SW_SPI instance;

};
