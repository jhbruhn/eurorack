#include "processor.h"
#include "stmlib/stmlib.h"
#include "stmlib/utils/dsp.h"
#include <math.h>

using namespace stereo_mix;
using namespace stmlib;

const int kVolumeFilterValue = 65535;

void Processor::Process(int16_t cvs[], uint16_t* outs)
{
  uint32_t value_l;
  uint32_t value_r;

  uint16_t pan_pot = (pan_offset + 32767L) >> (16 - 12); // adc is only 12 bit anyways
  uint16_t vol_pot = (volume_offset) >> (16 - 12);
  int16_t pan_cv = cvs[0] >> (16 - 12);
  int16_t vol_cv = cvs[1] >> (16 - 12);
  int32_t pan = pan_pot + pan_cv;

  // calculate value for ui
  int32_t lin = volume_offset + (cvs[1] * 2);
  CONSTRAIN(lin, 0, 65535);
  lin *= !mute;
  linear_vol = lin;

  uint16_t vol_pot_exp = lut_linear_to_exp[vol_pot];
  uint16_t vol_pot_log = 65535 - lut_linear_to_exp[LUT_LINEAR_TO_EXP_SIZE - 1 - vol_pot];

  vol_pot = Mix(vol_pot_exp, vol_pot_log, log_exp_mix_pot);
  vol_pot = vol_pot_exp;
  int32_t vol = vol_pot;

  uint16_t vol_cv_absu16 = abs(vol_cv);
  uint16_t vol_cv_exp = lut_linear_to_exp[vol_cv_absu16];
  uint16_t vol_cv_log = 65535 - lut_linear_to_exp[LUT_LINEAR_TO_EXP_SIZE - 1 - vol_cv_absu16];
  uint16_t vol_cv_pre = Mix(vol_cv_exp, vol_cv_log, log_exp_mix_cv);
  vol += vol_cv > 0 ? vol_cv_pre : -vol_cv_pre;
  vol *= !mute;

  CONSTRAIN(pan, 0, 4095);
  CONSTRAIN(vol, 0, 65535);

  previous_vol = vol;

  // leds.set_intensity(i, vol >> 4);
  value_l = (lut_left_sin_pan[pan] * vol) >> 16;
  value_r = (lut_right_cos_pan[pan] * vol) >> 16;

  outs[0] = value_r;
  outs[1] = value_l;
}
