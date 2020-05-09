#include "processor.h"
#include "stmlib/stmlib.h"
#include "stmlib/utils/dsp.h"
#include <math.h>

using namespace stereo_mix;
using namespace stmlib;

void Processor::Process(int16_t cvs[], uint16_t* outs)
{
  uint32_t value_l;
  uint32_t value_r;

  uint16_t pan_pot = (pan_offset + 32767L);
  uint16_t vol_pot = (volume_offset);
  int16_t pan_cv = cvs[0];
  int16_t vol_cv = cvs[1];
  int32_t pan = pan_pot + pan_cv;

  // calculate value for ui
  int32_t lin = volume_offset + (cvs[1] << 1);
  CONSTRAIN(lin, 0, 65535);
  lin *= !mute;
  this->linear_vol = lin;

  uint16_t vol_pot_exp = Interpolate124(lut_linear_to_exp, vol_pot);
  uint16_t vol_pot_log = 65535 - InverseInterpolate124(lut_linear_to_exp, vol_pot);

  vol_pot = Mix(vol_pot_exp, vol_pot_log, log_exp_mix_pot);
  int32_t vol = vol_pot;

  uint16_t vol_cv_absu16 = abs(vol_cv);
  uint16_t vol_cv_exp = Interpolate124(lut_linear_to_exp, vol_cv_absu16);
  uint16_t vol_cv_log = 65535 - InverseInterpolate124(lut_linear_to_exp, vol_cv_absu16);
  uint16_t vol_cv_pre = Mix(vol_cv_exp, vol_cv_log, log_exp_mix_cv);
  vol += vol_cv > 0 ? vol_cv_pre : -vol_cv_pre;
  vol *= !mute;

  CONSTRAIN(pan, 0, 65535);
  CONSTRAIN(vol, 0, 65535);

  this->previous_vol = vol;

  value_l = (Interpolate124(lut_left_sin_pan, pan) * vol) >> 16;
  value_r = (Interpolate124(lut_right_cos_pan, pan) * vol) >> 16;

  outs[0] = value_r;
  outs[1] = value_l;
}
