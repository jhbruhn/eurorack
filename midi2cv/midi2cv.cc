#include <stm32f10x_conf.h>

#include "stmlib/system/system_clock.h"
#include "drivers/gpio.h"

using namespace stmlib;

GPIO gpio;

void Init(void) {
  //system_clock.Init();
  gpio.Init();
}

int main(void) {
  Init();
  // hi
  gpio.Write(GPIO_PIN(GATE_OUT_1), 1);
  gpio.Write(GPIO_PIN(GATE_OUT_2), 0);
  gpio.Write(GPIO_PIN(GATE_OUT_3), 1);
  gpio.Write(GPIO_PIN(GATE_OUT_4), 0);
}
