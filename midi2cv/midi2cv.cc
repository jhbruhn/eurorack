#include <stm32f10x_conf.h>

#include "drivers/gpio.h"

using namespace stmlib;



GPIO gpio;


// Default interrupt handlers.
extern "C" {
  void NMI_Handler() { }
  void HardFault_Handler() {
    while (1);
  }
  void MemManage_Handler() { while (1); }
  void BusFault_Handler() { while (1); }
  void UsageFault_Handler() { while (1); }
  void SVC_Handler() { }
  void DebugMon_Handler() { }
  void PendSV_Handler() { }

  // called every 1ms
  void SysTick_Handler() {
  }
}



void Init(void) {
  SystemInit();
 NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x1000);

  RCC_APB2PeriphClockCmd(
      RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
      RCC_APB2Periph_TIM1 | RCC_APB2Periph_USART1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  gpio.Init();
}

int main(void) {
  Init();
while (1) {
  // hi
  gpio.Write(GPIO_PIN(GATE_OUT_1), 1);
  gpio.Write(GPIO_PIN(GATE_OUT_2), 0);
  gpio.Write(GPIO_PIN(GATE_OUT_3), 1);
  gpio.Write(GPIO_PIN(GATE_OUT_4), 0);
}
}

