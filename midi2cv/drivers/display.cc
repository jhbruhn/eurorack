#include "display.h"
#include "gpio.h"
#include <stm32f37x_conf.h>
#include <u8g2.h>
// SH1106 command definitions
#define SH1106_CMD_SETMUX (uint8_t)0xA8    // Set multiplex ratio (N, number of lines active on display)
#define SH1106_CMD_SETOFFS (uint8_t)0xD3   // Set display offset
#define SH1106_CMD_STARTLINE (uint8_t)0x40 // Set display start line
#define SH1106_CMD_SEG_NORM (uint8_t)0xA0  // Column 0 is mapped to SEG0 (X coordinate normal)
#define SH1106_CMD_SEG_INV (uint8_t)0xA1   // Column 127 is mapped to SEG0 (X coordinate inverted)
#define SH1106_CMD_COM_NORM (uint8_t)0xC0  // Scan from COM0 to COM[N-1] (N - mux ratio, Y coordinate normal)
#define SH1106_CMD_COM_INV (uint8_t)0xC8   // Scan from COM[N-1] to COM0 (N - mux ratio, Y coordinate inverted)
#define SH1106_CMD_COM_HW (uint8_t)0xDA    // Set COM pins hardware configuration
#define SH1106_CMD_CONTRAST (uint8_t)0x81  // Contrast control
#define SH1106_CMD_EDON (uint8_t)0xA5      // Entire display ON enabled (all pixels on, RAM content ignored)
#define SH1106_CMD_EDOFF (uint8_t)0xA4     // Entire display ON disabled (output follows RAM content)
#define SH1106_CMD_INV_OFF (uint8_t)0xA6   // Entire display inversion OFF (normal display)
#define SH1106_CMD_INV_ON (uint8_t)0xA7    // Entire display inversion ON (all pixels inverted)
#define SH1106_CMD_CLOCKDIV (uint8_t)0xD5  // Set display clock divide ratio/oscillator frequency
#define SH1106_CMD_DISP_ON (uint8_t)0xAF   // Display ON
#define SH1106_CMD_DISP_OFF (uint8_t)0xAE  // Display OFF (sleep mode)

#define SH1106_CMD_COL_LOW (uint8_t)0x00   // Set Lower Column Address
#define SH1106_CMD_COL_HIGH (uint8_t)0x10  // Set Higher Column Address
#define SH1106_CMD_PAGE_ADDR (uint8_t)0xB0 // Set Page Address

#define SH1106_CMD_CHARGE (uint8_t)0x22    //  Dis-charge / Pre-charge Period
#define SH1106_CMD_SCRL_HR (uint8_t)0x26   // Setup continuous horizontal scroll right
#define SH1106_CMD_SCRL_HL (uint8_t)0x27   // Setup continuous horizontal scroll left
#define SH1106_CMD_SCRL_VHR (uint8_t)0x29  // Setup continuous vertical and horizontal scroll right
#define SH1106_CMD_SCRL_VHL (uint8_t)0x2A  // Setup continuous vertical and horizontal scroll left
#define SH1106_CMD_SCRL_STOP (uint8_t)0x2E // Deactivate scroll
#define SH1106_CMD_SCRL_ACT (uint8_t)0x2F  // Activate scroll

void Display::Init()
{
    gpio.Write(GPIO_PIN(SS_OLED), Bit_SET); // deactivate OLED spi

    gpio.Write(GPIO_PIN(RST_OLED), Bit_SET);
    gpio.Write(GPIO_PIN(RST_OLED), Bit_RESET);
    gpio.Write(GPIO_PIN(RST_OLED), Bit_SET);

    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);

    SPI_InitTypeDef spi_init;
    spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi_init.SPI_Mode = SPI_Mode_Master;
    spi_init.SPI_DataSize = SPI_DataSize_8b;
    spi_init.SPI_CPOL = SPI_CPOL_Low;
    spi_init.SPI_CPHA = SPI_CPHA_1Edge;
    spi_init.SPI_NSS = SPI_NSS_Soft;
    spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    spi_init.SPI_FirstBit = SPI_FirstBit_LSB;
    spi_init.SPI_CRCPolynomial = 10;
    SPI_Init(SPI2, &spi_init);
    SPI_CalculateCRC(SPI2, DISABLE);
    SPI_Cmd(SPI2, ENABLE);

