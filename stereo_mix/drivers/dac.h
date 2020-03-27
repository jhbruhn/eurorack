#pragma once

#include <stm32f0xx.h>
#include "stm32f0xx_gpio.h"
#include "stmlib/stmlib.h"
#include <stm32f0xx_conf.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_spi.h>

class Dac { // MCP4xx2 dac implementation
  public:
  void Init(GPIO_TypeDef* ssGpioPort_, uint16_t ssGpioPin_)
  {
    ssGpioPort = ssGpioPort_;
    ssGpioPin = ssGpioPin_;
    // init SS/CS/RST GPIO
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio_init;
    GPIO_StructInit(&gpio_init);
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Pin = ssGpioPin;
    GPIO_Init(ssGpioPort, &gpio_init);

    GPIO_SetBits(ssGpioPort, ssGpioPin);

    // init AF GPIO
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_StructInit(&gpio_init);
    gpio_init.GPIO_Mode = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_0);

    // init SPI
    SPI_I2S_DeInit(SPI1);

    // Initialize SPI TODO: check which config we need
    SPI_InitTypeDef spi_init;
    SPI_StructInit(&spi_init);
    spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi_init.SPI_Mode = SPI_Mode_Master;
    spi_init.SPI_DataSize = SPI_DataSize_16b;
    spi_init.SPI_CPOL = SPI_CPOL_High;
    spi_init.SPI_CPHA = SPI_CPHA_1Edge;
    spi_init.SPI_NSS = SPI_NSS_Soft;
    spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
    spi_init.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &spi_init);
    SPI_Cmd(SPI1, ENABLE);
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

    GPIO_ResetBits(ssGpioPort, ssGpioPin);
    SPI_I2S_SendData16(SPI1, value);
    //SPI_I2S_SendData16(SPI1, value); // MSB first, specified in config
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
      asm("nop");
    }
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {
      asm("nop");
    }
    GPIO_SetBits(ssGpioPort, ssGpioPin);
  };

  void Write16(uint8_t channel, uint16_t value)
  {
    Write16(channel, value, 1, 0);
  };

  private:
  GPIO_TypeDef* ssGpioPort;
  uint16_t ssGpioPin;
};
