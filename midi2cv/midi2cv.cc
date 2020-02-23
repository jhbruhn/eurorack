#include <stm32f37x_conf.h>

#include "drivers/display.h"
#include "drivers/encoder.h"
#include "drivers/gpio.h"
#include "menu/menu.h"
#include "menu/menu_items.h"
#include "part.h"
#include "stmlib/system/system_clock.h"
#include "ui.h"
#include "config.h"

using namespace stmlib;

GPIO gpio;
Display display;
Encoder encoder;

UI ui;
Part part[PART_COUNT];

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
  ui.Poll();
  system_clock.Tick();
}

void TIM2_IRQHandler(void)
{
  // this will get called with 8kHz (foof)
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == RESET) {
    return;
  }
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

  static uint8_t count = 0;
  count++;
  if (count % (8000L / 60) == 0) {
    // refresh display with 60fps
    ui.Flush();
    count = 0;
  }

  // write audiodac1
  // write audiodac2
  // write audiodac3
  // write audiodac4
}
}

void InitTimers(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_TimeBaseInitTypeDef timer_init;
  timer_init.TIM_Period = F_CPU / (8000 * 1) - 1;
  timer_init.TIM_Prescaler = 0;
  timer_init.TIM_ClockDivision = TIM_CKD_DIV1;
  timer_init.TIM_CounterMode = TIM_CounterMode_Up;
  timer_init.TIM_RepetitionCounter = 0;
  //TIM_InternalClockConfig(TIM2);
  TIM_TimeBaseInit(TIM2, &timer_init);
  TIM_Cmd(TIM2, ENABLE);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 2.2 priority split.

  // DAC interrupt is given highest priority
  NVIC_InitTypeDef timer_interrupt;
  timer_interrupt.NVIC_IRQChannel = TIM2_IRQn;
  timer_interrupt.NVIC_IRQChannelPreemptionPriority = 0;
  timer_interrupt.NVIC_IRQChannelSubPriority = 1;
  timer_interrupt.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&timer_interrupt);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void Init(void)
{
  SystemInit();
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x8000);
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_16);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  system_clock.Init();
  SysTick_Config(F_CPU / 1000);

  //IWDG_Enable();
  gpio.Init();
  display.Init();
  encoder.Init();
  ui.Init();
  InitTimers();
}

int main(void)
{
  Init();

  while (1) {
    // In this loop we do things that dont depend on any timing, but that have to be done.
    // you should not write on spi here because that should happen in the TIM2 interrupt
    // do we want to call the watchdog here? it's the only part thats getting interrupted after all
    // (next to the interrupts themselves potentially interrupting each other)
    ui.DoEvents();
    IWDG_ReloadCounter();
  }
}
