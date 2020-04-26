#include "processor.h"
#include "stmlib/stmlib.h"
#include <math.h>

using namespace stereo_mix;

const int kVolumeFilterValue = 4095;

void Processor::Process(int16_t cvs[], uint16_t* outs)
{
  uint32_t value_l;
  uint32_t value_r;

  uint16_t pan_pot = (pan_offset + 32767L) >> (16 - 12); // adc is only 12 bit anyways
  uint16_t vol_pot = (volume_offset) >> (16 - 12);
  int16_t pan_cv = cvs[0] >> (16 - 12);
  int16_t vol_cv = cvs[1] >> (16 - 12);
  int32_t pan = pan_pot + pan_cv;
  int32_t vol = vol_pot + vol_cv;
  CONSTRAIN(pan, 0, (1 << 12) - 1);
  CONSTRAIN(vol, 0, (1 << 12) - 1);

  if (mute) {
    vol = 0;
  }

  if (vol > previous_vol + kVolumeFilterValue) {
    vol = previous_vol + kVolumeFilterValue;
  } else if (vol < previous_vol - kVolumeFilterValue) {
    vol = previous_vol - kVolumeFilterValue;
  }

  CONSTRAIN(pan, 0, (1 << 12) - 1);
  CONSTRAIN(vol, 0, (1 << 12) - 1);

  previous_vol = vol;

  // leds.set_intensity(i, vol >> 4);
  value_l = (lut_left_sin_pan[pan] * lut_linear_to_exp[vol]) >> 16;
  value_r = (lut_right_cos_pan[pan] * lut_linear_to_exp[vol]) >> 16;

  outs[0] = value_r;
  outs[1] = value_l;
}
