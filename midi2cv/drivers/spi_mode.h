#ifndef MIDI2CV_DRIVERS_SPI_MODE_H
#define MIDI2CV_DRIVERS_SPI_MODE_H

#include <stm32f37x_conf.h>

#define SPI_MODE_DISPLAY 1
#define SPI_MODE_DAC0 2
#define SPI_MODE_DAC1 3
#define SPI_MODE_USB 4

void InitSPI(uint8_t mode);

#endif
