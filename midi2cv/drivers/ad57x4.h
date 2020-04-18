#pragma once

#include "stmlib/stmlib.h"

enum VoltageRange {
  VOLTAGE_RANGE_NONE = 4,
  VOLTAGE_RANGE_FIVE_VOLTS = 0,
  VOLTAGE_RANGE_TEN_VOLTS = 1,
  VOLTAGE_RANGE_TEN_EIGHT_VOLTS = 2
};

enum Register {
  REGISTER_DAC = 0,
  REGISTER_OUTPUT_RANGE = 1,
  REGISTER_CONTROL = 2,
  REGISTER_POWER_CONTROL = 3
};

class AD57X4 {
  public:
  AD57X4()
  {
    for (size_t i = 0; i < 4; i++)
      dacRange[i] = VOLTAGE_RANGE_NONE;
  };

  void Init();

  void WriteVoltage(uint8_t dac, float voltage); // smart range choosing!

  void WriteDacBipolar(uint8_t dac, VoltageRange range, int16_t value);
  void WriteDacUnipolar(uint8_t dac, VoltageRange range, uint16_t value);

  private:
  uint8_t dacPower = 0;
  VoltageRange dacRange[4];
  void EnableAndSetRange(uint8_t dac, VoltageRange range, bool bipolar);
  void Write(Register reg, uint8_t address, uint16_t data);
  DISALLOW_COPY_AND_ASSIGN(AD57X4);
};
