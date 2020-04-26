#pragma once

#ifdef ENABLE_DEBUG_PIN
#define DEBUG_PIN

#define DEBUG_ON HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
#define DEBUG_OFF HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
#else
#define DEBUG_ON {};
#define DEBUG_OFF {};
#endif
