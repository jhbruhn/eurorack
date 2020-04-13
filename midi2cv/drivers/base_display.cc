#include "base_display.h"
#include "peripherals.h"
#include "spi_mode.h"
#include <U8x8lib.h>
#include <stm32f3xx_hal.h>

static const uint16_t kPinEnable = GPIO_PIN_2;
static const uint16_t kPinReset = GPIO_PIN_0;
static const uint16_t kPinDataCommand = GPIO_PIN_9;

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t* u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void* arg_ptr)
{
  return 1;
}

uint8_t u8x8_byte_4wire_stm32_spi(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int,
    void* arg_ptr)
{
  uint8_t* data = (uint8_t*)arg_ptr;
  switch (msg) {
  case U8X8_MSG_BYTE_SEND:

    HAL_SPI_Transmit(&hspi2, data, arg_int, 0);
    break;
  case U8X8_MSG_BYTE_INIT:
    break;
  case U8X8_MSG_BYTE_SET_DC:
    HAL_GPIO_WritePin(GPIOB, kPinDataCommand, arg_int ? GPIO_PIN_SET : GPIO_PIN_RESET);
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    InitSPI(SPI_MODE_DISPLAY);
    HAL_GPIO_WritePin(GPIOB, kPinEnable, GPIO_PIN_RESET);
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    HAL_GPIO_WritePin(GPIOB, kPinEnable, GPIO_PIN_SET);
    break;
  default:
    return 0;
  }
  return 1;
}

void BaseDisplay::Init()
{
  // init SS/CS/RST GPIO
  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitTypeDef gpio_init;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Pin = kPinEnable | kPinReset | kPinDataCommand;
  HAL_GPIO_Init(GPIOB, &gpio_init);

  HAL_GPIO_WritePin(GPIOB, kPinEnable, GPIO_PIN_SET);

  // init SPI
  // Initialize SPI
  InitSPI(SPI_MODE_DISPLAY);
  HAL_GPIO_WritePin(GPIOB, kPinReset, GPIO_PIN_RESET);
  asm("nop");

  HAL_GPIO_WritePin(GPIOB, kPinReset, GPIO_PIN_SET);
  InitGLib();
}
