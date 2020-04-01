#pragma once

#include "stmlib/stmlib.h"

namespace stereo_mix {

enum AdcChannel {
  ADC_CHANNEL_MUX,
  ADC_CHANNEL_CV_PAN_4,
  ADC_CHANNEL_CV_PAN_3,
  ADC_CHANNEL_CV_PAN_2,
  ADC_CHANNEL_CV_PAN_1,
  ADC_CHANNEL_CV_VOL_4,
  ADC_CHANNEL_CV_VOL_3,
  ADC_CHANNEL_CV_VOL_2,
  ADC_CHANNEL_CV_VOL_1,
  ADC_CHANNEL_POT_VOL_1,
  ADC_CHANNEL_POT_VOL_2,
  ADC_CHANNEL_POT_VOL_3,
  ADC_CHANNEL_POT_VOL_4,
  ADC_CHANNEL_POT_PAN_1,
  ADC_CHANNEL_POT_PAN_2,
  ADC_CHANNEL_POT_PAN_3,
  ADC_CHANNEL_POT_PAN_4,
  ADC_CHANNEL_LAST,

  ADC_CHANNEL_FIRST_DIRECT = ADC_CHANNEL_MUX,
  ADC_CHANNEL_LAST_DIRECT = ADC_CHANNEL_CV_VOL_1,
  ADC_CHANNEL_FIRST_MUXED = ADC_CHANNEL_POT_VOL_1,
  ADC_CHANNEL_LAST_MUXED = ADC_CHANNEL_POT_PAN_4,
  ADC_CHANNEL_NUM_DIRECT = ADC_CHANNEL_CV_VOL_1 + 1,
  ADC_CHANNEL_NUM_MUXED = ADC_CHANNEL_LAST - ADC_CHANNEL_FIRST_MUXED,
};

class Adc {
  public:
  Adc() {}
  ~Adc() {}

  void Init();
  void DeInit();
  void OnDMAFinish();
  inline const uint16_t* values() { return &values_[0]; }
  inline int32_t value(int32_t channel) const
  {
    return static_cast<int32_t>(values_[channel]);
  }
  inline float float_value(int32_t index) const
  {
    return static_cast<float>(values_[index]) / 65536.0f;
  }

  private:
  uint16_t values_[ADC_CHANNEL_LAST];
  uint8_t mux_index_;

  DISALLOW_COPY_AND_ASSIGN(Adc);
};

} // namespace stereo_mix
