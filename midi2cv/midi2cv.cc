#include <stm32f3xx_hal.h>

#include "config.h"
#include "drivers/display.h"
#include "drivers/encoder.h"
#include "drivers/peripherals.h"
#include "menu/menu.h"
#include "menu/menu_items.h"
#include "part.h"
#include "settings.h"
#include "stm32f3xx_hal_cortex.h"
#include "stm32f3xx_hal_tim.h"
#include "stmlib/system/system_clock.h"
#include "ui.h"

namespace std {
void __throw_bad_function_call()
{
  while (1)
    ;
};
}

extern "C" void __cxa_pure_virtual()
{
  while (1)
    ;
}

using namespace stmlib;

Display display;
Encoder encoder;

Settings settings;

Part parts[PART_COUNT];
Part* part_pointers[PART_COUNT] = { &parts[0], &parts[1], &parts[2], &parts[3] };
UI ui(part_pointers, &display, &settings);

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
void Error_Handler()
{
  while (1)
    ;
}
void SVC_Handler() {}
void DebugMon_Handler() {}
void PendSV_Handler() {}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

// called every 1ms
void SysTick_Handler(void)
{
  HAL_IncTick();
  ui.Poll();
  system_clock.Tick();
}

void TIM2_IRQHandler()
{
  HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
  if (htim != &htim2) {
    return;
  }

  static uint16_t count = 0;
  count++;
  if (count % (8000L / 24) == 0) {
    // refresh display with 24fps
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
  __HAL_RCC_TIM2_CLK_ENABLE();
  htim2.Init.Period = F_CPU / (8000 * 1) - 1;
  htim2.Init.Prescaler = 0;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.RepetitionCounter = 0;
  //TIM_InternalClockConfig(TIM2);
  HAL_TIM_Base_Init(&htim2);
  HAL_TIM_Base_Start_IT(&htim2);

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2); // 2.2 priority split.
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void Init(void)
{
  //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x8000);
  hiwdg.Init.Prescaler = IWDG_PRESCALER_16;
  //HAL_IWDG_Init(&hiwdg);

  system_clock.Init();

  //IWDG_Enable();
  display.Init();
  encoder.Init();
  InitTimers();
}

int main(void)
{
  SystemInit();
  SCB->VTOR = 0x8000;
  HAL_DeInit();
  HAL_Init();
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  SystemClock_Config();
  Init();

  while (1) {
    // In this loop we do things that dont depend on any timing, but that have to be done.
    // you should not write on spi here because that should happen in the TIM2 interrupt
    // do we want to call the watchdog here? it's the only part thats getting interrupted after all
    // (next to the interrupts themselves potentially interrupting each other)
    ui.DoEvents();
    HAL_IWDG_Refresh(&hiwdg);
  }
}
