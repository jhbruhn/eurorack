#include "ad57x4.h"
#include "peripherals.h"
#include "spi_mode.h"
#include <stm32f3xx_hal.h>
#include <math.h>

static const uint32_t kPinEnable = GPIO_PIN_5;

void AD57X4::Init()
{
  GPIO_InitTypeDef init;
  init.Pin = kPinEnable;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
  init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &init);

  HAL_GPIO_WritePin(GPIOB, kPinEnable, GPIO_PIN_SET);
}

void AD57X4::WriteVoltage(uint8_t dac, float voltage) {
  VoltageRange range = VOLTAGE_RANGE_FIVE_VOLTS;
  if(fabs(voltage) > 5) range = VOLTAGE_RANGE_TEN_VOLTS;
  if(fabs(voltage) > 10) range = VOLTAGE_RANGE_TEN_EIGHT_VOLTS;

  float multiplier = 2.0f;
  if(range == VOLTAGE_RANGE_TEN_VOLTS) multiplier = 4.0f;
  if(range == VOLTAGE_RANGE_TEN_EIGHT_VOLTS) multiplier = 4.32f;
  float refin = 2.5f;

  if(voltage < 0) {
    // convert to signed value
    int16_t value = (voltage / (multiplier * refin)) * (65535.0f);

    this->WriteDacBipolar(dac, range, value);
  } else {
    // convert to unsigned value
    uint16_t value = (voltage / (multiplier * refin)) * (65535.0f);

    this->WriteDacUnipolar(dac, range, value);
  }
}

void AD57X4::EnableAndSetRange(uint8_t dac, VoltageRange range, bool bipolar)
{
  if (!(this->dacPower & (1 << dac))) {
    // power on dac
    this->dacPower |= 1 << dac;
    this->Write(REGISTER_POWER_CONTROL, 0, this->dacPower);
  }
  if (this->dacRange[dac] != range) {
    this->Write(REGISTER_OUTPUT_RANGE, dac, range + (bipolar ? 3 : 0));
    this->dacRange[dac] = range;
  }
}

void AD57X4::WriteDacUnipolar(uint8_t dac, VoltageRange range, uint16_t value)
{
  EnableAndSetRange(dac, range, false);
  this->Write(REGISTER_DAC, dac, value);
}

void AD57X4::WriteDacBipolar(uint8_t dac, VoltageRange range, int16_t value)
{
  uint16_t twosComplement = value;
  if (value < 0) {
    twosComplement = ~(-value) + 1;
  }

  EnableAndSetRange(dac, range, true);
  this->Write(REGISTER_DAC, dac, twosComplement);
}

void AD57X4::Write(Register reg, uint8_t address, uint16_t data)
{
  uint8_t first = address; // select address
  first |= reg << 3;       // select register
  first |= 0 << 7;         // write command
  first |= 0 << 6;         // always 0

  InitSPI(SPI_MODE_DAC1);

  HAL_GPIO_WritePin(GPIOB, kPinEnable, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, &first, 1, HAL_MAX_DELAY); // write data
  HAL_SPI_Transmit(&hspi2, reinterpret_cast<uint8_t*>(&data), 2, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, kPinEnable, GPIO_PIN_SET);
}
