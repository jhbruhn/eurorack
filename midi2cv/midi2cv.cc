#include <stm32f10x_conf.h>

#include "stmlib/system/system_clock.h"

using namespace stmlib;

void Init(void) {
  system_clock.Init();
}

int main(void) {
  Init();
	// hi
}