#define SH1106_cmd_double(x, y) \
    WriteCommand(x);            \
    WriteCommand(y);
#define SH1106_cmd(x) WriteCommand(x);

    // Set multiplex ratio (visible lines)
    SH1106_cmd_double(SH1106_CMD_SETMUX, 0x3F); // 64MUX

    // Set display offset (offset of first line from the top of display)
    SH1106_cmd_double(SH1106_CMD_SETOFFS, 0x00); // Offset: 0

    // Set display start line (first line displayed)
    SH1106_cmd(SH1106_CMD_STARTLINE | 0x00); // Start line: 0

    // Set segment re-map (X coordinate)
    SH1106_cmd(SH1106_CMD_SEG_NORM);

    // Set COM output scan direction (Y coordinate)
    SH1106_cmd(SH1106_CMD_COM_NORM);

    // Set COM pins hardware configuration
    // bit[4]: reset - sequential COM pin configuration
    //         set   - alternative COM pin configuration (reset value)
    // bit[5]: reset - disable COM left/right remap (reset value)
    //         set   - enable COM left/right remap
    SH1106_cmd_double(SH1106_CMD_COM_HW, 0x12);

    uint8_t dis_charge = 0x00;
    uint8_t pre_charge = 0x00;

    SH1106_cmd_double(SH1106_CMD_CHARGE, dis_charge | (pre_charge << 4));

    // Set contrast control
    SH1106_cmd_double(SH1106_CMD_CONTRAST, 0x0F); // Contrast: middle level

    SH1106_cmd(0x30);

    // Disable entire display ON
    SH1106_cmd(SH1106_CMD_EDOFF); // Display follows RAM content

    // Disable display inversion
    SH1106_cmd(SH1106_CMD_INV_OFF); // Normal display mode

    // Set clock divide ratio and oscillator frequency
    // bits[3:0] defines the divide ratio of the display clocks (bits[3:0] + 1)
    // bits[7:4] set the oscillator frequency (Fosc), frequency increases with the value of these bits
    // 0xF0 value gives maximum frequency (maximum Fosc without divider)
    // 0x0F value gives minimum frequency (minimum Fosc divided by 16)
    // The higher display frequency decreases image flickering but increases current consumption and vice versa
    SH1106_cmd_double(SH1106_CMD_CLOCKDIV, 0xF0);

    // Display ON
    SH1106_cmd(SH1106_CMD_DISP_ON); // Display enabled
    SH1106_cmd(SH1106_CMD_EDON);
    Clear();
    Update();
}

void Display::WriteCommand(uint8_t byte)
{
    gpio.Write(GPIO_PIN(SDC_OLED), Bit_RESET); // command mode
    gpio.Write(GPIO_PIN(SS_OLED), Bit_RESET);  // activate OLED spi
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
	;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
	;
    SPI_I2S_SendData(SPI2, byte);	   // transmit via spi
    gpio.Write(GPIO_PIN(SS_OLED), Bit_SET); // disable oled spi
}

void Display::WriteData(uint8_t* buffer, uint8_t size)
{
    gpio.Write(GPIO_PIN(SDC_OLED), Bit_SET);  // data mode
    gpio.Write(GPIO_PIN(SS_OLED), Bit_RESET); // activate OLED spi
    for (int i = 0; i < size; i++) {
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
	    ;
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
	    ;
	SPI_I2S_SendData(SPI2, buffer[i]); // transmit via spi
	for (int i = 0; i < 100; i++)
	    ;
    }
    gpio.Write(GPIO_PIN(SS_OLED), Bit_SET); // disable oled spi
}

void Display::Clear()
{
    uint32_t i = 0;
    for (i = 0; i < sizeof(buffer); i++)
	buffer[i] = 0x00;
}

void Display::Update()
{
    for (uint32_t i = 0; i < 8; i++) {
	WriteCommand(0xb0 + i);
	WriteCommand(0x00);
	WriteCommand(0x10);
	WriteData(&buffer[128 * i], 128);
    }
}

void Display::WritePixel(uint8_t x, uint8_t y, bool color)
{
    if (x > DISPLAY_WIDTH || y > DISPLAY_HEIGHT)
	return;

    if (color) {
	buffer[x + (y / 8) * DISPLAY_WIDTH] |= 1 << (y % 8);
    } else {
	buffer[x + (y / 8) * DISPLAY_WIDTH] &= ~(1 << (y % 8));
    }
}
