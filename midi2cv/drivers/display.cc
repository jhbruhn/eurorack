#include "display.h"
#include "gpio.h"
#include "stmlib/system/system_clock.h"
#include "stmlib/utils/random.h"
#include <stm32f37x_conf.h>
#include <u8g2.h>

using namespace stmlib;

const uint16_t kPinEnable = GPIO_Pin_2;
const uint16_t kPinReset = GPIO_Pin_0;
const uint16_t kPinDataCommand = GPIO_Pin_9;

u8g2_t u8g2_;
uint8_t* default_buf;
uint8_t second_buf[1024];
uint8_t* output_buf;

u8g2_t* Display::u8g2()
{
    return &u8g2_;
}

void Display::Init()
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
    SPI_InitTypeDef spi_init;
    spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi_init.SPI_Mode = SPI_Mode_Master;
    spi_init.SPI_DataSize = SPI_DataSize_8b;
    spi_init.SPI_CPOL = SPI_CPOL_High;
    spi_init.SPI_CPHA = SPI_CPHA_2Edge;
    spi_init.SPI_NSS = SPI_NSS_Soft;
    spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
    spi_init.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &spi_init);
    SPI_Cmd(SPI2, ENABLE);

    GPIO_WriteBit(GPIOB, kPinReset, Bit_RESET);
    asm("nop");

    GPIO_WriteBit(GPIOB, kPinReset, Bit_SET);
    InitGLib();
}

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t* u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void* arg_ptr)
{
    return 1;
}

uint8_t u8x8_byte_4wire_hw_spi(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int,
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

void Display::InitGLib()
{
    u8g2_Setup_sh1106_128x64_noname_f(&u8g2_, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);
    output_buf = default_buf = u8g2_.tile_buf_ptr;
    u8g2_InitDisplay(&u8g2_);
    u8g2_SetContrast(&u8g2_, 127);
    u8g2_SetPowerSave(&u8g2_, 0);

    Random::Seed(42);
}

void Display::Flush()
{
    uint8_t* cache = u8g2_.tile_buf_ptr;
    u8g2_.tile_buf_ptr = output_buf;
    u8g2_SendBuffer(&u8g2_);
    u8g2_.tile_buf_ptr = cache;
}

void Display::Swap()
{
    output_buf = u8g2_.tile_buf_ptr;
    if (output_buf == default_buf)
	u8g2_.tile_buf_ptr = second_buf;
    else
	u8g2_.tile_buf_ptr = default_buf;
}
