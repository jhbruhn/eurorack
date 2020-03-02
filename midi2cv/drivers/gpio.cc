#include "gpio.h"

#include <gpio.h>

void GPIO::Init() {
  gpio_mode_setup(0, 0, 0, 0);
}


void GPIO::Write() {
}
