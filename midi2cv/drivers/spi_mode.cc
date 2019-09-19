#include "spi_mode.h"
#include <stm32f37x_conf.h>

uint8_t currentMode = 0;

void InitSPIDisplay(void);

void InitSPI(uint8_t mode)
{
    if (currentMode != mode) {
	switch (mode) {
	case SPI_MODE_DISPLAY:
	    InitSPIDisplay();
	    break;
	case SPI_MODE_DAC0:
	case SPI_MODE_DAC1:
	case SPI_MODE_USB:
	    break;
	}
	currentMode = mode;
    }
}

void InitSPIDisplay(void)
{
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
}
