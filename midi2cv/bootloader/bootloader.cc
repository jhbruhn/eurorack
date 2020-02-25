#include <stm32f37x_conf.h>

#include "stmlib/system/bootloader_utils.h"
#include "midi2cv/drivers/eco_display.h"
#include <U8x8lib.h>

using namespace stmlib;

const uint32_t kStartAddress = 0x08008000;

EcoDisplay display;

int main(void)
{
  SystemInit();

  display.Init();

  display.u8x8()->setFont(u8x8_font_amstrad_cpc_extended_r);
  display.u8x8()->drawString(0, 0, "Moin");
  for (int i = 0; i < 100000000; i++)
    ;
  Uninitialize();
  JumpTo(kStartAddress);
}
