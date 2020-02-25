#include <stm32f37x_conf.h>

#include "stmlib/system/bootloader_utils.h"
#include "stmlib/system/system_clock.h"
#include "midi2cv/drivers/eco_display.h"
#include <U8x8lib.h>

using namespace stmlib;

extern "C" {
  void SysTick_Handler() {
    system_clock.Tick();
  }
}

const uint32_t kStartAddress = 0x08008000;

EcoDisplay display;

int main(void)
{
  SystemInit();

  SysTick_Config(F_CPU / 1000);

  system_clock.Init();

  display.Init();

  display.u8x8()->setFont(u8x8_font_amstrad_cpc_extended_r);
  display.u8x8()->drawString(0, 0, "Moin");
  system_clock.Delay(500);
  display.u8x8()->drawString(0, 10, "i bims");
  system_clock.Delay(1000);

  Uninitialize();
  JumpTo(kStartAddress);
}
