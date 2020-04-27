#pragma once

#include "peripherals.h"
#include "stmlib/stmlib.h"
#include <stm32f0xx_hal.h>
#include <stm32f0xx_ll_spi.h>

namespace stereo_mix {

GPIO_TypeDef* kMDacPorts[] = { GPIOB, GPIOB, GPIOB, GPIOB };
const uint16_t kMDacPins[] = { GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11 };

GPIO_TypeDef* kOffsetDacPorts[] = { GPIOA, GPIOA, GPIOA, GPIOA };
const uint16_t kOffsetDacPins[] = { GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11 };

class Dacs { // MCP4xx2 dac implementation
  public:
  Dacs()
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();

    HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);

    GPIO_InitTypeDef gpio_init;

    for (size_t i = 0; i < 8; i++) {
      // init SS/CS/RST GPIO
      uint16_t ssGpioPin;
      GPIO_TypeDef* ssGpioPort;
      if (i < 4) {
        ssGpioPin = kMDacPins[i];
        ssGpioPort = kMDacPorts[i];
      } else {
        ssGpioPin = kOffsetDacPins[i - 4];
        ssGpioPort = kOffsetDacPorts[i - 4];
      }
      gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
      gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
      gpio_init.Pull = GPIO_NOPULL;
      gpio_init.Pin = ssGpioPin;
      HAL_GPIO_Init(ssGpioPort, &gpio_init);

      HAL_GPIO_WritePin(ssGpioPort, ssGpioPin, GPIO_PIN_SET);
    }

    // init AF GPIO

    gpio_init.Mode = GPIO_MODE_AF_PP;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    gpio_init.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOB, &gpio_init);

    // init SPI
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.CRCPolynomial = 7;
    HAL_SPI_Init(&hspi1);
    SPI1->CR1 |= SPI_CR1_SPE; // this is required only once
  };

  void Write16(uint8_t device, uint8_t channel, uint16_t value, uint8_t gain, uint8_t buffered)
  {
    if (channel > 1)
      return; // only 2 channels available
    if (buffered > 1)
      return; // buffered can only be 0 or 1
    if (gain > 2 || gain < 1)
      return; // gain has to be 1 or 2

    gain = !(gain - 1);

    value >>= 4; // the dac supports a maximum of 12 bits precision

    value |= channel << 15;  // select channel
    value |= buffered << 14; // set buffered
    value |= gain << 13;     // set gain
    value |= 1 << 12;        // shutdown always set to 1

    kMDacPorts[device]->BRR |= kMDacPins[device];
    kOffsetDacPorts[device]->BRR |= kOffsetDacPins[device];
    SPI1->DR = value;
    while ((SPI1->SR & (SPI_SR_TXE | SPI_SR_BSY)) != SPI_SR_TXE)
      ;
    kMDacPorts[device]->BSRR |= kMDacPins[device];
    kOffsetDacPorts[device]->BSRR |= kOffsetDacPins[device];
  };

  void Write16(uint8_t device, uint8_t channel, uint16_t value)
  {
    Write16(device, channel, value, 1, 0);
  };
};

}
