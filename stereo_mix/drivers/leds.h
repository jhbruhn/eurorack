#pragma once

#include "stm32f0xx_hal_gpio.h"
#include <stm32f0xx_hal.h>

const uint8_t kNumChannels = 4;

static const uint16_t kGpioPins[] = { GPIO_PIN_7, GPIO_PIN_15, GPIO_PIN_13, GPIO_PIN_14 };
static GPIO_TypeDef* kGpioPorts[] = { GPIOB, GPIOB, GPIOF, GPIOF };

class Leds {
  public:
  Leds()
  {
    GPIO_InitTypeDef gpioInit;
    for (size_t i = 0; i < kNumChannels; i++) {
      gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
      gpioInit.Pin = kGpioPins[i];
      gpioInit.Pull = GPIO_NOPULL;
      gpioInit.Speed = GPIO_SPEED_FREQ_MEDIUM;
      HAL_GPIO_Init(kGpioPorts[i], &gpioInit);
    }
  }
  void Write()
  {
    pwm_counter += 2;

    for (size_t i = 0; i < kNumChannels; i++) {
      if (intensities[0] && intensities[i] >= pwm_counter) {
        HAL_GPIO_WritePin(kGpioPorts[i], kGpioPins[i], GPIO_PIN_SET);
      } else {
        HAL_GPIO_WritePin(kGpioPorts[i], kGpioPins[i], GPIO_PIN_RESET);
      }
    }
  }
  void set_intensity(uint8_t channel, uint8_t intensity)
  {
    if (channel >= kNumChannels)
      return;
    intensities[channel] = intensity;
  }

  private:
  uint8_t pwm_counter;
  uint8_t intensities[kNumChannels];
};
