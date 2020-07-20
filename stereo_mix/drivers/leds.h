#pragma once

#include "../resources.h"
#include "peripherals.h"
#include "stm32f030x8.h"
#include "stm32f0xx_hal_gpio_ex.h"
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_tim.h"
#include "stm32f0xx_hal_tim_ex.h"
#include "stmlib/utils/dsp.h"
#include "stm32f0xx_hal_gpio.h"
#include <stm32f0xx_hal.h>
#include <math.h>
#include "../config.h"

using namespace stereo_mix;
using namespace stmlib;

enum LedColor {
  LED_COLOR_GREEN,
  LED_COLOR_RED,
  LED_COLOR_ORANGE
};

static GPIO_TypeDef* kGpioPorts[] = { GPIOA, GPIOA, GPIOA, GPIOA };
static const uint16_t kGpioPins[] = { GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11 };

static GPIO_TypeDef* kGpioColorPorts[] = {GPIOC, GPIOC, GPIOF, GPIOF};
static const uint16_t kGpioColorPins[] = {GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_6, GPIO_PIN_7};

static const uint32_t timer_channel[] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4};

class Leds {
  public:
  Leds()
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef gpioInit;
    for (size_t i = 0; i < CHANNEL_COUNT; i++) {
      gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
      gpioInit.Pin = kGpioColorPins[i];
      gpioInit.Pull = GPIO_NOPULL;
      gpioInit.Speed = GPIO_SPEED_FREQ_MEDIUM;
      HAL_GPIO_Init(kGpioColorPorts[i], &gpioInit);

      HAL_GPIO_WritePin(kGpioColorPorts[i], kGpioColorPins[i], GPIO_PIN_RESET);
    }


    __HAL_RCC_TIM1_CLK_ENABLE();

    htim1.Init.Prescaler = 1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 1024; // 10 bit
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim1);

    TIM_MasterConfigTypeDef sMasterConfig;
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 100;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    for(size_t i = 0; i < CHANNEL_COUNT; i++) {
      HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, timer_channel[i]);
      gpioInit.Mode = GPIO_MODE_AF_PP;
      gpioInit.Pin = kGpioPins[i];
      gpioInit.Pull = GPIO_NOPULL;
      gpioInit.Speed = GPIO_SPEED_FREQ_MEDIUM;
      gpioInit.Alternate = GPIO_AF2_TIM1;
      HAL_GPIO_Init(kGpioPorts[i], &gpioInit);
      HAL_TIM_PWM_Start(&htim1, timer_channel[i]);
    }

  }

  void Write()
  {
    for(size_t i = 0; i < CHANNEL_COUNT; i++) {
      LedColor targetColor = colors[i];
      uint16_t intensity = intensities[i];
      if(colors[i] == LED_COLOR_ORANGE) {
        if(toggle[i]) targetColor = LED_COLOR_RED;
        else targetColor = LED_COLOR_GREEN;
        toggle[i] = !toggle[i];
      }

      if(targetColor == LED_COLOR_RED) {
        HAL_GPIO_WritePin(kGpioColorPorts[i], kGpioColorPins[i], GPIO_PIN_SET);
        intensity = 65535 - lut_led_red_gamma[intensity >> 6];
      } else if(targetColor == LED_COLOR_GREEN) {
        HAL_GPIO_WritePin(kGpioColorPorts[i], kGpioColorPins[i], GPIO_PIN_RESET);
        intensity = lut_led_green_gamma[intensity >> 6];
      }

      __HAL_TIM_SET_COMPARE(&htim1, timer_channel[i], (intensity >> 6));
    }
  }

  void set_intensity_signed(uint8_t channel, int16_t intensity) {
    if(channel >= CHANNEL_COUNT) return;

    if(intensity < 0) {
      colors[channel] = LED_COLOR_RED;
      intensities[channel] = (-intensity) << 1;
    } else {
      colors[channel] = LED_COLOR_GREEN;
      intensities[channel] = (intensity) << 1;
    }

  }

  void set_intensity_unsigned(uint8_t channel, uint16_t intensity, LedColor color)
  {
    if (channel >= CHANNEL_COUNT)
      return;

    intensities[channel] = intensity;
    colors[channel] = color;
  }

  private:
  uint16_t intensities[CHANNEL_COUNT];
  bool toggle[CHANNEL_COUNT];
  LedColor colors[CHANNEL_COUNT];
};
