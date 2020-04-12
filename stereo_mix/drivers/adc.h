#pragma once

#include "stmlib/stmlib.h"

#include <stm32f0xx_hal.h>

namespace stereo_mix {

enum AdcChannel {
  ADC_CHANNEL_CV_VOL_1,
  ADC_CHANNEL_CV_VOL_2,
  ADC_CHANNEL_CV_VOL_3,
  ADC_CHANNEL_CV_VOL_4,
  ADC_CHANNEL_CV_PAN_1,
  ADC_CHANNEL_CV_PAN_2,
  ADC_CHANNEL_CV_PAN_3,
  ADC_CHANNEL_CV_PAN_4,
  ADC_CHANNEL_MUX,
  ADC_CHANNEL_LAST,

  ADC_CHANNEL_COUNT = (ADC_CHANNEL_LAST * 2) - 1
};

enum AdcGroup {
  ADC_GROUP_CV = 0,
  ADC_GROUP_POT = ADC_CHANNEL_LAST,

  ADC_GROUP_COUNT
};

class Adc {
  public:
  Adc() {}
  ~Adc() {}

  void Init();
  void DeInit();
  void OnDMATransferComplete();
  inline const uint16_t* values() { return &values_[0]; }
  inline int32_t value(int32_t channel) const
  {
    return static_cast<int32_t>(values_[channel]);
  }
  inline float float_value(int32_t index) const
  {
    return static_cast<float>(values_[index]) / 65536.0f;
  }
  DMA_HandleTypeDef dma;
  ADC_HandleTypeDef adc;

  private:
  uint16_t values_[ADC_CHANNEL_COUNT];
  uint8_t mux_index_;

  DISALLOW_COPY_AND_ASSIGN(Adc);
};

} // namespace stereo_mix
