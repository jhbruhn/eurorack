#include "spi_mode.h"
#include "peripherals.h"
#include "stm32f3xx_hal_spi.h"
#include <stm32f3xx_hal.h>

SPIMode currentMode = SPI_MODE_UNINITIALIZED;

void InitSPIDisplay(void);

void InitSPI(SPIMode mode)
{
  if (currentMode == SPI_MODE_UNINITIALIZED) {
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    // init AF GPIO
    GPIO_InitTypeDef gpio_init;
    gpio_init.Mode = GPIO_MODE_AF_PP;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Pin = GPIO_PIN_8 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio_init.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &gpio_init);
  }
  if (currentMode != mode) {
    switch (mode) {
    case SPI_MODE_DISPLAY:
      InitSPIDisplay();
      break;
    case SPI_MODE_DAC0:
    case SPI_MODE_DAC1:
    case SPI_MODE_USB:
    case SPI_MODE_UNINITIALIZED:

      break;
    }
    currentMode = mode;
  }
}

void InitSPIDisplay(void)
{
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  HAL_SPI_Init(&hspi2);
}
