#pragma once

#include <stmlib/stmlib.h>
#include <U8x8lib.h>

extern uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t* u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void* arg_ptr);

extern uint8_t u8x8_byte_4wire_stm32_spi(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int,
    void* arg_ptr);

class BaseDisplay {
  public:
  void Init();

  protected:
  virtual void InitGLib() = 0;
};
