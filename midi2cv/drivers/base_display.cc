#include "base_display.h"
#include "spi_mode.h"
#include <U8x8lib.h>
#include <stm32f37x_conf.h>

static const uint16_t kPinEnable = GPIO_Pin_2;
static const uint16_t kPinReset = GPIO_Pin_0;
static const uint16_t kPinDataCommand = GPIO_Pin_9;

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t* u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void* arg_ptr)
{
  return 1;
}

uint8_t u8x8_byte_4wire_stm32_spi(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int,
    void* arg_ptr)
{
  uint8_t* data;
  switch (msg) {
  case U8X8_MSG_BYTE_SEND:
    data = (uint8_t*)arg_ptr;
    while (arg_int > 0) {
      while (!(SPI2->SR & SPI_SR_TXE)) {
      }
      SPI_SendData8(SPI2, (uint8_t)*data);
      arg_int--;
      data++;
    }
    break;
  case U8X8_MSG_BYTE_INIT:
    break;
  case U8X8_MSG_BYTE_SET_DC:
    if (arg_int)
      GPIO_WriteBit(GPIOB, kPinDataCommand, Bit_SET);
    else
      GPIO_WriteBit(GPIOB, kPinDataCommand, Bit_RESET);
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    InitSPI(SPI_MODE_DISPLAY);
    GPIO_WriteBit(GPIOB, kPinEnable, Bit_RESET);
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    GPIO_WriteBit(GPIOB, kPinEnable, Bit_SET);
    break;
  default:
    return 0;
  }
  return 1;
}

void BaseDisplay::Init()
{
  // init SS/CS/RST GPIO
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  GPIO_InitTypeDef gpio_init;
  gpio_init.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init.GPIO_OType = GPIO_OType_PP;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio_init.GPIO_Pin = kPinEnable | kPinReset | kPinDataCommand;
  GPIO_Init(GPIOB, &gpio_init);

  GPIO_WriteBit(GPIOB, kPinEnable, Bit_SET);

  // init AF GPIO
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  gpio_init.GPIO_Mode = GPIO_Mode_AF;
  gpio_init.GPIO_OType = GPIO_OType_PP;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio_init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &gpio_init);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_5);

  // init SPI
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  SPI_I2S_DeInit(SPI2);
  // Initialize SPI
  InitSPI(SPI_MODE_DISPLAY);
  GPIO_WriteBit(GPIOB, kPinReset, Bit_RESET);
  asm("nop");

  GPIO_WriteBit(GPIOB, kPinReset, Bit_SET);
  InitGLib();
}
