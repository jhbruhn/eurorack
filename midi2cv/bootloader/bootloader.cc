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

  display.u8x8()->setFont(u8x8_font_5x7_f);
  display.u8x8()->drawString(0, 0, "RolfOS 1.0");
  system_clock.Delay(200);
  display.u8x8()->drawString(0, 2, "Display ready");
  system_clock.Delay(500);
  display.u8x8()->drawString(0, 3, "Ehre ready");
  system_clock.Delay(500);
  display.u8x8()->drawString(0, 5, "let's fetz");
  system_clock.Delay(1000);

  Uninitialize();
  JumpTo(kStartAddress);
}
