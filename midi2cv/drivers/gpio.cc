#include "gpio.h"

#include <stm32f10x_conf.h>

void GPIO::Init() {
  GPIO_InitTypeDef gpio_init;
  
  gpio_init.GPIO_Pin = PIN_SS_DAC0 | PIN_SS_DAC1 | PIN_RST_USB | PIN_SS_USB | PIN_SS_OLED | PIN_SDC_OLED;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &gpio_init);

  gpio_init.GPIO_Pin = PIN_GATE_OUT_1 | PIN_GATE_OUT_2 | PIN_GATE_OUT_3 | PIN_GATE_OUT_4 | PIN_GATE_OUT_5 | PIN_GATE_OUT_6;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &gpio_init);
}

void GPIO::Write(GPIO_TypeDef* port, uint16_t pin, bool state) {
  GPIO_WriteBit(port, pin, static_cast<BitAction>(state));
}
