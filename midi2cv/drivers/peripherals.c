#include "peripherals.h"

IWDG_HandleTypeDef hiwdg = { .Instance = IWDG };
TIM_HandleTypeDef htim2 = { .Instance = TIM2 };
SPI_HandleTypeDef hspi2 = { .Instance = SPI2 };

void TIM2_IRQHandler()
{
  HAL_TIM_IRQHandler(&htim2);
}
