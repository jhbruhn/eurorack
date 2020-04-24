#pragma once

#include "peripherals.h"
#include "stm32f0xx_hal_gpio.h"
#include <algorithm>
#include <stm32f0xx_hal.h>

enum Switch {
  SWITCH_1,
  SWITCH_2,
  SWITCH_3,
  SWITCH_4,
  SWITCH_COUNT
};

static const uint16_t kSwitchPins[] = { GPIO_PIN_12, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_6 };
static GPIO_TypeDef* kSwitchPorts[] = { GPIOA, GPIOB, GPIOB, GPIOB };

class Switches {
  public:
  Switches()
  {
    GPIO_InitTypeDef gpio;
    for (size_t i = 0; i < SWITCH_COUNT; i++) {
      gpio.Mode = GPIO_MODE_INPUT;
      gpio.Pin = kSwitchPins[i];
      gpio.Pull = GPIO_PULLUP;
      gpio.Speed = GPIO_SPEED_FREQ_MEDIUM;
      HAL_GPIO_Init(kSwitchPorts[i], &gpio);
    }

    std::fill(&switch_state_[0], &switch_state_[SWITCH_COUNT], 0xff);
  }

  void Debounce()
  {
    for (int i = 0; i < SWITCH_COUNT; ++i) {
      switch_state_[i] = (switch_state_[i] << 1) | HAL_GPIO_ReadPin(kSwitchPorts[i], kSwitchPins[i]);
    }
  }

  inline bool released(Switch s) const
  {
    return switch_state_[s] == 0x7f;
  }

  inline bool just_pressed(Switch s) const
  {
    return switch_state_[s] == 0x80;
  }

  inline bool pressed(Switch s) const
  {
    return switch_state_[s] == 0x00;
  }

  inline bool pressed_immediate(Switch s) const
  {
    return !HAL_GPIO_ReadPin(kSwitchPorts[s], kSwitchPins[s]);
  }

  private:
  uint8_t switch_state_[SWITCH_COUNT];
};
