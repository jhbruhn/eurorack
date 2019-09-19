#include <stm32f37x_conf.h>

#include "stmlib/system/bootloader_utils.h"

using namespace stmlib;

const uint32_t kStartAddress = 0x08008000;

int main(void) {
  SystemInit();
  Uninitialize();
  JumpTo(kStartAddress);
}
