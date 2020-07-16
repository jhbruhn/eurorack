#include "processor.h"
#include "stmlib/stmlib.h"
#include "stmlib/dsp/dsp.h"
#include "stmlib/utils/dsp.h"
#include <math.h>

using namespace stereo_mix;
using namespace stmlib;

void Processor::Process(int16_t cvs[], uint16_t* outs)
{
  uint32_t value_l;
  uint32_t value_r;

  // dirty low pass
  this->cv_input_pan += ((cvs[0] - this->cv_input_pan) >> 4);
  this->cv_input_vol += ((cvs[1] - this->cv_input_vol) >> 5);

  uint16_t pan_pot = (pan_offset + 32767L);
  uint16_t vol_pot = (vol_offset);
  int32_t vol_cv = (cv_input_vol * static_cast<int32_t>(vol_att)) >> 15;
  vol_cv = Clip16(vol_cv);


  // calculate value for ui
  int32_t lin = vol_offset + (vol_cv << 3) * 3;
  lin = ClipU16(lin);
  this->linear_vol = lin;

  uint16_t vol_pot_exp = Interpolate124(lut_linear_to_exp, vol_pot);
  uint16_t vol_pot_log = 65535 - InverseInterpolate124(lut_linear_to_exp, vol_pot);

  int32_t vol = Mix(static_cast<uint16_t>(vol_pot_exp >> 1), vol_pot_log >> 1, log_exp_mix_pot) << 1;
  uint16_t vol_cv_absu16 = abs(vol_cv) << 1;
  uint16_t vol_cv_exp = Interpolate124(lut_linear_to_exp, vol_cv_absu16);
  uint16_t vol_cv_log = 65535 - InverseInterpolate124(lut_linear_to_exp, vol_cv_absu16);
  uint32_t vol_cv_pre = (Mix(static_cast<uint16_t>(vol_cv_exp >> 1), vol_cv_log >> 1, log_exp_mix_cv) << 1) * 2;
  vol += vol_cv > 0 ? vol_cv_pre : -vol_cv_pre;
  vol *= !mute;

  vol = ClipU16(vol);

  int32_t pan_cv = (cv_input_pan * static_cast<int32_t>(pan_att)) >> 15; // full attenuate gives 2x amplification :)
  pan_cv = Clip16(pan_cv);
  int32_t pan = pan_pot + ((pan_cv) * 2);
  pan = ClipU16(pan);

  value_l = (lut_left_sin_pan[pan >> 4] * vol) >> 16;
  value_r = (lut_right_cos_pan[pan >> 4] * vol) >> 16;

  outs[0] = value_r;
  outs[1] = value_l;
}
