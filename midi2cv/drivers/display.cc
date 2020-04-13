#include "display.h"
#include "gpio.h"
#include "spi_mode.h"
#include "stmlib/system/system_clock.h"
#include <U8g2lib.h>
#include <u8g2.h>

using namespace stmlib;

static uint8_t* default_buf;
static uint8_t second_buf[1024];
static uint8_t* output_buf;

class U8G2_SH1106_128x64_NONAME_F_SPI : public U8G2 {
  public:
  U8G2_SH1106_128x64_NONAME_F_SPI()
      : U8G2()
  {
    u8g2_Setup_sh1106_128x64_noname_f(&this->u8g2, U8G2_R0, u8x8_byte_4wire_stm32_spi, u8x8_stm32_gpio_and_delay);
    output_buf = default_buf = this->u8g2.tile_buf_ptr;
    /*u8g2_InitDisplay(&u8g2_);
  u8g2_SetContrast(&u8g2_, 255);
  u8g2_SetPowerSave(&u8g2_, 0);*/
  }
};

U8G2_SH1106_128x64_NONAME_F_SPI u8g2_;

U8G2* Display::u8g2()
{
  return &u8g2_;
}

void Display::InitGLib()
{
  u8g2_.begin();
}

void Display::Flush()
{
  uint8_t* cache = u8g2_.getU8g2()->tile_buf_ptr;
  u8g2_.getU8g2()->tile_buf_ptr = output_buf;
  u8g2_.sendBuffer();
  u8g2_.getU8g2()->tile_buf_ptr = cache;
}

void Display::Swap()
{
  output_buf = u8g2_.getU8g2()->tile_buf_ptr;
  if (output_buf == default_buf)
    u8g2_.getU8g2()->tile_buf_ptr = second_buf;
  else
    u8g2_.getU8g2()->tile_buf_ptr = default_buf;
}
