
#define ENABLE_DEBUG_PIN
#include "drivers/debug_pin.h"

#include "drivers/adc.h"
#include "drivers/dacs.h"
#include "drivers/leds.h"
#include "drivers/peripherals.h"
#include "drivers/switches.h"
#include "processor.h"
#include "resources.h"
#include "stmlib/ui/event_queue.h"
#include "ui.h"
#include <stm32f0xx_hal.h>

using namespace stereo_mix;
using namespace stmlib;

Dacs dacs;

Adc adc;
Leds leds;
Switches switches;
Processor processors[kNumChannels];
UI ui(&adc, &switches, &leds, processors);

bool mute[4];

void WriteOutputs(void);

// Default interrupt handlers.
extern "C" {
void NMI_Handler() { }
void Error_Handler()
{
  while (1)
    ;
}
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
void SVC_Handler() { }
void DebugMon_Handler() { }
void PendSV_Handler() { }

// called every 1ms
void SysTick_Handler()
{
  HAL_IncTick();

  system_clock.Tick();

  switches.Debounce();
  ui.Poll();
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
      | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    Error_Handler();
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  adc.OnDMATransferComplete();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
  if (htim == &htim3) {
    leds.Write(); // 53571 Hz
    return;
  }
  if (htim == &htim6) {
    WriteOutputs(); // 4076 Hz
  }
}
}

void Init(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_TIM1_CLK_ENABLE();
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_TIM6_CLK_ENABLE();
  __HAL_RCC_SPI1_CLK_ENABLE();

  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  htim3.Init.Prescaler = 27;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535 >> 2;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&htim3);
  HAL_TIM_Base_Start_IT(&htim3);

  HAL_NVIC_SetPriority(TIM6_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(TIM6_IRQn);
  htim6.Init.Prescaler = 47;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 256; // 96 without optimize
  htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim6.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&htim6);
  HAL_TIM_Base_Start_IT(&htim6);

  system_clock.Init();
}

uint16_t out[kNumChannels][2];

void WriteOutputs(void)
{
  for (int i = 0; i < kNumChannels; i++) {
    dacs.Write16(i, 0, out[i][0]);
    dacs.Write16(i, 1, out[i][1]);
  }
  for (int i = 0; i < kNumChannels; i++) {
    int16_t cvs[2];
    cvs[0] = 65535 - adc.cv_value(AdcChannel(ADC_CHANNEL_PAN_1 + i));
    cvs[1] = adc.cv_value(AdcChannel(ADC_CHANNEL_VOL_1 + i));
    processors[i].Process(cvs, out[i]);
  }
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  Init();
  ui.Init();
  while (true) {
    ui.DoEvents();
  }
}
