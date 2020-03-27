#include "drivers/dac.h"

// Default interrupt handlers.
extern "C" {
void NMI_Handler() {}
void HardFault_Handler()
{
  while (1)
    ;
}
void MemManage_Handler()
{
  while (1)
    ;
}
void BusFault_Handler()
{
  while (1)
    ;
}
void UsageFault_Handler()
{
  while (1)
    ;
}
void SVC_Handler() {}
void DebugMon_Handler() {}
void PendSV_Handler() {}

// called every 1ms
void SysTick_Handler()
{
}
}

Dac dacs[8];

int main(void)
{
  SystemInit();
  dacs[0].Init(GPIOB, GPIO_Pin_8);
  dacs[1].Init(GPIOB, GPIO_Pin_9);
  dacs[2].Init(GPIOB, GPIO_Pin_10);
  dacs[3].Init(GPIOB, GPIO_Pin_11);
  dacs[4].Init(GPIOA, GPIO_Pin_8);
  dacs[5].Init(GPIOA, GPIO_Pin_9);
  dacs[6].Init(GPIOA, GPIO_Pin_10);
  dacs[7].Init(GPIOA, GPIO_Pin_11);

  while (true) {
    for (uint16_t i = 0; i < 65535; i++) {
      dacs[0].Write16(0, i);
      dacs[0].Write16(1, 65535 - i);
    }
  }
}
