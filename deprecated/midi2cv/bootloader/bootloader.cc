#include <stm32f3xx_hal.h>

#include "midi2cv/drivers/eco_display.h"
#include "stmlib/system/bootloader_utils.h"
#include "stmlib/system/system_clock.h"
#include <U8x8lib.h>

using namespace stmlib;

extern "C" void __cxa_pure_virtual()
{
  while (1)
    ;
}

extern "C" {
void Error_Handler(void)
{
  while (1)
    ;
}
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
void SysTick_Handler()
{
  system_clock.Tick();
}
}

const uint32_t kStartAddress = 0x08008000;

EcoDisplay display;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  SystemInit();

  SysTick_Config(F_CPU / 1000);

  system_clock.Init();

  display.Init();

  display.u8x8()->setFont(u8x8_font_5x7_f);
  display.u8x8()->drawString(0, 0, "RolfOS 1.0");
  system_clock.Delay(20);
  display.u8x8()->drawString(0, 2, "Display ready");
  system_clock.Delay(50);
  display.u8x8()->drawString(0, 3, "Ehre ready");
  system_clock.Delay(50);
  display.u8x8()->drawString(0, 5, "let's fetz");
  system_clock.Delay(100);

  Uninitialize();
  JumpTo(kStartAddress);
}
