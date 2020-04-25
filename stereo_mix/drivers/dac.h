#pragma once

#include "peripherals.h"
#include "stm32f030x8.h"
#include "stmlib/stmlib.h"
#include <stm32f0xx_hal.h>

namespace stereo_mix {

class Dac { // MCP4xx2 dac implementation
  public:
  Dac(GPIO_TypeDef* ssGpioPort_, uint16_t ssGpioPin_)
      : ssGpioPort(ssGpioPort_)
      , ssGpioPin(ssGpioPin_)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();

    ssGpioPort = ssGpioPort_;
    ssGpioPin = ssGpioPin_;
    // init SS/CS/RST GPIO

    GPIO_InitTypeDef gpio_init;
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Pin = ssGpioPin;
    HAL_GPIO_Init(ssGpioPort, &gpio_init);

    HAL_GPIO_WritePin(ssGpioPort, ssGpioPin, GPIO_PIN_SET);

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
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.CRCPolynomial = 7;
    HAL_SPI_Init(&hspi1);
  };

  void Write16(uint8_t channel, uint16_t value, uint8_t gain, uint8_t buffered)
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

    HAL_GPIO_WritePin(ssGpioPort, ssGpioPin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, (uint8_t*)&value, 1, HAL_MAX_DELAY);
    //SPI_I2S_SendData16(SPI1, value); // MSB first, specified in config
    /*while (HAL_SPI_GetState(&hspi1) & HAL_SPI_STATE_BUSY) {
      asm("nop");
    }*/
    HAL_GPIO_WritePin(ssGpioPort, ssGpioPin, GPIO_PIN_SET);
  };

  void Write16(uint8_t channel, uint16_t value)
  {
    Write16(channel, value, 1, 0);
  };

  private:
  GPIO_TypeDef* ssGpioPort;
  uint16_t ssGpioPin;
};

}
